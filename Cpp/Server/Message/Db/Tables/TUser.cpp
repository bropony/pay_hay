// **********************************************************************
//
// Copyright (c) 2003-2009 CDE, Inc. All rights reserved.
//
// This copy of Cde is licensed to you under the terms described in the
// CDE_LICENSE file included in this distribution.
//
// **********************************************************************

// Cde version 1.0.1
// Generated from file `TUser.cdl'

#include "framework/objectpool/objectpool.h"
#include "TUser.h"

#ifdef CDE_INT_VERSION
#   if CDE_INT_VERSION / 100 != 100
#       error Cde version mismatch!
#   endif
#   if CDE_INT_VERSION % 100 < 1
#       error Cde patch level mismatch!
#   endif
#endif

Message::Db::Tables::TUser::TUser()
{
    __init();
}

bool
Message::Db::Tables::TUser::operator==(const TUser& __rhs) const
{
    return !operator!=(__rhs);
}

bool
Message::Db::Tables::TUser::operator!=(const TUser& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(userId != __rhs.userId)
    {
        return true;
    }
    if(account != __rhs.account)
    {
        return true;
    }
    if(nickname != __rhs.nickname)
    {
        return true;
    }
    if(loginKey != __rhs.loginKey)
    {
        return true;
    }
    if(createDt != __rhs.createDt)
    {
        return true;
    }
    return false;
}

bool
Message::Db::Tables::TUser::operator<(const TUser& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(userId < __rhs.userId)
    {
        return true;
    }
    else if(__rhs.userId < userId)
    {
        return false;
    }
    if(account < __rhs.account)
    {
        return true;
    }
    else if(__rhs.account < account)
    {
        return false;
    }
    if(nickname < __rhs.nickname)
    {
        return true;
    }
    else if(__rhs.nickname < nickname)
    {
        return false;
    }
    if(loginKey < __rhs.loginKey)
    {
        return true;
    }
    else if(__rhs.loginKey < loginKey)
    {
        return false;
    }
    if(createDt < __rhs.createDt)
    {
        return true;
    }
    else if(__rhs.createDt < createDt)
    {
        return false;
    }
    return false;
}

void
Message::Db::Tables::TUser::__init()
{
    userId = 0;
}

void
Message::Db::Tables::TUser::__write(cdf::CSerializeStream& __os) const
{
    __os.write(userId);
    __os.write(account);
    __os.write(nickname);
    __os.write(loginKey);
    __os.write(createDt);
}

void
Message::Db::Tables::TUser::__read(cdf::CSerializeStream& __is)
{
    __is.read(userId);
    __is.read(account);
    __is.read(nickname);
    __is.read(loginKey);
    __is.read(createDt);
}

void
Message::Db::Tables::TUser::__update(const TUser& __rhs)
{
    userId = __rhs.userId;
    if( account != __rhs.account ) 
    {
        account = __rhs.account;
    }
    if( nickname != __rhs.nickname ) 
    {
        nickname = __rhs.nickname;
    }
    if( loginKey != __rhs.loginKey ) 
    {
        loginKey = __rhs.loginKey;
    }
    createDt = __rhs.createDt;
}

void
Message::Db::Tables::__write(cdf::CSerializeStream& __os, const ::Message::Db::Tables::SeqTUser& v, ::Message::Db::Tables::__U__SeqTUser)
{
    __os.writeSize(int(v.size()));
    ::Message::Db::Tables::SeqTUser::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        (*p).__write(__os);
    }
}

void
Message::Db::Tables::__read(cdf::CSerializeStream& __is, ::Message::Db::Tables::SeqTUser& v, ::Message::Db::Tables::__U__SeqTUser)
{
    int sz;
    __is.readSize(sz);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
    }
}
