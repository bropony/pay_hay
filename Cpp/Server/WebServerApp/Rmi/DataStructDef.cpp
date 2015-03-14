#include "DataStructDef.h"

namespace Rmi
{

//definition of class STest
STest::STest()
:s()
,l()
,i()
,b()
,ss()
{
}

STest::~STest()
{
}

void STest::__read(cdf::CSimpleSerializer & __is)
{
	__is.read(s); 
	__is.read(l); 
	__is.read(i); 
	__is.read(b); 
	__is.read(ss); 
}

void STest::__write(cdf::CSimpleSerializer & __os)
{
	__os.write(s); 
	__os.write(l); 
	__os.write(i); 
	__os.write(b); 
	__os.write(ss); 
}

//definition of __read and __write of SeqSeqInt
void __read(cdf::CSimpleSerializer & __is, SeqSeqInt& v, SeqSeqInt__U__)
{
	unsigned size = 0;
	__is.readSize(size); 

	for(unsigned i = 0; i < size; i++)
	{
		SeqInt elem;
		__is.read(elem);
		v.push_back(elem);
	}
}

void __write(cdf::CSimpleSerializer & __os, SeqSeqInt& v, SeqSeqInt__U__)
{
	unsigned size = v.size();
	__os.writeSize(size);

	for (auto elem : v)
	{
		__os.write(elem);
	}
}

//definition of class SGoo
SGoo::SGoo()
:st()
,ilist()
{
}

SGoo::~SGoo()
{
}

void SGoo::__read(cdf::CSimpleSerializer & __is)
{
	st.__read(__is);
	::Rmi::__read(__is, ilist, SeqSeqInt__U__());
}

void SGoo::__write(cdf::CSimpleSerializer & __os)
{
	st.__write(__os);
	::Rmi::__write(__os, ilist, SeqSeqInt__U__());
}


} //end of namespace Rmi

