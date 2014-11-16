#include "Storage.hpp"

namespace A = Engine::Asset;

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
	if (--(asset->grabCount) <= 0) {
		AssetMapIterator it = storage.find(asset->key);
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
