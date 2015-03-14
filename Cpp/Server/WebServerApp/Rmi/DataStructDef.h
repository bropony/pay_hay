#ifndef __RMI_DATA_STRUCT_DEF_H__
#define __RMI_DATA_STRUCT_DEF_H__

#include "framework/serialize/simpleserializer.h"
#include "framework/util/refshared.h"
#include <string>
#include <vector>
#include <set>
#include <map>

namespace Rmi
{
	typedef std::vector<short> SeqShort;

	typedef std::vector<long64_t> SeqLong;

	typedef std::vector<int> SeqInt;

	typedef std::vector<bool> SeqBool;

	typedef std::vector<std::string> SeqString;

	struct STest
	{
		SeqShort s;
		SeqLong l;
		SeqInt i;
		SeqBool b;
		SeqString ss;

		STest();
		~STest();

		void __read(cdf::CSimpleSerializer & __is);
		void __write(cdf::CSimpleSerializer & __os);
	}; //end of class STest

	typedef std::vector<SeqInt> SeqSeqInt;
	class SeqSeqInt__U__{};
	void __read(cdf::CSimpleSerializer & __is, SeqSeqInt& v, SeqSeqInt__U__);
	void __write(cdf::CSimpleSerializer & __os, SeqSeqInt& v, SeqSeqInt__U__);

	struct SGoo
	{
		STest st;
		SeqSeqInt ilist;

		SGoo();
		~SGoo();

		void __read(cdf::CSimpleSerializer & __is);
		void __write(cdf::CSimpleSerializer & __os);
	}; //end of class SGoo

} // end of namespace Rmi
#endif // end of __RMI_DATA_STRUCT_DEF_H__

