#ifndef _WEBSERVER_HELPER_UTIL_H_
#define _WEBSERVER_HELPER_UTIL_H_
/*
* 工具类
* wenzhihua
*/
#include <vector>
#include <set>
#include "framework/util/datetime.h"
#include "framework/json/value.h"

namespace WebServerApp
{
	/*
	* 随机物品
	*/
	struct SRateItem
	{
		int code;		// 编码
		int num;		// 数量
		int lower;		// 下限
		int upper;		// 上限
	};
	typedef std::vector<SRateItem> SeqRateItem;

	/*
	* 工具类
	*/
	class CUtil
	{
	public:
		static const double MinProb;
		static bool happened(double probability);
		static int myRand(int n);
		/*
		*生成一个随机数
		*@param min -- 最小值 闭区间[
		*@param max -- 最大值 闭区间]
		*@return int -- 随机数
		*/
		static int myRand(int min, int max);

		/*
		* 在给定的集合中，随机挑选一个
		* @param vec
		* @return int
		*/
		static int myRand(const std::vector<int>& vec);

		/*
		* 在一个概率集合中，按概率挑选概率的数值
		* @param min -- 最小值 闭区间[
		* @param max -- 最大值 闭区间]
		* @param SeqRateValue
		* @return int
		*/
		static SeqRateItem::const_iterator 
			myRand(int min, int max, const SeqRateItem& rateValues);

		/*
		* 在结定的范围内，随机取N个数
		*/
		static void myRand(int min, int max, int n, std::set<int> & res);

		/*
		* 随机数比较
		* @param min -- 最小值 闭区间[
		* @param max -- 最大值 闭区间]
		* @param upper -- 上限值
		* @return bool
		*/
		static bool compRand(int min, int max, int upper);

		/*
		* 四舍五入
		*/
		static int round(double value);

		/*
		* 判断是否为汉字
		*/
		static bool isChinese(int ch);

		/*
		* 判断是否为数字
		*/
		static bool isNumber(int ch);

		/*
		* 判断是否为英文字母
		*/
		static bool isLetter(int ch);

		/*
		* 是否为全角标点
		*/
		static bool isFullWidthPunctuation(int ch);

		/*
		* 判断是否同一天
		*/
		static bool sameDay(const cdf::CDateTime& d1, const cdf::CDateTime& d2);

		/*
		* 判断是否同一周
		*/
		static bool sameWeek(const cdf::CDateTime& d1, const cdf::CDateTime& d2);
		static bool sameWeek(const cdf::CDateTime& d1, int d2Days);

		//mergetDt
		static const cdf::CDateTime mergeDate(const cdf::CDateTime & dayDt, const cdf::CDateTime & timeDate);

		/*
		* 获取HTML标签的颜色字符串
		* @param color - 游戏中的物品颜色值
		* @param oldStr - 字符串
		* @return str
		*/
		static std::string htmlColorStr(int color, std::string& oldStr);

		/*
		* 精简Json
		*/
		static void cutJson(const Json::Value& fromJson, Json::Value& toJson);

		/*
		* 生成端口
		*/
		static const std::string genAddressPort(const std::string & ip = "", int port = 2);

		/*
		* 把一个值限制在一个范围内[minVal, maxVal]
		* 类型参数T--仅限于基本数据类型
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
		* 保证val >= minVal
		*/
		template <typename T>
		static T minConstrain(T val, T minVal)
		{
			return (val < minVal ? minVal : val);
		}

		/*
		* 保证 val <= maxVal
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
