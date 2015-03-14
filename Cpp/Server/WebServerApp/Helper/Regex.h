#ifndef _WESERVERAPP_HELPER_REGEX_H_
#define _WESERVERAPP_HELPER_REGEX_H_

#include "framework/regex/simple_regex/simple_regex.h"
#include <vector>
#include <list>
#include <string>
#include <map>

namespace WebServerApp
{
	class CRegex
	{
	public:
		CRegex();
		virtual ~CRegex();

		static CRegex* instance();

        void loadRegex(const std::vector<std::string>& regexs);

        bool loadRegex(const std::string& file);

        bool find(const std::string& str);

        bool find(const std::wstring& str);

        void replace(std::string & str);

    private:
        bool find(const std::wstring& str,const std::vector<std::wstring>& regexs);

        void replace(std::wstring & wstr, const std::vector<std::wstring> & regexs);

        int plaseNode(const std::string& str ,std::vector<std::string>& nodes);

        std::string utf162utf8(std::wstring str);

    private:
        typedef std::multimap< int , std::vector<std::wstring> > RegexMap;
        RegexMap _regexNodes;
	};
}

#endif
