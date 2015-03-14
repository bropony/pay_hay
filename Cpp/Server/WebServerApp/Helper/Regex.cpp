#include "Helper/Regex.h"
#include "framework/util/stringfun.h"
#include "framework/lang/transcodestring.h"
#include "framework/lang/transcodestring.h"
#include "framework/util/allocator.h"
#include "framework/util/exception.h"
#include <fstream>
#include <set>

using namespace WebServerApp;

CRegex::CRegex()
{
}

CRegex::~CRegex()
{
}

CRegex* CRegex::instance()
{
	static CRegex inst;
	return &inst;
}


void CRegex::loadRegex(
    const std::vector<std::string>& regexs 
   )
{
    _regexNodes.clear();
    std::vector<std::string>::const_iterator iter;
    std::vector<std::string> regexNodes;
    for(iter = regexs.begin() ; iter != regexs.end() ; iter ++)
    {
        std::vector<std::string> nodes;
        cdf::CStrFun::split_str(nodes, iter->c_str(), "|");
        std::vector<std::string>::const_iterator iter1;
        for(iter1 = nodes.begin() ; iter1 != nodes.end() ; iter1 ++)
        {
            plaseNode(*iter1, regexNodes);
            if(!regexNodes.empty())
            {
                std::vector<std::wstring> wregexNodes;
                int len = 0;
                for(size_t i = 0 ; i < regexNodes.size() ; i ++)
                {
                    std::wstring node = cdf::utf82utf16(regexNodes[i]);
                    len += (int)node.length();
                    wregexNodes.push_back(node);
                }
                if(len == 0)
                {
                    continue;
                }
                _regexNodes.insert(std::pair<int, std::vector<std::wstring> >(len, wregexNodes));
            }
        }
    }
#ifndef _DEBUG
    RegexMap regexMap = _regexNodes;
    std::set<std::vector<std::wstring> > nodesSet;
    for(RegexMap::reverse_iterator iter1 = _regexNodes.rbegin() ; iter1 != _regexNodes.rend() ; iter1 ++)
    {
        RegexMap::iterator iter2;
        for(iter2 = regexMap.begin() ; iter2 != regexMap.end() ; iter2 ++)
        {
            if(iter2->second == iter1->second)
            {
                break;
            }
            if(find(iter1->second[0], iter2->second))
            {
                nodesSet.insert(iter1->second);
                break;
            }
            if(iter1->first < iter2->first)
            {
                break;
            }
        }
    }
    for(RegexMap::iterator iter1 = _regexNodes.begin() ; iter1 != _regexNodes.end() ;)
    {
        if(nodesSet.find(iter1->second) != nodesSet.end())
        {
            _regexNodes.erase(iter1 ++);
        }
        else
        {
            iter1 ++ ;
        }
    }
#endif
}

bool CRegex::loadRegex(
    const std::string& file 
   )
{
    std::ifstream ifs;
    ifs.open(file.c_str());
    if(!ifs.is_open())
    {
        return false;
    }
    char buf[2048];
    std::vector<std::string> lines;
    while(!ifs.eof())
    {
        ifs.getline(buf, sizeof(buf) - 1);
        lines.push_back(cdf::CStrFun::trim_ex(buf, "\n\r"));
    }
    loadRegex(lines);
    return true;
}

bool CRegex::find(
    const std::string& str 
   )
{
    return find(cdf::utf82utf16(str));
}

bool CRegex::find(
    const std::wstring& str 
   )
{
    RegexMap::const_iterator iter;
    for(iter = _regexNodes.begin() ; iter != _regexNodes.end() ; iter ++)
    {
        if((int)str.length() < iter->first)
        {
            break;
        }
        if(find(str, iter->second))
        {
            return true;
        }
    }
    return false;
}

bool CRegex::find(
    const std::wstring& str,
    const std::vector<std::wstring>& regexs
   )
{
    if(str.length() == 0)
    {
        return false;
    }
    std::vector<std::wstring>::const_iterator iter;
    const wchar_t * p = str.c_str();
    int leave = (int)str.length();
    for(iter = regexs.begin() ; iter != regexs.end() ; iter ++)
    {
        if(leave < (int)iter->length())
        {
            return false;
        }
        p = cdf::CStrFun::wstrcasestr(p, iter->c_str());
        if(NULL == p)
        {
            return false;
        }
        p += iter->length();
        leave -= (int)iter->length();

    }
    return true;
}

int CRegex::plaseNode(
    const std::string& str, 
    std::vector<std::string>& nodes 
   )
{
    cdf::CStrFun::split_str(nodes, str.c_str(), ".*");
    std::vector<std::string>::const_iterator iter;
    int len = 0;
    for(iter = nodes.begin() ; iter != nodes.end() ; iter ++)
    {
        len += (int)iter->length();
    }
    return len;
}

void CRegex::replace(std::string& str)
{
    std::wstring wstr = cdf::utf82utf16(str);
    RegexMap::const_iterator iter;
    for(iter = _regexNodes.begin() ; iter != _regexNodes.end() ; iter ++)
    {
        if((int)str.length() < iter->first)
        {
            break;
        }
        replace(wstr, iter->second);
    }
    str = utf162utf8(wstr);
    return;
}

void CRegex::replace(std::wstring& wstr, const std::vector<std::wstring>& regexs)
{
    if(wstr.length() == 0 || regexs.size() == 0)
    {
        return;
    }
    //对于可能存在统配的过滤词只替换其前缀
    std::wstring wFilter = regexs.at(0);
    std::wstring wstar = cdf::utf82utf16(std::string("**"));
    int index = 0;
    do
    {
        index = wstr.find(wFilter, index);
        if (index >= 0)
        {
            wstr.replace(index, wFilter.length(),wstar);
        }
    } 
    while (index >= 0);
}

std::string CRegex::utf162utf8(std::wstring wstr)
{
    int len = (int)wstr.length() * 3  + 3;
    char* buf = (char*)cdf::CAllocator::instance()->malloc( len );
    if( cdf::CTranscoder::utf16s2utf8s( wstr.c_str() , buf, len) < 0 )
    {
        return "";
    }
    std::string str = buf;
    return str;
}
