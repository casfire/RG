#include "Exception.hpp"

using Engine::BaseException;
using Engine::EngineInitException;



/* BaseException */

BaseException::BaseException(const std::string &info)
: info(info)
{}

const char* BaseException::what() const throw()
{
	return info.c_str();
}



/* EngineInitException */

EngineInitException::EngineInitException(const std::string &info)
: BaseException(info)
{}
