#include "Storage.hpp"
#include <fstream>

namespace A = Engine::Asset;
typedef std::map<std::string, A::Asset*>::iterator AssetMapIterator;

A::Storage::Storage()
{
	path.push("");
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
		AssetMapIterator it = storage.find(asset.file);
		if (it != storage.end()) {
			delete it->second;
			storage.erase(it);
		}
	}
}

std::string A::Storage::pushPath(const std::string &key)
{
	const std::string& base = path.top();
	if (key.empty()) {
		path.push(base);
		return base + key;
	}
	std::string file = (key[0] == '/') ? key.substr(1) : (base + key);
	std::string::size_type r = file.rfind('/');
	path.push(r == std::string::npos ? base : file.substr(0, r + 1));
	return file;
}

void A::Storage::popPath()
{
	path.pop();
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

A::Asset* A::Storage::load(const std::string &file, Asset *obj)
{
	try {
		std::ifstream stream;
		stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		stream.open(file, std::ios::binary);
		obj->file = file;
		obj->grabCount = 0;
		obj->load(*this, static_cast<std::istream&>(stream));
		stream.close();
		return obj;
	} catch (std::ios::failure &fail) {
		throw Engine::Asset::IOException(fail);
	}
}
