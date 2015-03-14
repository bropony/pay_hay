// **********************************************************************
//
// Copyright (c) 2003-2009 CDE, Inc. All rights reserved.
//
// This copy of Cde is licensed to you under the terms described in the
// CDE_LICENSE file included in this distribution.
//
// **********************************************************************

// Cde version 1.0.1
// Generated from file `TErrorCode.cdl'

#include "framework/objectpool/objectpool.h"
#include "TErrorCode.h"

#ifdef CDE_INT_VERSION
#   if CDE_INT_VERSION / 100 != 100
#       error Cde version mismatch!
#   endif
#   if CDE_INT_VERSION % 100 < 1
#       error Cde patch level mismatch!
#   endif
#endif

Message::Db::Tables::TErrorCode::TErrorCode()
{
    __init();
}

bool
Message::Db::Tables::TErrorCode::operator==(const TErrorCode& __rhs) const
{
    return !operator!=(__rhs);
}

bool
Message::Db::Tables::TErrorCode::operator!=(const TErrorCode& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(errorCode != __rhs.errorCode)
    {
        return true;
    }
    if(errorName != __rhs.errorName)
    {
        return true;
    }
    if(errorStr != __rhs.errorStr)
    {
        return true;
    }
    return false;
}

bool
Message::Db::Tables::TErrorCode::operator<(const TErrorCode& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(errorCode < __rhs.errorCode)
    {
        return true;
    }
    else if(__rhs.errorCode < errorCode)
    {
        return false;
    }
    if(errorName < __rhs.errorName)
    {
        return true;
    }
    else if(__rhs.errorName < errorName)
    {
        return false;
    }
    if(errorStr < __rhs.errorStr)
    {
        return true;
    }
    else if(__rhs.errorStr < errorStr)
    {
        return false;
    }
    return false;
}

void
Message::Db::Tables::TErrorCode::__init()
{
    errorCode = 0;
}

void
Message::Db::Tables::TErrorCode::__write(cdf::CSerializeStream& __os) const
{
    __os.write(errorCode);
    __os.write(errorName);
    __os.write(errorStr);
}

void
Message::Db::Tables::TErrorCode::__read(cdf::CSerializeStream& __is)
{
    __is.read(errorCode);
    __is.read(errorName);
    __is.read(errorStr);
}

void
Message::Db::Tables::TErrorCode::__update(const TErrorCode& __rhs)
{
    errorCode = __rhs.errorCode;
    if( errorName != __rhs.errorName ) 
    {
        errorName = __rhs.errorName;
    }
    if( errorStr != __rhs.errorStr ) 
    {
        errorStr = __rhs.errorStr;
    }
}

void
Message::Db::Tables::__write(cdf::CSerializeStream& __os, const ::Message::Db::Tables::SeqTErrorCode& v, ::Message::Db::Tables::__U__SeqTErrorCode)
{
    __os.writeSize(int(v.size()));
    ::Message::Db::Tables::SeqTErrorCode::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        (*p).__write(__os);
    }
}

void
Message::Db::Tables::__read(cdf::CSerializeStream& __is, ::Message::Db::Tables::SeqTErrorCode& v, ::Message::Db::Tables::__U__SeqTErrorCode)
{
    int sz;
    __is.readSize(sz);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
    }
}
