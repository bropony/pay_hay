#include "DataStructDef.h"

namespace Rmi
{

//definition of class SLoginReturn
SLoginReturn::SLoginReturn()
:userId()
,nickname()
,avatar()
,sessionKey()
{
}

SLoginReturn::~SLoginReturn()
{
}

void SLoginReturn::__read(cdf::CSimpleSerializer & __is)
{
	__is.read(userId);
	__is.read(nickname);
	__is.read(avatar);
	__is.read(sessionKey);
}

void SLoginReturn::__write(cdf::CSimpleSerializer & __os) const
{
	__os.write(userId);
	__os.write(nickname);
	__os.write(avatar);
	__os.write(sessionKey);
}

//definition of class SPost
SPost::SPost()
:postId()
,title()
,content()
,authorUserId()
,authorAccount()
,authorNickname()
,imgIdList()
,postDt()
,likes()
,dislikes()
,comments()
{
}

SPost::~SPost()
{
}

void SPost::__read(cdf::CSimpleSerializer & __is)
{
	__is.read(postId);
	__is.read(title);
	__is.read(content);
	__is.read(authorUserId);
	__is.read(authorAccount);
	__is.read(authorNickname);
	__is.read(imgIdList); 
	__is.read(postDt);
	__is.read(likes);
	__is.read(dislikes);
	__is.read(comments);
}

void SPost::__write(cdf::CSimpleSerializer & __os) const
{
	__os.write(postId);
	__os.write(title);
	__os.write(content);
	__os.write(authorUserId);
	__os.write(authorAccount);
	__os.write(authorNickname);
	__os.write(imgIdList); 
	__os.write(postDt);
	__os.write(likes);
	__os.write(dislikes);
	__os.write(comments);
}

//definition of __read and __write of SeqPost
void __read(cdf::CSimpleSerializer & __is, SeqPost& v, SeqPost__U__)
{
	unsigned size = 0;
	__is.readSize(size); 

	for(unsigned i = 0; i < size; i++)
	{
		SPost elem;
		elem.__read(__is);
		v.push_back(elem);
	}
}

void __write(cdf::CSimpleSerializer & __os, const SeqPost& v, SeqPost__U__)
{
	unsigned size = v.size();
	__os.writeSize(size);

	for (auto elem : v)
	{
		elem.__write(__os);
	}
}

//definition of class SComment
SComment::SComment()
:userId()
,nickname()
,content()
,commentDt()
{
}

SComment::~SComment()
{
}

void SComment::__read(cdf::CSimpleSerializer & __is)
{
	__is.read(userId);
	__is.read(nickname);
	__is.read(content);
	__is.read(commentDt);
}

void SComment::__write(cdf::CSimpleSerializer & __os) const
{
	__os.write(userId);
	__os.write(nickname);
	__os.write(content);
	__os.write(commentDt);
}

//definition of __read and __write of SeqComment
void __read(cdf::CSimpleSerializer & __is, SeqComment& v, SeqComment__U__)
{
	unsigned size = 0;
	__is.readSize(size); 

	for(unsigned i = 0; i < size; i++)
	{
		SComment elem;
		elem.__read(__is);
		v.push_back(elem);
	}
}

void __write(cdf::CSimpleSerializer & __os, const SeqComment& v, SeqComment__U__)
{
	unsigned size = v.size();
	__os.writeSize(size);

	for (auto elem : v)
	{
		elem.__write(__os);
	}
}


} //end of namespace Rmi

