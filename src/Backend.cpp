//
// This is the Boost.Beast implementaion of a SSL websocket client
//
// All the networking/websocket/boost related code is taken directly from
// https://www.boost.org/doc/libs/develop/libs/beast/example/websocket/client/sync-ssl/websocket_client_sync_ssl.cpp
// and adapted to our needs
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <chrono>

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

#include "root_certificates.hpp"
#include "json.hpp"

#include "Backend.hpp"
#include "TransactionEvent.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

Backend::Backend()
{
    std::cout << "Backend constructor\n";

    _exitFlag = false;
}

/**
 * Connect to the websocket and perform the handshake
 */
void Backend::Init()
{
}

void Backend::Run()
{
    if (_events == nullptr)
    {
        throw std::exception("[Backend] Events queue has not been properly set");
    }

    std::cout << "Backend thread starting\n";

    try
    {
        std::string host = "ws.blockchain.info";
        auto const port = "443";
        auto const text = "{\"op\":\"unconfirmed_sub\"}";

        // The io_context is required for all I/O
        net::io_context ioc;

        // The SSL context is required, and holds certificates
        ssl::context ctx{ssl::context::tlsv12_client};

        // This holds the root certificate used for verification
        load_root_certificates(ctx);

        // These objects perform our I/O
        tcp::resolver resolver{ioc};
        websocket::stream<beast::ssl_stream<tcp::socket>> ws{ioc, ctx};

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        std::cout << "Connecting to websocket\n";

        // Make the connection on the IP address we get from a lookup
        auto ep = net::connect(get_lowest_layer(ws), results);

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if (!SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str()))
            throw beast::system_error(
                beast::error_code(
                    static_cast<int>(::ERR_get_error()),
                    net::error::get_ssl_category()),
                "Failed to set SNI Hostname");

        // Update the host_ string. This will provide the value of the
        // Host HTTP header during the WebSocket handshake.
        // See https://tools.ietf.org/html/rfc7230#section-5.4
        host += ':' + std::to_string(ep.port());

        std::cout << "Perform SSL handshake\n";

        // Perform the SSL handshake
        ws.next_layer().handshake(ssl::stream_base::client);

        // Set a decorator to change the User-Agent of the handshake
        ws.set_option(websocket::stream_base::decorator(
            [](websocket::request_type &req) {
                req.set(http::field::user_agent,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-client-coro");
            }));

        // Perform the websocket handshake
        ws.handshake(host, "/inv");

        std::cout << "Socket connection established!\n";

        ws.write(net::buffer(std::string(text)));

        // This buffer will hold the incoming message
        beast::flat_buffer buffer;

        // Read a message into our buffer
        do
        {
            ws.read(buffer);
            std::string s(beast::buffers_to_string(buffer.data()));
            std::vector<std::string> splitted = Split(s, "}{");

            for (size_t i = 0; i < splitted.size(); ++i)
            {
                // Parse the json
                auto j = nlohmann::json::parse(splitted[i]);
                if (j["op"] == "utx")
                {
                    // Create a new transaction event
                    std::unique_ptr<AEvent> ev = std::make_unique<TransactionEvent>(j["x"]["hash"]);
                    _events->push(std::move(ev));
                }
            }
        } while (buffer.size() > 0 && !_exitFlag);

        // Close the WebSocket connection
        ws.close(websocket::close_code::normal);
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "Backend thread ended\n";
}

/**
 * When we receive multiple json object, we need to split them before parsing them
 */
std::vector<std::string> Backend::Split(std::string s, std::string delimiter)
{
    std::vector<std::string> jsons;

    size_t idx = s.find("}{");
    if (idx == std::string::npos)
    {
        jsons.push_back(s);
        return std::move(jsons);
    }

    do
    {
        std::string json(s.substr(0, idx + 1));
        s.erase(0, idx + 1);
        jsons.push_back(json);
        idx = s.find("}{");
    } while (idx != std::string::npos);
    jsons.push_back(s);

    return std::move(jsons);
}

void Backend::Exit()
{
    _exitFlag = true;
}