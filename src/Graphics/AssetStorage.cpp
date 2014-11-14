#include "AssetStorage.hpp"

namespace G = Graphics;



/* Graphics::AssetStorage */

typedef std::map<std::string, G::Asset*>::iterator AssetMapIterator;

G::AssetStorage::AssetStorage()
{}

G::AssetStorage::~AssetStorage()
{
	clear();
}

void G::AssetStorage::clear()
{
	AssetMapIterator end = storage.end();
	for (AssetMapIterator it = storage.begin(); it != end; ++it) {
		delete it->second;
	}
	storage.clear();
}

void G::AssetStorage::release(Asset* asset)
{
	if (--(asset->assetCount) <= 0) {
		AssetMapIterator it = storage.find(asset->assetKey);
		if (it != storage.end()) {
			storage.erase(it);
			delete asset;
		}
	}
}

G::Asset* G::AssetStorage::get(const std::string &key)
{
	AssetMapIterator it = storage.find(key);
	if (it != storage.end()) {
		return it->second;
	} else {
		return nullptr;
	}
}



/* Graphics::Asset */

G::Asset::Asset(const std::string &key)
: assetKey(key), assetCount(0)
{}

G::Asset::~Asset()
{}

const std::string& G::Asset::getAssetKey() const
{
	return assetKey;
}

unsigned int G::Asset::getAssetCount() const
{
	return assetCount;
}



/* Graphics::AssetException */

G::AssetException::AssetException(const std::string &info)
: exceptionInfo(info)
{}

const char* G::AssetException::what() const throw()
{
	return exceptionInfo.c_str();
}



/* Graphics::AssetIOException */

G::AssetIOException::AssetIOException(const std::ios::failure &fail)
: AssetException(fail.what())
{}
