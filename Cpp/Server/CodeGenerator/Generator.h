#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include "ConfigManager.h"
#include <fstream>

namespace cg
{
	class CCodeGenerator
	{
	public:
		bool init(const std::string & outPath, const std::string & jsPath, std::string & headRoot);
		void genMsgCode();
		void genEventCode();
		void genJsCode();
		void close();

	private:
		void states(std::ofstream & of);

	private:
		std::string _outPath;
		std::string _jsPath;
		std::string _headRoot;
		std::string _eventHandlerName;
		std::string _eventClassName;

		std::ofstream _msgHpp;
		std::ofstream _msgCpp;
		std::ofstream _eventHpp;
		std::ofstream _eventCpp;

		std::ofstream _js;
	};
}

#endif