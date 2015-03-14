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

#ifndef ___TUserComment_h__
#define ___TUserComment_h__

#include "framework/cdf_common.h"
#include "framework/util/refshared.h"
#include "framework/util/handle.h"
#include "framework/util/datetime.h"
#include "framework/serialize/serializestream.h"
#include "framework/mq/messageblock.h"
#include "framework/mq/messagemanager.h"
#include "vector"
#include "map"
#include "string"
#include "algorithm"

#ifdef CDE_INT_VERSION
#   if CDE_INT_VERSION / 100 != 100
#       error Cde version mismatch!
#   endif
#   if CDE_INT_VERSION % 100 < 1
#       error Cde patch level mismatch!
#   endif
#endif

namespace Message
{
    namespace Db
    {
        namespace Tables
        {
            struct TUserComment
            {
                int commentId;
                int postId;
                int fromUserId;
                int fromNickname;
                std::string content;
                cdf::CDateTime commentDt;

                TUserComment();
                bool operator==(const TUserComment&) const;
                bool operator!=(const TUserComment&) const;
                bool operator<(const TUserComment&) const;
                
                void __init();
                void __write(cdf::CSerializeStream&) const;
                void __read(cdf::CSerializeStream&);
                void __update(const TUserComment&);
            };

            typedef std::vector< ::Message::Db::Tables::TUserComment> SeqTUserComment;

            class __U__SeqTUserComment { };
            void __write(cdf::CSerializeStream&, const SeqTUserComment&, __U__SeqTUserComment);
            void __read(cdf::CSerializeStream&, SeqTUserComment&, __U__SeqTUserComment);
        }
    }
}

#endif
