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

#ifndef ___TStructConfig_h__
#define ___TStructConfig_h__

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
            struct TStructConfig
            {
                int id;
                std::string name;
                int type;
                std::string fields;
                std::string descr;

                TStructConfig();
                bool operator==(const TStructConfig&) const;
                bool operator!=(const TStructConfig&) const;
                bool operator<(const TStructConfig&) const;
                
                void __init();
                void __write(cdf::CSerializeStream&) const;
                void __read(cdf::CSerializeStream&);
                void __update(const TStructConfig&);
            };

            typedef std::vector< ::Message::Db::Tables::TStructConfig> SeqTStructConfig;

            class __U__SeqTStructConfig { };
            void __write(cdf::CSerializeStream&, const SeqTStructConfig&, __U__SeqTStructConfig);
            void __read(cdf::CSerializeStream&, SeqTStructConfig&, __U__SeqTStructConfig);
        }
    }
}

#endif
