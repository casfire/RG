#pragma once
#ifndef _ENGINE_ASSET_STORAGE_HPP_
#define _ENGINE_ASSET_STORAGE_HPP_

#include "Common.hpp"
#include <string>
#include <map>
#include <stack>
#include <fstream>
#include <typeinfo> // typeid

namespace Engine { namespace Asset {
	
	
	
	/* Asset storage for pooling */
	class Storage {
	public:
		
		/* Create a new empty asset storage */
		Storage();
		
		/* Delete all assets */
		~Storage();
		void clear();
		
		/* Grab asset - throws Asset::Exception */
		template<class T>
		T& grab(const std::string &key);
		
		/* Release asset */
		void release(Asset& asset);
		
	private:
		
		/* Storage */
		std::map<std::string, Asset*> storage;
		
		/* Path stack */
		std::stack<std::string> path;
		std::string pushPath(const std::string &key);
		void popPath();
		
		/* Retrieve already loaded asset or nullptr */
		Asset* get(const std::string &file);
		
		/* Load and create asset - throws Asset::Exception */
		template<class T>
		T* load(const std::string &file);
		
		/* Prevent copying */
		Storage(const Storage&) = delete;
		Storage& operator=(const Storage&) = delete;
		
	};
	
	
	
}} // namespace Engine::Asset

template<class T>
T& Engine::Asset::Storage::grab(const std::string &key)
{
	std::string file = pushPath(key);
	try {
		Engine::Asset::Asset* a = get(file);
		if (a == nullptr) storage[file] = (a = load<T>(file));
		a->grabCount++;
		T* t = dynamic_cast<T*>(a);
		if (t == nullptr) {
			throw CastException(typeid(*a).name(), typeid(T).name());
		}
		popPath();
		return *t;
	} catch (Engine::Asset::Exception &fail) {
		fail.pushFile(file);
		popPath();
		throw;
	}
}

template<class T>
T* Engine::Asset::Storage::load(const std::string &file)
{
	try {
		std::ifstream stream;
		stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		stream.open(file, std::ios::binary);
		T* a = new T();
		a->file = file;
		a->grabCount = 0;
		a->load(*this, static_cast<std::istream&>(stream));
		stream.close();
		return a;
	} catch (std::ios::failure &fail) {
		throw Engine::Asset::IOException(fail);
	}
}

#endif // _ENGINE_ASSET_STORAGE_HPP_
