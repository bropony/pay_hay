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

#ifndef ___TUserPost_h__
#define ___TUserPost_h__

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
            struct TUserPost
            {
                int postId;
                int userId;
                std::string title;
                std::string content;
                std::string imgList;
                std::string imgStatus;
                int nlike;
                int ndislike;
                int ncomment;
                cdf::CDateTime postDt;

                TUserPost();
                bool operator==(const TUserPost&) const;
                bool operator!=(const TUserPost&) const;
                bool operator<(const TUserPost&) const;
                
                void __init();
                void __write(cdf::CSerializeStream&) const;
                void __read(cdf::CSerializeStream&);
                void __update(const TUserPost&);
            };

            typedef std::vector< ::Message::Db::Tables::TUserPost> SeqTUserPost;

            class __U__SeqTUserPost { };
            void __write(cdf::CSerializeStream&, const SeqTUserPost&, __U__SeqTUserPost);
            void __read(cdf::CSerializeStream&, SeqTUserPost&, __U__SeqTUserPost);
        }
    }
}

#endif
