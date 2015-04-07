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
	typedef std::vector<int> SeqInt;

	typedef std::vector<std::string> SeqString;

	typedef std::vector<cdf::CDateTime> SeqDate;

	typedef std::vector<bool> SeqBool;

	typedef std::vector<byte_t> SeqByte;

	typedef std::vector<short> SeqShort;

	typedef std::vector<double> SeqDouble;

	typedef std::vector<long64_t> SeqLong;

	typedef std::vector<std::string> SeqImage;

	struct SLoginReturn
	{
		int userId;
		std::string nickname;
		std::string avatar;
		int avatarImgId;
		std::string sessionKey;

		SLoginReturn();
		~SLoginReturn();

		void __read(cdf::CSimpleSerializer & __is);
		void __write(cdf::CSimpleSerializer & __os) const;
	}; //end of class SLoginReturn

	struct SPost
	{
		int postId;
		std::string title;
		std::string content;
		int authorUserId;
		std::string authorAccount;
		std::string authorNickname;
		int authorAvatarImgId;
		SeqInt imgIdList;
		cdf::CDateTime postDt;
		int likes;
		int dislikes;
		int comments;

		SPost();
		~SPost();

		void __read(cdf::CSimpleSerializer & __is);
		void __write(cdf::CSimpleSerializer & __os) const;
	}; //end of class SPost

	typedef std::vector<SPost> SeqPost;
	class SeqPost__U__{};
	void __read(cdf::CSimpleSerializer & __is, SeqPost& v, SeqPost__U__);
	void __write(cdf::CSimpleSerializer & __os, const SeqPost& v, SeqPost__U__);

	struct SComment
	{
		int userId;
		std::string nickname;
		std::string content;
		cdf::CDateTime commentDt;

		SComment();
		~SComment();

		void __read(cdf::CSimpleSerializer & __is);
		void __write(cdf::CSimpleSerializer & __os) const;
	}; //end of class SComment

	typedef std::vector<SComment> SeqComment;
	class SeqComment__U__{};
	void __read(cdf::CSimpleSerializer & __is, SeqComment& v, SeqComment__U__);
	void __write(cdf::CSimpleSerializer & __os, const SeqComment& v, SeqComment__U__);

} // end of namespace Rmi
#endif // end of __RMI_DATA_STRUCT_DEF_H__

