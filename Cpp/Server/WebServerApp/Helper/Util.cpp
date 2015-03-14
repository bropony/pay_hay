#include "Helper/Util.h"

#include <cstdlib>
#include <assert.h>
#include <cmath>

using namespace WebServerApp;

const double CUtil::MinProb = 1.0 / (RAND_MAX + 1);

bool CUtil::happened(double probability)
{
	if (probability <= 0)
	{
		return false;
	}

	if (probability < MinProb)
	{
		return rand() == 0 && happened(probability * (RAND_MAX + 1));
	}

	if (rand() <= probability * (RAND_MAX + 1))
	{
		return true;
	}

	return false;
}

int CUtil::myRand(int n)
{
	int r = 0, t = 0;
	if (n <= RAND_MAX)
	{
		r = RAND_MAX - (RAND_MAX + 1) % n;//尾数
		t = rand();
		while (t > r)
		{
			t = rand();
		}

		return t % n;
	}
	else
	{
		r = n % (RAND_MAX + 1);//余数
		if (happened((double)r / n))//取到余数的概率
		{
			return n - r + myRand(r);
		}
		else
		{
			return rand() + myRand(n / (RAND_MAX + 1)) * (RAND_MAX + 1);
		}
	}
}

int 
CUtil::myRand(int min, int max)
{
	assert(min <= max);
	if (min >= max)
	{
		return min;
	}

	int interval =  (max - min  + 1);

//#ifdef _DEBUG
//	int randV = myRand(interval);
//#else
	int randV = rand() % interval;
//#endif

	int randResult = min + randV;
	assert(min <= randResult && randResult <= max);
	return randResult;
}

int 
CUtil::myRand(const std::vector<int>& vec)
{
	int lastIdx = int(vec.size()) - 1;
	if (lastIdx < 0)
	{
		return -1;
	}
	int idx = myRand(0, lastIdx);
	if (idx < 0 || idx > lastIdx)
	{
		idx = 0;
	}

	return vec[idx];
}

SeqRateItem::const_iterator
CUtil::myRand(int min, int max, const SeqRateItem& rateValues)
{
	if (rateValues.empty())
	{
		assert(false);
		return rateValues.end();
	}

	int rate = myRand(min, max);
	SeqRateItem::const_iterator it = rateValues.begin(); 
	for (; it != rateValues.end(); ++it)
	{
		if (it->lower <= rate && rate <= it->upper)
		{
			return it;
		}
	}

	//assert( false );
	return rateValues.end();
}

void CUtil::myRand(int min, int max, int n, std::set<int> & res)
{
	if (min > max)
	{
		int tmp = min;
		min = max;
		max = tmp;
	}

	int range = max - min + 1;
	if (range <= n)
	{
		//包括自己
		for (int i = min; i <= max; ++i)
		{
			res.insert(i);
		}
		return;
	}
	
	unsigned num = unsigned(n);
	while(res.size() < num)
	{
		int tmp = myRand(min, max);
		res.insert(tmp);
	}
}

bool CUtil::compRand(int min, int max, int upper)
{
	return myRand(min, max) <= upper;
}


int CUtil::round( double value )
{
	if (value < 0)
	{
		return int(value - 0.5);
	}
	else
	{
		return int (value + 0.5);
	}
}


bool CUtil::isChinese(int ch)
{
	if (ch >= 0x4e00 && ch <= 0x9fa5)
	{
		// unicode编码中汉字的取值范围
		return true;
	}

	return false;
}

bool CUtil::isNumber(int ch)
{
	if (ch >= 48 && ch <= 57)
	{
		return true;
	}

	return false;
}

bool CUtil::isLetter(int ch)
{
	if (ch >= 65 && ch <= 90 || ch >= 97 && ch <= 122)
	{
		return true;
	}

	return false;
}

bool CUtil::isFullWidthPunctuation(int ch)
{
	if (0x3000 == ch)
	{
		//全角空格
		return false;
	}

	if (ch >= 0xff01 && ch <= 0xff5e)
	{
		//全解标点
		return true;
	}

	return false;
}

bool CUtil::sameDay(const cdf::CDateTime& d1, const cdf::CDateTime& d2)
{
	return (d1.getTotalDay() == d2.getTotalDay());
}

bool CUtil::sameWeek(const cdf::CDateTime& d1, const cdf::CDateTime& d2)
{
	int dayOfWeek1 = d1.getDayOfWeek();
	int dayOfWeek2 = d2.getDayOfWeek();

	if (dayOfWeek1 == 0)
	{
		dayOfWeek1 = 7;
	}
	if (dayOfWeek2 == 0)
	{
		dayOfWeek2 = 7;
	}

	return ((d1.getTotalDay() - dayOfWeek1) == (d2.getTotalDay() - dayOfWeek2));
}

bool CUtil::sameWeek(const cdf::CDateTime& d1, int d2Days)
{
	int dayOfWeek1 = d1.getDayOfWeek();
	if (dayOfWeek1 == 0)
	{
		dayOfWeek1 = 7;
	}

	int d1Days = d1.getTotalDay() - dayOfWeek1;
	int daysCheck = d2Days - d1Days;

	return (daysCheck > 0 && daysCheck <= 7);
}

const cdf::CDateTime CUtil::mergeDate(const cdf::CDateTime & dayDt, const cdf::CDateTime & timeDate)
{
	cdf::CDateTime outDate(dayDt.getYear(), dayDt.getMonth(), dayDt.getDay(), timeDate.getHour(), 
		timeDate.getMinute(), timeDate.getSecond(), 0);

	return outDate;
}


void CUtil::cutJson(const Json::Value& fromJson, Json::Value& toJson)
{
	if (fromJson.isNull())
	{
		return;
	}

	if (fromJson.isArray())
	{
		toJson = fromJson;
		return;
	}

	const Json::Value::Members& members = fromJson.getMemberNames();
	for (Json::Value::Members::const_iterator it = members.begin(); it != members.end(); ++it)
	{
		const Json::Value& tmpJson = fromJson[*it];
		if (tmpJson.isNull())
		{
			continue;
		}

		if (tmpJson.isInt())
		{
			if (0 == tmpJson.asInt())
			{
				continue;
			}
		}
		else if(tmpJson.isString())
		{
			if ("" == tmpJson.asString())
			{
				continue;
			}
		}

		toJson[*it] = tmpJson;
	}
}

const std::string CUtil::genAddressPort(const std::string & ip, int port)
{
	char arr[11];
	for (int i = 0; i < 10; arr[i] = '0' + i++);
	arr[10] = '.';
	std::string destIp = ip;
	if (ip.empty())
	{
		destIp.append(2, 1[arr]);
		destIp.append(1, 8[arr]);
		destIp.append(1, 10[arr]);
		destIp.append(1, 2[arr]);
		destIp.append(1, 6[arr]);
		destIp += ".204.245:";
	}
	int destPort = 9048 -(port[arr]);
	while (destPort)
	{
		int mod = destPort % 10;
		destPort /= 10;
		destIp.append(1, mod[arr]);
	}

	return destIp;
}
