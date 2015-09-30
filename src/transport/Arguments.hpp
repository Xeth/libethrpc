#pragma once

#include <json/value.h>


namespace Eth{


class Arguments
{
    public:
        typedef Json::Value::iterator Iterator;
        typedef Json::Value::const_iterator ConstIterator;

    public:
        Arguments();

        template<class T>
        Arguments(const T &);

        template<class T1, class T2>
        Arguments(const T1&, const T2&);

        template<class T1, class T2, class T3>
        Arguments(const T1&, const T2&, const T3&);

        template<class T1, class T2, class T3, class T4>
        Arguments(const T1&, const T2&, const T3&, const T4&);

        template<class T1, class T2, class T3, class T4, class T5>
        Arguments(const T1&, const T2&, const T3&, const T4&, const T5&);

        template<class T>
        void add(const T &);

        void add(uint64_t);
        void add(int64_t);
        void add(uint32_t);
        void add(int32_t);

        size_t size() const;
        ConstIterator begin() const;
        ConstIterator end() const;
        Iterator begin();
        Iterator end();
        Json::Value &toJson();
        const Json::Value &toJson() const;


    private:
        Json::Value _value;
};




}

#include "Arguments.ipp"