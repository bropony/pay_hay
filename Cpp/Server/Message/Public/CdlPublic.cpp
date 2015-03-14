// **********************************************************************
//
// Copyright (c) 2003-2009 CDE, Inc. All rights reserved.
//
// This copy of Cde is licensed to you under the terms described in the
// CDE_LICENSE file included in this distribution.
//
// **********************************************************************

// Cde version 1.0.1
// Generated from file `CdlPublic.cdl'

#include "framework/objectpool/objectpool.h"
#include "Message/Public/CdlPublic.h"

#ifdef CDE_INT_VERSION
#   if CDE_INT_VERSION / 100 != 100
#       error Cde version mismatch!
#   endif
#   if CDE_INT_VERSION % 100 < 1
#       error Cde patch level mismatch!
#   endif
#endif

void
Message::Public::__write(cdf::CSerializeStream& __os, const ::Message::Public::DictIntInt& v, ::Message::Public::__U__DictIntInt)
{
    __os.writeSize(int(v.size()));
    ::Message::Public::DictIntInt::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        __os.write(p->first);
        __os.write(p->second);
    }
}

void
Message::Public::__read(cdf::CSerializeStream& __is, ::Message::Public::DictIntInt& v, ::Message::Public::__U__DictIntInt)
{
    int sz;
    __is.readSize(sz);
    while(sz--)
    {
        ::std::pair<const int, int> pair;
        __is.read(const_cast<int&>(pair.first));
        ::Message::Public::DictIntInt::iterator __i = v.insert(v.end(), pair);
        __is.read(__i->second);
    }
}

void
Message::Public::__write(cdf::CSerializeStream& __os, const ::Message::Public::DictLongInt& v, ::Message::Public::__U__DictLongInt)
{
    __os.writeSize(int(v.size()));
    ::Message::Public::DictLongInt::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        __os.write(p->first);
        __os.write(p->second);
    }
}

void
Message::Public::__read(cdf::CSerializeStream& __is, ::Message::Public::DictLongInt& v, ::Message::Public::__U__DictLongInt)
{
    int sz;
    __is.readSize(sz);
    while(sz--)
    {
        ::std::pair<const long64_t, int> pair;
        __is.read(const_cast<long64_t&>(pair.first));
        ::Message::Public::DictLongInt::iterator __i = v.insert(v.end(), pair);
        __is.read(__i->second);
    }
}

void
Message::Public::__write(cdf::CSerializeStream& __os, const ::Message::Public::DictIntStr& v, ::Message::Public::__U__DictIntStr)
{
    __os.writeSize(int(v.size()));
    ::Message::Public::DictIntStr::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        __os.write(p->first);
        __os.write(p->second);
    }
}

void
Message::Public::__read(cdf::CSerializeStream& __is, ::Message::Public::DictIntStr& v, ::Message::Public::__U__DictIntStr)
{
    int sz;
    __is.readSize(sz);
    while(sz--)
    {
        ::std::pair<const int, std::string> pair;
        __is.read(const_cast<int&>(pair.first));
        ::Message::Public::DictIntStr::iterator __i = v.insert(v.end(), pair);
        __is.read(__i->second);
    }
}

void
Message::Public::__write(cdf::CSerializeStream& __os, const ::Message::Public::DictStrInt& v, ::Message::Public::__U__DictStrInt)
{
    __os.writeSize(int(v.size()));
    ::Message::Public::DictStrInt::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        __os.write(p->first);
        __os.write(p->second);
    }
}

void
Message::Public::__read(cdf::CSerializeStream& __is, ::Message::Public::DictStrInt& v, ::Message::Public::__U__DictStrInt)
{
    int sz;
    __is.readSize(sz);
    while(sz--)
    {
        ::std::pair<const std::string, int> pair;
        __is.read(const_cast<std::string&>(pair.first));
        ::Message::Public::DictStrInt::iterator __i = v.insert(v.end(), pair);
        __is.read(__i->second);
    }
}

void
Message::Public::__write(cdf::CSerializeStream& __os, const ::Message::Public::DictIntBool& v, ::Message::Public::__U__DictIntBool)
{
    __os.writeSize(int(v.size()));
    ::Message::Public::DictIntBool::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        __os.write(p->first);
        __os.write(p->second);
    }
}

void
Message::Public::__read(cdf::CSerializeStream& __is, ::Message::Public::DictIntBool& v, ::Message::Public::__U__DictIntBool)
{
    int sz;
    __is.readSize(sz);
    while(sz--)
    {
        ::std::pair<const int, bool> pair;
        __is.read(const_cast<int&>(pair.first));
        ::Message::Public::DictIntBool::iterator __i = v.insert(v.end(), pair);
        __is.read(__i->second);
    }
}

void
Message::Public::__write(cdf::CSerializeStream& __os, const ::Message::Public::DictIntDate& v, ::Message::Public::__U__DictIntDate)
{
    __os.writeSize(int(v.size()));
    ::Message::Public::DictIntDate::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        __os.write(p->first);
        __os.write(p->second);
    }
}

void
Message::Public::__read(cdf::CSerializeStream& __is, ::Message::Public::DictIntDate& v, ::Message::Public::__U__DictIntDate)
{
    int sz;
    __is.readSize(sz);
    while(sz--)
    {
        ::std::pair<const int, cdf::CDateTime> pair;
        __is.read(const_cast<int&>(pair.first));
        ::Message::Public::DictIntDate::iterator __i = v.insert(v.end(), pair);
        __is.read(__i->second);
    }
}

void
Message::Public::__write(cdf::CSerializeStream& __os, const ::Message::Public::DictStrBool& v, ::Message::Public::__U__DictStrBool)
{
    __os.writeSize(int(v.size()));
    ::Message::Public::DictStrBool::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        __os.write(p->first);
        __os.write(p->second);
    }
}

void
Message::Public::__read(cdf::CSerializeStream& __is, ::Message::Public::DictStrBool& v, ::Message::Public::__U__DictStrBool)
{
    int sz;
    __is.readSize(sz);
    while(sz--)
    {
        ::std::pair<const std::string, bool> pair;
        __is.read(const_cast<std::string&>(pair.first));
        ::Message::Public::DictStrBool::iterator __i = v.insert(v.end(), pair);
        __is.read(__i->second);
    }
}

void
Message::Public::__write(cdf::CSerializeStream& __os, const ::Message::Public::DictStrStr& v, ::Message::Public::__U__DictStrStr)
{
    __os.writeSize(int(v.size()));
    ::Message::Public::DictStrStr::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        __os.write(p->first);
        __os.write(p->second);
    }
}

void
Message::Public::__read(cdf::CSerializeStream& __is, ::Message::Public::DictStrStr& v, ::Message::Public::__U__DictStrStr)
{
    int sz;
    __is.readSize(sz);
    while(sz--)
    {
        ::std::pair<const std::string, std::string> pair;
        __is.read(const_cast<std::string&>(pair.first));
        ::Message::Public::DictStrStr::iterator __i = v.insert(v.end(), pair);
        __is.read(__i->second);
    }
}
