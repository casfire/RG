#include "Base.hpp"

using Engine::Asset::BaseAsset;
using Engine::Asset::Storage;
using Engine::Asset::BaseException;
using Engine::Asset::NotFoundException;
using Engine::Asset::IOException;
using Engine::Asset::CastException;
using Engine::Asset::LoadException;



/* BaseAsset */

BaseAsset::BaseAsset()
{}

BaseAsset::~BaseAsset()
{}

void BaseAsset::unload(Storage&)
{}



/* BaseException */

BaseException::BaseException(const std::string &info)
: info(info)
{}

const char* BaseException::what() const throw()
{
	return info.c_str();
}

void BaseException::pushFile(const std::string &file)
{
	info = info + "\nFrom asset '" + file + "'";
}



/* NotFoundException */

NotFoundException::NotFoundException(const std::string &file)
: BaseException("Asset '" + file + "' not found.")
{}



/* IOException */

IOException::IOException(const std::ios::failure &fail)
: BaseException(fail.what())
{}



/* CastException */

CastException::CastException(const char *from, const char *to)
: BaseException(std::string(from) + " to " + std::string(to) + ".")
{}



/* LoadException */

LoadException::LoadException(const std::string &info)
: BaseException(info)
{}
