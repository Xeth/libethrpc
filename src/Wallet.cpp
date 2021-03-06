#include "Wallet.hpp"

namespace Ethereum{namespace Connector{

Wallet::Wallet(Provider &provider) :
    _provider(provider)
{}

Collection<std::string> Wallet::getAccounts()
{
    return Collection<std::string>(_provider.request("eth_accounts"));
}

std::string Wallet::getCoinBase()
{
    Json::Value result = _provider.request("eth_coinbase");
    return result.asString();
}

BigInt Wallet::getBalance(const char *account, const char *type)
{
    Json::Value result = _provider.request("eth_getBalance", Arguments(account, type));
    return unhex<BigInt>(result.asCString());
}

BigInt Wallet::getBalance(const char *account)
{
    return getBalance(account, "latest");
}

BigInt Wallet::getBalance(const std::string &account)
{
    return getBalance(account.c_str());
}

BigInt Wallet::getPendingBalance(const char *account)
{
    return getBalance(account, "pending");
}

BigInt Wallet::getPendingBalance(const std::string &account)
{
    return getPendingBalance(account.c_str());
}


bool Wallet::unlockAccount(const char *address, const char *password, time_t time)
{
    try
    {
        Json::Value result = _provider.request("personal_unlockAccount", Arguments(address, password, SIZE_T(time)));
        return result.asBool();
    }
    catch(...)
    {}
    return false;
}

bool Wallet::unlockAccount(const std::string &address, const std::string &password, time_t time)
{
    return unlockAccount(address.c_str(), password.c_str(), time);
}
////


std::string Wallet::signAndSendTransaction(const char *from, const char *password, const char *to, const BigInt &amount, size_t nonce)
{
    return sendTransactionRequest("personal_signAndSendTransaction", Arguments(TransactionParamsFactory::makeParams(from, to, amount, SIZE_T(nonce)), password));
}

std::string Wallet::signAndSendTransaction(const char *from, const char *password, const char *to, const BigInt &amount, const BigInt &gas, const BigInt &gasPrice, size_t nonce)
{
    return sendTransactionRequest("personal_signAndSendTransaction", Arguments(TransactionParamsFactory::makeParams(from, to, amount, gas, gasPrice, SIZE_T(nonce)), password));
}

std::string Wallet::signAndSendTransaction(const char *from, const char *password, const char *to, const BigInt &amount, const BigInt &gas, size_t nonce)
{
    return sendTransactionRequest("personal_signAndSendTransaction", Arguments(TransactionParamsFactory::makeParams(from, to, amount, gas, SIZE_T(nonce)), password));
}


std::string Wallet::signAndSendTransaction(const char *from, const char *password, const char *to, const BigInt &amount, const char *data, size_t nonce)
{
    return sendTransactionRequest("personal_signAndSendTransaction", Arguments(TransactionParamsFactory::makeParams(from, to, amount, data, SIZE_T(nonce)), password));
}

std::string Wallet::signAndSendTransaction(const char *from, const char *password, const char *to, const BigInt &amount, const char *data, const BigInt &gas, const BigInt &gasPrice, size_t nonce)
{
    return sendTransactionRequest("personal_signAndSendTransaction", Arguments(TransactionParamsFactory::makeParams(from, to, amount, data, gas, gasPrice, SIZE_T(nonce)), password));
}

std::string Wallet::signAndSendTransaction(const char *from, const char *password, const char *to, const BigInt &amount, const char *data, const BigInt &gas, size_t nonce)
{
    return sendTransactionRequest("personal_signAndSendTransaction", Arguments(TransactionParamsFactory::makeParams(from, to, amount, data, gas, SIZE_T(nonce)), password));
}

std::string Wallet::signAndSendTransaction(const std::string &from, const std::string &password, const std::string &to, const BigInt &amount, size_t nonce)
{
    return signAndSendTransaction(from.c_str(), password.c_str(), to.c_str(), amount, SIZE_T(nonce));
}

std::string Wallet::signAndSendTransaction(const std::string &from, const std::string &password, const std::string &to, const BigInt &amount, const BigInt &gas,  const BigInt &gasPrice, size_t nonce)
{
    return signAndSendTransaction(from.c_str(), password.c_str(), to.c_str(), amount, gas, gasPrice, SIZE_T(nonce));
}

std::string Wallet::signAndSendTransaction(const std::string &from, const std::string &password, const std::string &to, const BigInt &amount, const BigInt &gas, size_t nonce)
{
    return signAndSendTransaction(from.c_str(), password.c_str(), to.c_str(), amount, gas, SIZE_T(nonce));
}

std::string Wallet::signAndSendTransaction(const std::string &from, const std::string &password, const std::string &to, const BigInt &amount, const std::string &data, size_t)
{
    return signAndSendTransaction(from.c_str(), password.c_str(), to.c_str(), amount, data.c_str());
}

std::string Wallet::signAndSendTransaction(const std::string &from, const std::string &password, const std::string &to, const BigInt &amount, const std::string &data, const BigInt &gas,  const BigInt &gasPrice, size_t nonce)
{
    return signAndSendTransaction(from.c_str(), password.c_str(), to.c_str(), amount, data.c_str(), gas, gasPrice, SIZE_T(nonce));
}


std::string Wallet::signAndSendTransaction(const std::string &from, const std::string &password, const std::string &to, const BigInt &amount, const std::string &data, const BigInt &gas, size_t nonce)
{
    return signAndSendTransaction(from.c_str(), password.c_str(), to.c_str(), amount, data.c_str(), gas, SIZE_T(nonce));
}

/////

std::string Wallet::sendTransaction(const char *from, const char *to, const BigInt &amount, size_t nonce)
{

    return sendTransactionRequest("eth_sendTransaction", TransactionParamsFactory::makeParams(from, to, amount, SIZE_T(nonce)));
}

std::string Wallet::sendTransaction(const char *from, const char *to, const BigInt &amount, const BigInt &gas, const BigInt &gasPrice, size_t nonce)
{
    return sendTransactionRequest("eth_sendTransaction", TransactionParamsFactory::makeParams(from, to, amount, gas, gasPrice, SIZE_T(nonce)));
}

std::string Wallet::sendTransaction(const char *from, const char *to, const BigInt &amount, const BigInt &gas, size_t nonce)
{
    return sendTransactionRequest("eth_sendTransaction", TransactionParamsFactory::makeParams(from, to, amount, gas, SIZE_T(nonce)));
}


std::string Wallet::sendTransaction(const char *from, const char *to, const BigInt &amount, const char *data, size_t nonce)
{
    return sendTransactionRequest("eth_sendTransaction", TransactionParamsFactory::makeParams(from, to, amount, data, SIZE_T(nonce)));
}

std::string Wallet::sendTransaction(const char *from, const char *to, const BigInt &amount, const char *data, const BigInt &gas, const BigInt &gasPrice, size_t nonce)
{
    return sendTransactionRequest("eth_sendTransaction", TransactionParamsFactory::makeParams(from, to, amount, data, gas, gasPrice, SIZE_T(nonce)));
}

std::string Wallet::sendTransaction(const char *from, const char *to, const BigInt &amount, const char *data, const BigInt &gas, size_t nonce)
{
    return sendTransactionRequest("eth_sendTransaction", TransactionParamsFactory::makeParams(from, to, amount, data, gas, SIZE_T(nonce)));
}

std::string Wallet::sendTransaction(const std::string &from, const std::string &to, const BigInt &amount, size_t nonce)
{
    return sendTransaction(from.c_str(), to.c_str(), amount, SIZE_T(nonce));
}

std::string Wallet::sendTransaction(const std::string &from, const std::string &to, const BigInt &amount, const BigInt &gas,  const BigInt &gasPrice, size_t nonce)
{
    return sendTransaction(from.c_str(), to.c_str(), amount, gas, gasPrice, SIZE_T(nonce));
}

std::string Wallet::sendTransaction(const std::string &from, const std::string &to, const BigInt &amount, const BigInt &gas, size_t nonce)
{
    return sendTransaction(from.c_str(), to.c_str(), amount, gas, SIZE_T(nonce));
}

std::string Wallet::sendTransaction(const std::string &from, const std::string &to, const BigInt &amount, const std::string &data, size_t nonce)
{
    return sendTransaction(from.c_str(), to.c_str(), amount, data.c_str());
}

std::string Wallet::sendTransaction(const std::string &from, const std::string &to, const BigInt &amount, const std::string &data, const BigInt &gas,  const BigInt &gasPrice, size_t nonce)
{
    return sendTransaction(from.c_str(), to.c_str(), amount, data.c_str(), gas, gasPrice, SIZE_T(nonce));
}


std::string Wallet::sendTransaction(const std::string &from, const std::string &to, const BigInt &amount, const std::string &data, const BigInt &gas, size_t nonce)
{
    return sendTransaction(from.c_str(), to.c_str(), amount, data.c_str(), gas, SIZE_T(nonce));
}


std::string Wallet::sendRawTransaction(const char *transaction)
{
    Json::Value result = _provider.request("eth_sendRawTransaction", Arguments(transaction));
    return result.asString();
}

std::string Wallet::sendRawTransaction(const std::string &transaction)
{
    return sendRawTransaction(transaction.c_str());
}


std::string Wallet::sign(const char *account, const char *data)
{
    Json::Value result = _provider.request("eth_sign", Arguments(account, data));
    return result.asString();
}

std::string Wallet::sign(const std::string &account, const std::string &data)
{
    return sign(account.c_str(), data.c_str());
}


inline std::string Wallet::sendTransactionRequest(const char *type, const Arguments &params)
{
    Json::Value result = _provider.request(type, params);
    return result.asString();
}


}}
