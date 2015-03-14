// **********************************************************************
//
// Copyright (c) 2003-2009 CDE, Inc. All rights reserved.
//
// This copy of Cde is licensed to you under the terms described in the
// CDE_LICENSE file included in this distribution.
//
// **********************************************************************

// Cde version 1.0.1
// Generated from file `TStructConfig.cdl'

#include "framework/objectpool/objectpool.h"
#include "TStructConfig.h"

#ifdef CDE_INT_VERSION
#   if CDE_INT_VERSION / 100 != 100
#       error Cde version mismatch!
#   endif
#   if CDE_INT_VERSION % 100 < 1
#       error Cde patch level mismatch!
#   endif
#endif

Message::Db::Tables::TStructConfig::TStructConfig()
{
    __init();
}

bool
Message::Db::Tables::TStructConfig::operator==(const TStructConfig& __rhs) const
{
    return !operator!=(__rhs);
}

bool
Message::Db::Tables::TStructConfig::operator!=(const TStructConfig& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(name != __rhs.name)
    {
        return true;
    }
    if(type != __rhs.type)
    {
        return true;
    }
    if(fields != __rhs.fields)
    {
        return true;
    }
    if(descr != __rhs.descr)
    {
        return true;
    }
    return false;
}

bool
Message::Db::Tables::TStructConfig::operator<(const TStructConfig& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(name < __rhs.name)
    {
        return true;
    }
    else if(__rhs.name < name)
    {
        return false;
    }
    if(type < __rhs.type)
    {
        return true;
    }
    else if(__rhs.type < type)
    {
        return false;
    }
    if(fields < __rhs.fields)
    {
        return true;
    }
    else if(__rhs.fields < fields)
    {
        return false;
    }
    if(descr < __rhs.descr)
    {
        return true;
    }
    else if(__rhs.descr < descr)
    {
        return false;
    }
    return false;
}

void
Message::Db::Tables::TStructConfig::__init()
{
    type = 0;
}

void
Message::Db::Tables::TStructConfig::__write(cdf::CSerializeStream& __os) const
{
    __os.write(name);
    __os.write(type);
    __os.write(fields);
    __os.write(descr);
}

void
Message::Db::Tables::TStructConfig::__read(cdf::CSerializeStream& __is)
{
    __is.read(name);
    __is.read(type);
    __is.read(fields);
    __is.read(descr);
}

void
Message::Db::Tables::TStructConfig::__update(const TStructConfig& __rhs)
{
    if( name != __rhs.name ) 
    {
        name = __rhs.name;
    }
    type = __rhs.type;
    if( fields != __rhs.fields ) 
    {
        fields = __rhs.fields;
    }
    if( descr != __rhs.descr ) 
    {
        descr = __rhs.descr;
    }
}

void
Message::Db::Tables::__write(cdf::CSerializeStream& __os, const ::Message::Db::Tables::SeqTStructConfig& v, ::Message::Db::Tables::__U__SeqTStructConfig)
{
    __os.writeSize(int(v.size()));
    ::Message::Db::Tables::SeqTStructConfig::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        (*p).__write(__os);
    }
}

void
Message::Db::Tables::__read(cdf::CSerializeStream& __is, ::Message::Db::Tables::SeqTStructConfig& v, ::Message::Db::Tables::__U__SeqTStructConfig)
{
    int sz;
    __is.readSize(sz);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
    }
}
