

namespace Eth{


template<class Socket, class Connector>
GenericTransport<Socket, Connector>::GenericTransport() : 
    _socket(_service)
{}

template<class Socket, class Connector>
GenericTransport<Socket, Connector>::GenericTransport(const char *uri):
    _socket(_service)
{
    if(!_connector.connect(_socket, uri))
    {
        std::string error = "Connection to [";
        error+=uri;
        error+="] failed";
        throw std::runtime_error(error);
    }
}

template<class Socket, class Connector>
bool GenericTransport<Socket, Connector>::connect(const char *uri)
{
    return _connector.connect(_socket, uri);
}

template<class Socket, class Connector>
bool GenericTransport<Socket, Connector>::read(Json::Value &message)
{
    return _reader.read(_socket, message);
}

template<class Socket, class Connector>
Json::Value GenericTransport<Socket, Connector>::read()
{
    return _reader.read(_socket);
}

template<class Socket, class Connector>
bool GenericTransport<Socket, Connector>::write(const Json::Value &message)
{
    return _writer.write(_socket, message);
}



template<class Socket, class Connector>
Json::Value GenericTransport<Socket, Connector>::request(Json::Value &msg)
{
    Json::Value response;
    if(!request(msg, response))
    {
        throw std::runtime_error("Failed to send request");
    }
    
    return response;
}

template<class Socket, class Connector>
bool GenericTransport<Socket, Connector>::request(Json::Value &msg, Json::Value &response)
{

    unsigned id = (unsigned)time(NULL);
    msg["id"] = Json::Value(id);
    if(!_writer.write(_socket, msg))
    {
        return false;
    }

    if(!_reader.read(_socket, response))
    {
        return false;
    }

    if(!response["id"]||response["id"].asUInt64()!=id)
    {
        return false;
    }

    if(response.isMember("error"))
    {
        return false;
    }

    response = response["result"];

    return true;
}

template<class Socket, class Connector>
bool GenericTransport<Socket, Connector>::request(const char *method, const Arguments &args, Json::Value &result)
{
   Json::Value message;
   RequestEncoder encoder;
   encoder.encode(method, args,  message);
   return request(message, result);
}

template<class Socket, class Connector>
Json::Value GenericTransport<Socket, Connector>::request(const char *method, const Arguments &args)
{
    Json::Value result;
    if(!request(method, args, result))
    {
        throw std::runtime_error("failed to send request");
    }
    return result;
}

template<class Socket, class Connector>
bool GenericTransport<Socket, Connector>::request(const char *method, Json::Value &result)
{
   Json::Value message;
   RequestEncoder encoder;
   encoder.encode(method,  message);
   return request(message, result);
}

template<class Socket, class Connector>
Json::Value GenericTransport<Socket, Connector>::request(const char *method)
{
    Json::Value result;
    if(!request(method, result))
    {
        throw std::runtime_error("failed to send request");
    }
    return result;
}

template<class Socket, class Connector>
Json::Value GenericTransport<Socket, Connector>::request(const char *method, const Json::Value &params)
{
   RequestEncoder encoder;
   Json::Value message = encoder.encode(method, params);
   return request(message);
}

template<class Socket, class Connector>
bool GenericTransport<Socket, Connector>::isConnected() const
{
    return _socket.is_open();
}


}
