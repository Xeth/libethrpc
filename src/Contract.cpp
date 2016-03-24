#include "Contract.hpp"

#ifdef __ABI_ENABLED__

namespace Ethereum{namespace Connector{


Contract::Contract(Provider &provider, const std::string &address) : 
    Base(address, ContractInvoker(provider))
{}


void Contract::setSenderAddress(const std::string &sender)
{
    getInvoker().setSenderAddress(sender);
}

ContractInvoker::ContractInvoker(Provider &provider) : 
    _provider(provider)
{}


void ContractInvoker::setSenderAddress(const std::string &sender)
{
    _sender = sender;
}



std::string ContractInvoker::execute(const std::string &from, const std::string &to, const std::string &code)
{
    GasEstimator estimator(_provider);
    BigInt gas = estimator.estimate(from, to, BigInt(0), code);
    Json::Value result = _provider.request("eth_sendTransaction", TransactionParamsFactory::makeParams(from.c_str(), to.c_str(), BigInt(0), code.c_str(), gas, 0));
    return result.asString();
}

std::string ContractInvoker::execute(const std::string &to, const std::string &code)
{
    return execute(_sender.size()?_sender:getDefaultAddress(), to, code);
}



std::string ContractInvoker::call(const std::string &to, const std::string &code)
{
    return call(_sender.size()?_sender:getDefaultAddress(), to, code);
}


std::string ContractInvoker::call(const std::string &from, const std::string &to, const std::string &code)
{
    Json::Value result = _provider.request("eth_call", TransactionParamsFactory::makeParams(from.c_str(), to.c_str(), BigInt(0), code.c_str(), 0));
    return result.asString();
}


std::string ContractInvoker::getDefaultAddress()
{
    Json::Value result = _provider.request("eth_coinbase");
    return result.asString();
}



}}

#endif