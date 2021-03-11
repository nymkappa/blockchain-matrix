#pragma once

#include <string>
#include <iostream>
#include "AEvent.hpp"

class TransactionEvent : public AEvent
{
public:
    TransactionEvent(const std::string &txid) : AEvent(TRANSACTION), _txid(txid) {}
    std::string ToString() { return "Transaction event, hash: " + _txid; }

private:
    std::string _txid;
};
