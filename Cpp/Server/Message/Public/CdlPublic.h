// **********************************************************************
//
// Copyright (c) 2003-2009 CDE, Inc. All rights reserved.
//
// This copy of Cde is licensed to you under the terms described in the
// CDE_LICENSE file included in this distribution.
//
// **********************************************************************

// Cde version 1.0.1
// Generated from file `CdlPublic.cdl'

#ifndef ___CdlPublic_h__
#define ___CdlPublic_h__

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
    namespace Public
    {
        typedef std::vector<bool> SeqBool;

        typedef std::vector<byte> SeqByte;

        typedef std::vector<short> SeqShort;

        typedef std::vector<int> SeqInt;

        typedef std::vector<float> SeqFloat;

        typedef std::vector<double> SeqDouble;

        typedef std::vector<long64_t> SeqLong;

        typedef std::vector<std::string> SeqString;

        typedef ::std::map<int, int> DictIntInt;

        class __U__DictIntInt { };
        void __write(cdf::CSerializeStream&, const DictIntInt&, __U__DictIntInt);
        void __read(cdf::CSerializeStream&, DictIntInt&, __U__DictIntInt);

        typedef ::std::map<long64_t, int> DictLongInt;

        class __U__DictLongInt { };
        void __write(cdf::CSerializeStream&, const DictLongInt&, __U__DictLongInt);
        void __read(cdf::CSerializeStream&, DictLongInt&, __U__DictLongInt);

        typedef ::std::map<int, std::string> DictIntStr;

        class __U__DictIntStr { };
        void __write(cdf::CSerializeStream&, const DictIntStr&, __U__DictIntStr);
        void __read(cdf::CSerializeStream&, DictIntStr&, __U__DictIntStr);

        typedef ::std::map<std::string, int> DictStrInt;

        class __U__DictStrInt { };
        void __write(cdf::CSerializeStream&, const DictStrInt&, __U__DictStrInt);
        void __read(cdf::CSerializeStream&, DictStrInt&, __U__DictStrInt);

        typedef ::std::map<int, bool> DictIntBool;

        class __U__DictIntBool { };
        void __write(cdf::CSerializeStream&, const DictIntBool&, __U__DictIntBool);
        void __read(cdf::CSerializeStream&, DictIntBool&, __U__DictIntBool);

        typedef ::std::map<int, cdf::CDateTime> DictIntDate;

        class __U__DictIntDate { };
        void __write(cdf::CSerializeStream&, const DictIntDate&, __U__DictIntDate);
        void __read(cdf::CSerializeStream&, DictIntDate&, __U__DictIntDate);

        typedef ::std::map<std::string, bool> DictStrBool;

        class __U__DictStrBool { };
        void __write(cdf::CSerializeStream&, const DictStrBool&, __U__DictStrBool);
        void __read(cdf::CSerializeStream&, DictStrBool&, __U__DictStrBool);

        typedef ::std::map<std::string, std::string> DictStrStr;

        class __U__DictStrStr { };
        void __write(cdf::CSerializeStream&, const DictStrStr&, __U__DictStrStr);
        void __read(cdf::CSerializeStream&, DictStrStr&, __U__DictStrStr);
    }
}

#endif
