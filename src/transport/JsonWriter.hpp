#pragma once

#include <json/value.h>
#include <json/writer.h>

#include "debug.hpp"

namespace Eth{



class JsonWriter
{
    public:

        template<class Socket>
        bool write(Socket &, const Json::Value &);

};



}

#include "JsonWriter.ipp"
