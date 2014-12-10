#include "Common.hpp"

namespace A = Engine::Asset;



/* Engine::Asset::Asset */

A::Asset::Asset()
: grabCount(0)
{}

A::Asset::~Asset()
{}



/* Engine::Asset::Exception */

A::Exception::Exception(const std::string &info)
: info(info)
{}

const char* A::Exception::what() const throw()
{
	return info.c_str();
}

void A::Exception::pushFile(const std::string &file)
{
	info = info + "\nFrom asset '" + file + "'";
}



/* Engine::Asset::IOException */

A::IOException::IOException(const std::ios::failure &fail)
: Exception(fail.what())
{}



/* Engine::Asset::CastException */

A::CastException::CastException(const char *from, const char *to)
: Exception(std::string(from) + " to " + std::string(to) + ".")
{}



/* Engine::Asset::LoadException */

A::LoadException::LoadException(const std::string &info)
: Exception(info)
{}
