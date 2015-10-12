
#include "Provider.hpp"
#include "transport/RequestEncoder.hpp"

namespace Eth{

Provider::Provider(const char *uri, size_t retryLimit, size_t retryInterval): 
    _retryLimit(retryLimit),
    _retryInterval(retryInterval)
{
    if(!connect(uri))
    {
        throw std::runtime_error("failed to connect");
    }
}

Provider::Provider(size_t retryLimit, size_t retryInterval) : 
    _retryLimit(retryLimit),
    _retryInterval(retryInterval)
{}


bool Provider::connect(const char *uri)
{
    if(!strncmp(uri, "ipc:", 4))
    {
        uri+=4;
        if(uri[0]=='/' && uri[1] =='/')
        {
            uri++;
        }
        _uri = uri;
        _connection.reset(new ConnectionAdapter<IpcTransport>);
        return _connection->connect(uri);
    }
    else
    {
        throw std::runtime_error("Protocol not implemented");
    }
}

Json::Value Provider::request(Json::Value &request)
{
    Json::Value result;
    if(!_connection->request(request, result))
    {
        throw std::runtime_error("request failed");
    }
    return result;
}


bool Provider::request(const char *method, const Arguments &args, Json::Value &result)
{
    Json::Value message;
    RequestEncoder encoder;
    encoder.encode(method, args, message);
    return request(message, result);
}



Json::Value Provider::request(const char *method, const Arguments &args)
{
    Json::Value result;
    if(!request(method, args, result))
    {
        throw std::runtime_error("rpc request failed");
    }
    return result;
}


bool Provider::request(Json::Value &request, Json::Value &response)
{
    if(!_connection->request(request, response))
    {
        size_t errors = 1;

        while(errors <= _retryLimit)
        {

            LOG_DEBUG("request failed, retrying in "<<_retryInterval);

            if(_retryInterval)
            {
                sleep(_retryInterval);
            }
            
            if(_connection->connect(_uri.c_str()))
            {
                if(_connection->request(request, response))
                {
                    return true;
                }
                else
                {
                    LOG_DEBUG("failed to send request");
                }
            }
            else
            {
                LOG_DEBUG("failed to re-establish connection to : "<<_uri.c_str());
            }
            
            errors++;
        }

        LOG_DEBUG("request failed, too many errors : "<<errors);

        return false;
    }

    return true;
}

bool Provider::request(const char *method, Json::Value &response)
{
    RequestEncoder encoder;
    Json::Value request = encoder.encode(method);
    return _connection->request(request, response);
}

bool Provider::request(const char *method, const Json::Value &params, Json::Value &result)
{
    RequestEncoder encoder;
    Json::Value request = encoder.encode(method, params);
    return _connection->request(request, result);
}

Json::Value Provider::request(const char *method)
{
    Json::Value result;
    if(!request(method, result))
    {
        throw std::runtime_error("failed to send request");
    }
    return result;
}

bool Provider::isEmpty() const
{
    return !_connection;
}


bool Provider::isConnected() const
{
    return (bool)_connection && _connection->isConnected();
}

template<class Transport>
Provider::ConnectionAdapter<Transport>::ConnectionAdapter(const char *uri) : _transport(uri)
{}

template<class Transport>
Provider::ConnectionAdapter<Transport>::ConnectionAdapter()
{}


template<class Transport>
bool Provider::ConnectionAdapter<Transport>::request(Json::Value &request, Json::Value &response)
{
    return _transport.request(request, response);
}

template<class Transport>
bool Provider::ConnectionAdapter<Transport>::isConnected() const
{
    return _transport.isConnected();
}

template<class Transport>
bool Provider::ConnectionAdapter<Transport>::connect(const char *uri)
{
    return _transport.connect(uri);
}


}
