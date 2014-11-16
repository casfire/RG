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

void A::Exception::pushKey(const std::string &key)
{
	keys.push_back(key);
	info = info + "\nFrom asset '" + key + "'";
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
