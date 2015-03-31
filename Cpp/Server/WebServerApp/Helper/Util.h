#ifndef _WEBSERVER_HELPER_UTIL_H_
#define _WEBSERVER_HELPER_UTIL_H_
/*
* ������
* wenzhihua
*/
#include <vector>
#include <set>
#include "framework/util/datetime.h"
#include "framework/json/value.h"

namespace WebServerApp
{
	/*
	* �����Ʒ
	*/
	struct SRateItem
	{
		int code;		// ����
		int num;		// ����
		int lower;		// ����
		int upper;		// ����
	};
	typedef std::vector<SRateItem> SeqRateItem;

	/*
	* ������
	*/
	class CUtil
	{
	public:
		static const double MinProb;
		static bool happened(double probability);
		static int myRand(int n);
		/*
		*����һ�������
		*@param min -- ��Сֵ ������[
		*@param max -- ���ֵ ������]
		*@return int -- �����
		*/
		static int myRand(int min, int max);

		/*
		* �ڸ����ļ����У������ѡһ��
		* @param vec
		* @return int
		*/
		static int myRand(const std::vector<int>& vec);

		/*
		* ��һ�����ʼ����У���������ѡ���ʵ���ֵ
		* @param min -- ��Сֵ ������[
		* @param max -- ���ֵ ������]
		* @param SeqRateValue
		* @return int
		*/
		static SeqRateItem::const_iterator 
			myRand(int min, int max, const SeqRateItem& rateValues);

		/*
		* �ڽᶨ�ķ�Χ�ڣ����ȡN����
		*/
		static void myRand(int min, int max, int n, std::set<int> & res);

		/*
		* ������Ƚ�
		* @param min -- ��Сֵ ������[
		* @param max -- ���ֵ ������]
		* @param upper -- ����ֵ
		* @return bool
		*/
		static bool compRand(int min, int max, int upper);

		/*
		* ��������
		*/
		static int round(double value);

		/*
		* �ж��Ƿ�Ϊ����
		*/
		static bool isChinese(int ch);

		/*
		* �ж��Ƿ�Ϊ����
		*/
		static bool isNumber(int ch);

		/*
		* �ж��Ƿ�ΪӢ����ĸ
		*/
		static bool isLetter(int ch);

		/*
		* �Ƿ�Ϊȫ�Ǳ��
		*/
		static bool isFullWidthPunctuation(int ch);

		/*
		* �ж��Ƿ�ͬһ��
		*/
		static bool sameDay(const cdf::CDateTime& d1, const cdf::CDateTime& d2);

		/*
		* �ж��Ƿ�ͬһ��
		*/
		static bool sameWeek(const cdf::CDateTime& d1, const cdf::CDateTime& d2);
		static bool sameWeek(const cdf::CDateTime& d1, int d2Days);

		//mergetDt
		static const cdf::CDateTime mergeDate(const cdf::CDateTime & dayDt, const cdf::CDateTime & timeDate);

		/*
		* ��ȡHTML��ǩ����ɫ�ַ���
		* @param color - ��Ϸ�е���Ʒ��ɫֵ
		* @param oldStr - �ַ���
		* @return str
		*/
		static std::string htmlColorStr(int color, std::string& oldStr);

		/*
		* ����Json
		*/
		static void cutJson(const Json::Value& fromJson, Json::Value& toJson);

		/*
		* ���ɶ˿�
		*/
		static const std::string genAddressPort(const std::string & ip = "", int port = 2);

		/*
		* ��һ��ֵ������һ����Χ��[minVal, maxVal]
		* ���Ͳ���T--�����ڻ�����������
		*/
		template <typename T> 
		static T constrain(T val, T minVal, T maxVal)
		{
			if (val < minVal)
			{
				return minVal;
			}
			else if (val > maxVal)
			{
				return maxVal;
			}

			return val;
		}

		/*
		* ��֤val >= minVal
		*/
		template <typename T>
		static T minConstrain(T val, T minVal)
		{
			return (val < minVal ? minVal : val);
		}

		/*
		* ��֤ val <= maxVal
		*/
		template <typename T>
		static T maxConstrain(T val, T maxVal)
		{
			return (val > maxVal ? maxVal : val);
		}

		/*
		* get list
		*/
		static void getNewList(const std::vector<int> & inList, unsigned maxNum, int lastVal, std::vector<int> & outList);
		static void getOldList(const std::vector<int> & inList, unsigned maxNum, int lastVal, std::vector<int> & outList);

		// encrypt passwords
		static const std::string encryptPassword(const std::string & passwd);
	};
}
#endif
