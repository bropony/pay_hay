// **********************************************************************
//
// Copyright (c) 2003-2009 CDE, Inc. All rights reserved.
//
// This copy of Cde is licensed to you under the terms described in the
// CDE_LICENSE file included in this distribution.
//
// **********************************************************************

// Cde version 1.0.1
// Generated from file `TUserImg.cdl'

#include "framework/objectpool/objectpool.h"
#include "TUserImg.h"

#ifdef CDE_INT_VERSION
#   if CDE_INT_VERSION / 100 != 100
#       error Cde version mismatch!
#   endif
#   if CDE_INT_VERSION % 100 < 1
#       error Cde patch level mismatch!
#   endif
#endif

Message::Db::Tables::TUserImg::TUserImg()
{
    __init();
}

bool
Message::Db::Tables::TUserImg::operator==(const TUserImg& __rhs) const
{
    return !operator!=(__rhs);
}

bool
Message::Db::Tables::TUserImg::operator!=(const TUserImg& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(imgId != __rhs.imgId)
    {
        return true;
    }
    if(imgPath != __rhs.imgPath)
    {
        return true;
    }
    if(shortDesc != __rhs.shortDesc)
    {
        return true;
    }
    return false;
}

bool
Message::Db::Tables::TUserImg::operator<(const TUserImg& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(imgId < __rhs.imgId)
    {
        return true;
    }
    else if(__rhs.imgId < imgId)
    {
        return false;
    }
    if(imgPath < __rhs.imgPath)
    {
        return true;
    }
    else if(__rhs.imgPath < imgPath)
    {
        return false;
    }
    if(shortDesc < __rhs.shortDesc)
    {
        return true;
    }
    else if(__rhs.shortDesc < shortDesc)
    {
        return false;
    }
    return false;
}

void
Message::Db::Tables::TUserImg::__init()
{
    imgId = 0;
}

void
Message::Db::Tables::TUserImg::__write(cdf::CSerializeStream& __os) const
{
    __os.write(imgId);
    __os.write(imgPath);
    __os.write(shortDesc);
}

void
Message::Db::Tables::TUserImg::__read(cdf::CSerializeStream& __is)
{
    __is.read(imgId);
    __is.read(imgPath);
    __is.read(shortDesc);
}

void
Message::Db::Tables::TUserImg::__update(const TUserImg& __rhs)
{
    imgId = __rhs.imgId;
    if( imgPath != __rhs.imgPath ) 
    {
        imgPath = __rhs.imgPath;
    }
    if( shortDesc != __rhs.shortDesc ) 
    {
        shortDesc = __rhs.shortDesc;
    }
}

void
Message::Db::Tables::__write(cdf::CSerializeStream& __os, const ::Message::Db::Tables::SeqTUserImg& v, ::Message::Db::Tables::__U__SeqTUserImg)
{
    __os.writeSize(int(v.size()));
    ::Message::Db::Tables::SeqTUserImg::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        (*p).__write(__os);
    }
}

void
Message::Db::Tables::__read(cdf::CSerializeStream& __is, ::Message::Db::Tables::SeqTUserImg& v, ::Message::Db::Tables::__U__SeqTUserImg)
{
    int sz;
    __is.readSize(sz);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
    }
}
