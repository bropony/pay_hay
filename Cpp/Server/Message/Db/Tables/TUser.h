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

#ifndef ___TUser_h__
#define ___TUser_h__

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
            struct TUser
            {
                int userId;
                std::string account;
                std::string nickname;
                std::string loginKey;
                int avatar;
                cdf::CDateTime createDt;

                TUser();
                bool operator==(const TUser&) const;
                bool operator!=(const TUser&) const;
                bool operator<(const TUser&) const;
                
                void __init();
                void __write(cdf::CSerializeStream&) const;
                void __read(cdf::CSerializeStream&);
                void __update(const TUser&);
            };

            typedef std::vector< ::Message::Db::Tables::TUser> SeqTUser;

            class __U__SeqTUser { };
            void __write(cdf::CSerializeStream&, const SeqTUser&, __U__SeqTUser);
            void __read(cdf::CSerializeStream&, SeqTUser&, __U__SeqTUser);
        }
    }
}

#endif
