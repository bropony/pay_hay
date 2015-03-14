// **********************************************************************
//
// Copyright (c) 2003-2009 CDE, Inc. All rights reserved.
//
// This copy of Cde is licensed to you under the terms described in the
// CDE_LICENSE file included in this distribution.
//
// **********************************************************************

// Cde version 1.0.1
// Generated from file `TUserPost.cdl'

#include "framework/objectpool/objectpool.h"
#include "TUserPost.h"

#ifdef CDE_INT_VERSION
#   if CDE_INT_VERSION / 100 != 100
#       error Cde version mismatch!
#   endif
#   if CDE_INT_VERSION % 100 < 1
#       error Cde patch level mismatch!
#   endif
#endif

Message::Db::Tables::TUserPost::TUserPost()
{
    __init();
}

bool
Message::Db::Tables::TUserPost::operator==(const TUserPost& __rhs) const
{
    return !operator!=(__rhs);
}

bool
Message::Db::Tables::TUserPost::operator!=(const TUserPost& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(postId != __rhs.postId)
    {
        return true;
    }
    if(userId != __rhs.userId)
    {
        return true;
    }
    if(title != __rhs.title)
    {
        return true;
    }
    if(content != __rhs.content)
    {
        return true;
    }
    if(imgList != __rhs.imgList)
    {
        return true;
    }
    if(nlike != __rhs.nlike)
    {
        return true;
    }
    if(ndislike != __rhs.ndislike)
    {
        return true;
    }
    if(ncomment != __rhs.ncomment)
    {
        return true;
    }
    if(postDt != __rhs.postDt)
    {
        return true;
    }
    return false;
}

bool
Message::Db::Tables::TUserPost::operator<(const TUserPost& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(postId < __rhs.postId)
    {
        return true;
    }
    else if(__rhs.postId < postId)
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
    if(title < __rhs.title)
    {
        return true;
    }
    else if(__rhs.title < title)
    {
        return false;
    }
    if(content < __rhs.content)
    {
        return true;
    }
    else if(__rhs.content < content)
    {
        return false;
    }
    if(imgList < __rhs.imgList)
    {
        return true;
    }
    else if(__rhs.imgList < imgList)
    {
        return false;
    }
    if(nlike < __rhs.nlike)
    {
        return true;
    }
    else if(__rhs.nlike < nlike)
    {
        return false;
    }
    if(ndislike < __rhs.ndislike)
    {
        return true;
    }
    else if(__rhs.ndislike < ndislike)
    {
        return false;
    }
    if(ncomment < __rhs.ncomment)
    {
        return true;
    }
    else if(__rhs.ncomment < ncomment)
    {
        return false;
    }
    if(postDt < __rhs.postDt)
    {
        return true;
    }
    else if(__rhs.postDt < postDt)
    {
        return false;
    }
    return false;
}

void
Message::Db::Tables::TUserPost::__init()
{
    postId = 0;
    userId = 0;
    nlike = 0;
    ndislike = 0;
    ncomment = 0;
}

void
Message::Db::Tables::TUserPost::__write(cdf::CSerializeStream& __os) const
{
    __os.write(postId);
    __os.write(userId);
    __os.write(title);
    __os.write(content);
    __os.write(imgList);
    __os.write(nlike);
    __os.write(ndislike);
    __os.write(ncomment);
    __os.write(postDt);
}

void
Message::Db::Tables::TUserPost::__read(cdf::CSerializeStream& __is)
{
    __is.read(postId);
    __is.read(userId);
    __is.read(title);
    __is.read(content);
    __is.read(imgList);
    __is.read(nlike);
    __is.read(ndislike);
    __is.read(ncomment);
    __is.read(postDt);
}

void
Message::Db::Tables::TUserPost::__update(const TUserPost& __rhs)
{
    postId = __rhs.postId;
    userId = __rhs.userId;
    if( title != __rhs.title ) 
    {
        title = __rhs.title;
    }
    if( content != __rhs.content ) 
    {
        content = __rhs.content;
    }
    if( imgList != __rhs.imgList ) 
    {
        imgList = __rhs.imgList;
    }
    nlike = __rhs.nlike;
    ndislike = __rhs.ndislike;
    ncomment = __rhs.ncomment;
    postDt = __rhs.postDt;
}

void
Message::Db::Tables::__write(cdf::CSerializeStream& __os, const ::Message::Db::Tables::SeqTUserPost& v, ::Message::Db::Tables::__U__SeqTUserPost)
{
    __os.writeSize(int(v.size()));
    ::Message::Db::Tables::SeqTUserPost::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        (*p).__write(__os);
    }
}

void
Message::Db::Tables::__read(cdf::CSerializeStream& __is, ::Message::Db::Tables::SeqTUserPost& v, ::Message::Db::Tables::__U__SeqTUserPost)
{
    int sz;
    __is.readSize(sz);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
    }
}
