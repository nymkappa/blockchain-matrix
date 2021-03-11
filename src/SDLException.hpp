#pragma once

#include <exception>
#include <string>

class SDLException : public std::exception
{
public:
	SDLException(const std::string &what)
	{
		_what = what;
	}

	virtual const char* what() const throw()
	{
        std::string what("SDL Exception! Error: " + _what);
        return what.c_str();
    }

public:
	std::string _what;
};