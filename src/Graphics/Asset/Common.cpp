#include "Common.hpp"

namespace A = Graphics::Asset;



/* Graphics::Asset::Storage */

typedef std::map<std::string, A::Asset*>::iterator AssetMapIterator;

A::Storage::Storage()
{}

A::Storage::~Storage()
{
	clear();
}

void A::Storage::clear()
{
	AssetMapIterator end = storage.end();
	for (AssetMapIterator it = storage.begin(); it != end; ++it) {
		delete it->second;
	}
	storage.clear();
}

void A::Storage::release(A::Asset* asset)
{
	if (--(asset->assetCount) <= 0) {
		AssetMapIterator it = storage.find(asset->assetKey);
		if (it != storage.end()) {
			storage.erase(it);
			delete asset;
		}
	}
}

A::Asset* A::Storage::get(const std::string &key)
{
	AssetMapIterator it = storage.find(key);
	if (it != storage.end()) {
		return it->second;
	} else {
		return nullptr;
	}
}



/* Graphics::Asset::Asset */

A::Asset::Asset()
{}

A::Asset::~Asset()
{}

const std::string& A::Asset::getAssetKey() const
{
	return assetKey;
}

std::size_t A::Asset::getAssetCount() const
{
	return assetCount;
}



/* Graphics::Asset::Exception */

A::Exception::Exception(const std::string &info)
: exceptionWhat(info)
{}

const char* A::Exception::what() const throw()
{
	return exceptionWhat.c_str();
}

const std::string& A::Exception::key() const
{
	return exceptionKey;
}

void A::Exception::setKey(const std::string &key)
{
	exceptionKey = key;
	if (exceptionWhat.size() > 0) {
		exceptionWhat = key + ": " + exceptionWhat;
	} else {
		exceptionWhat = key;
	}
}



/* Graphics::Asset::IOException */

A::IOException::IOException(const std::ios::failure &fail)
: Exception(fail.what())
{}



/* Graphics::Asset::CastException */

A::CastException::CastException()
: Exception("")
{}



/* Graphics::Asset::FormatException */
A::FormatException::FormatException(const std::string &info)
: Exception(info)
{}
