#include "Storage.hpp"

namespace A = Engine::Asset;

typedef std::map<std::string, A::Asset*>::iterator AssetMapIterator;

A::Storage::Storage()
{
	basename.push("");
}

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

void A::Storage::release(A::Asset& asset)
{
	if (--(asset.grabCount) <= 0) {
		AssetMapIterator it = storage.find(asset.key);
		if (it != storage.end()) {
			storage.erase(it);
			delete &asset;
		}
	}
}

void A::Storage::pushKey(const std::string &key)
{
	std::string::size_type r = key.rfind('/');
	if (r == std::string::npos) {
		basename.push(basename.top() + "");
	} else {
		basename.push(key.substr(0, r + 1));
	}
}

void A::Storage::popKey()
{
	basename.pop();
}

std::string A::Storage::getKey(const std::string &key) const
{
	if (!key.empty() && (key[0] == '/')) {
		return key.substr(1);
	} else {
		return basename.top() + key;
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
