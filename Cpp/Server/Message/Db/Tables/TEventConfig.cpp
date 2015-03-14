// **********************************************************************
//
// Copyright (c) 2003-2009 CDE, Inc. All rights reserved.
//
// This copy of Cde is licensed to you under the terms described in the
// CDE_LICENSE file included in this distribution.
//
// **********************************************************************

// Cde version 1.0.1
// Generated from file `TEventConfig.cdl'

#include "framework/objectpool/objectpool.h"
#include "TEventConfig.h"

#ifdef CDE_INT_VERSION
#   if CDE_INT_VERSION / 100 != 100
#       error Cde version mismatch!
#   endif
#   if CDE_INT_VERSION % 100 < 1
#       error Cde patch level mismatch!
#   endif
#endif

Message::Db::Tables::TEventConfig::TEventConfig()
{
    __init();
}

bool
Message::Db::Tables::TEventConfig::operator==(const TEventConfig& __rhs) const
{
    return !operator!=(__rhs);
}

bool
Message::Db::Tables::TEventConfig::operator!=(const TEventConfig& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(eventId != __rhs.eventId)
    {
        return true;
    }
    if(event != __rhs.event)
    {
        return true;
    }
    if(inParams != __rhs.inParams)
    {
        return true;
    }
    if(outParams != __rhs.outParams)
    {
        return true;
    }
    return false;
}

bool
Message::Db::Tables::TEventConfig::operator<(const TEventConfig& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(eventId < __rhs.eventId)
    {
        return true;
    }
    else if(__rhs.eventId < eventId)
    {
        return false;
    }
    if(event < __rhs.event)
    {
        return true;
    }
    else if(__rhs.event < event)
    {
        return false;
    }
    if(inParams < __rhs.inParams)
    {
        return true;
    }
    else if(__rhs.inParams < inParams)
    {
        return false;
    }
    if(outParams < __rhs.outParams)
    {
        return true;
    }
    else if(__rhs.outParams < outParams)
    {
        return false;
    }
    return false;
}

void
Message::Db::Tables::TEventConfig::__init()
{
    eventId = 0;
}

void
Message::Db::Tables::TEventConfig::__write(cdf::CSerializeStream& __os) const
{
    __os.write(eventId);
    __os.write(event);
    __os.write(inParams);
    __os.write(outParams);
}

void
Message::Db::Tables::TEventConfig::__read(cdf::CSerializeStream& __is)
{
    __is.read(eventId);
    __is.read(event);
    __is.read(inParams);
    __is.read(outParams);
}

void
Message::Db::Tables::TEventConfig::__update(const TEventConfig& __rhs)
{
    eventId = __rhs.eventId;
    if( event != __rhs.event ) 
    {
        event = __rhs.event;
    }
    if( inParams != __rhs.inParams ) 
    {
        inParams = __rhs.inParams;
    }
    if( outParams != __rhs.outParams ) 
    {
        outParams = __rhs.outParams;
    }
}

void
Message::Db::Tables::__write(cdf::CSerializeStream& __os, const ::Message::Db::Tables::SeqTEventConfig& v, ::Message::Db::Tables::__U__SeqTEventConfig)
{
    __os.writeSize(int(v.size()));
    ::Message::Db::Tables::SeqTEventConfig::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        (*p).__write(__os);
    }
}

void
Message::Db::Tables::__read(cdf::CSerializeStream& __is, ::Message::Db::Tables::SeqTEventConfig& v, ::Message::Db::Tables::__U__SeqTEventConfig)
{
    int sz;
    __is.readSize(sz);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
    }
}
