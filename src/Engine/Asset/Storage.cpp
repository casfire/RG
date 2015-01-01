#include "Storage.hpp"
#include <fstream>

using Engine::Asset::BaseAsset;
using Engine::Asset::Storage;
using Engine::Asset::NotFoundException;
using Engine::Asset::IOException;
typedef std::map<std::string, BaseAsset*>::iterator AssetMapIterator;

Storage::Storage()
{
	path.push("");
}

Storage::~Storage()
{
	clear();
}

void Storage::clear()
{
	AssetMapIterator end = storage.end();
	for (AssetMapIterator it = storage.begin(); it != end; ++it) {
		delete it->second;
	}
	storage.clear();
}

void Storage::release(BaseAsset &asset)
{
	if (--(asset.grabCount) <= 0) {
		AssetMapIterator it = storage.find(asset.file);
		if (it != storage.end()) {
			it->second->unload(*this);
			delete it->second;
			storage.erase(it);
		}
	}
}

std::string Storage::pushPath(const std::string &key)
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

void Storage::popPath()
{
	path.pop();
}

BaseAsset* Storage::get(const std::string &key)
{
	AssetMapIterator it = storage.find(key);
	if (it != storage.end()) {
		return it->second;
	} else {
		return nullptr;
	}
}

BaseAsset* Storage::load(const std::string &file, BaseAsset *obj)
{
	std::ifstream stream;
	stream.open(file, std::ios::binary);
	if (!stream.is_open()) {
		delete obj;
		throw NotFoundException(file);
	}
	try {
		stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		obj->file = file;
		obj->grabCount = 0;
		obj->load(*this, static_cast<std::istream&>(stream));
		return obj;
	} catch (std::ios::failure &fail) {
		delete obj;
		throw IOException(fail);
	}
}
