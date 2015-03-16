// **********************************************************************
//
// Copyright (c) 2003-2009 CDE, Inc. All rights reserved.
//
// This copy of Cde is licensed to you under the terms described in the
// CDE_LICENSE file included in this distribution.
//
// **********************************************************************

// Cde version 1.0.1
// Generated from file `TUserComment.cdl'

#include "framework/objectpool/objectpool.h"
#include "TUserComment.h"

#ifdef CDE_INT_VERSION
#   if CDE_INT_VERSION / 100 != 100
#       error Cde version mismatch!
#   endif
#   if CDE_INT_VERSION % 100 < 1
#       error Cde patch level mismatch!
#   endif
#endif

Message::Db::Tables::TUserComment::TUserComment()
{
    __init();
}

bool
Message::Db::Tables::TUserComment::operator==(const TUserComment& __rhs) const
{
    return !operator!=(__rhs);
}

bool
Message::Db::Tables::TUserComment::operator!=(const TUserComment& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(commentId != __rhs.commentId)
    {
        return true;
    }
    if(postId != __rhs.postId)
    {
        return true;
    }
    if(fromUserId != __rhs.fromUserId)
    {
        return true;
    }
    if(fromNickname != __rhs.fromNickname)
    {
        return true;
    }
    if(content != __rhs.content)
    {
        return true;
    }
    if(commentDt != __rhs.commentDt)
    {
        return true;
    }
    return false;
}

bool
Message::Db::Tables::TUserComment::operator<(const TUserComment& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(commentId < __rhs.commentId)
    {
        return true;
    }
    else if(__rhs.commentId < commentId)
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
    if(fromUserId < __rhs.fromUserId)
    {
        return true;
    }
    else if(__rhs.fromUserId < fromUserId)
    {
        return false;
    }
    if(fromNickname < __rhs.fromNickname)
    {
        return true;
    }
    else if(__rhs.fromNickname < fromNickname)
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
    if(commentDt < __rhs.commentDt)
    {
        return true;
    }
    else if(__rhs.commentDt < commentDt)
    {
        return false;
    }
    return false;
}

void
Message::Db::Tables::TUserComment::__init()
{
    commentId = 0;
    postId = 0;
    fromUserId = 0;
}

void
Message::Db::Tables::TUserComment::__write(cdf::CSerializeStream& __os) const
{
    __os.write(commentId);
    __os.write(postId);
    __os.write(fromUserId);
    __os.write(fromNickname);
    __os.write(content);
    __os.write(commentDt);
}

void
Message::Db::Tables::TUserComment::__read(cdf::CSerializeStream& __is)
{
    __is.read(commentId);
    __is.read(postId);
    __is.read(fromUserId);
    __is.read(fromNickname);
    __is.read(content);
    __is.read(commentDt);
}

void
Message::Db::Tables::TUserComment::__update(const TUserComment& __rhs)
{
    commentId = __rhs.commentId;
    postId = __rhs.postId;
    fromUserId = __rhs.fromUserId;
    if( fromNickname != __rhs.fromNickname ) 
    {
        fromNickname = __rhs.fromNickname;
    }
    if( content != __rhs.content ) 
    {
        content = __rhs.content;
    }
    commentDt = __rhs.commentDt;
}

void
Message::Db::Tables::__write(cdf::CSerializeStream& __os, const ::Message::Db::Tables::SeqTUserComment& v, ::Message::Db::Tables::__U__SeqTUserComment)
{
    __os.writeSize(int(v.size()));
    ::Message::Db::Tables::SeqTUserComment::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        (*p).__write(__os);
    }
}

void
Message::Db::Tables::__read(cdf::CSerializeStream& __is, ::Message::Db::Tables::SeqTUserComment& v, ::Message::Db::Tables::__U__SeqTUserComment)
{
    int sz;
    __is.readSize(sz);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
    }
}
