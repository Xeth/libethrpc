

namespace Eth{




template<class Socket>
bool JsonWriter::write(Socket &socket, const Json::Value &json)
{
    Json::FastWriter writer;
    std::string data = writer.write(json);
    size_t size = data.size();
    size_t sent = boost::asio::write(socket, boost::asio::buffer(data.c_str(), size));
    if(sent<size)
    {
        return false;
    }
    
    return true;
}


}