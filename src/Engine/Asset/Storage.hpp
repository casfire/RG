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
		
		/* Grab asset - throws Exception */
		template<class T>
		T* grab(const std::string &key);
		
		/* Release asset */
		void release(Asset* asset);
		
	private:
		
		/* Storage */
		std::map<std::string, Asset*> storage;
		
		/* Basename stack */
		std::stack<std::string> basename;
		void pushKey(const std::string &key);
		void popKey();
		std::string getKey(const std::string &key) const;
		
		/* Retrieve already loaded asset or nullptr */
		Asset* get(const std::string &key);
		
		/* Load and create asset - throws Exception */
		template<class T>
		T* load(const std::string &key);
		
		/* Prevent copying */
		Storage(const Storage&) = delete;
		Storage& operator=(const Storage&) = delete;
		
	};
	
	
	
}} // namespace Engine::Asset

template<class T>
T* Engine::Asset::Storage::grab(const std::string &key)
{
	try {
		Engine::Asset::Asset* a = get(key);
		if (a == nullptr) storage[key] = (a = load<T>(key));
		a->grabCount++;
		T* t = dynamic_cast<T*>(a);
		if (t == nullptr) {
			throw CastException(typeid(*a).name(), typeid(T).name());
		}
		return t;
	} catch (Engine::Asset::Exception &fail) {
		fail.pushKey(key);
		throw;
	}
}

template<class T>
T* Engine::Asset::Storage::load(const std::string &key)
{
	std::string filename = getKey(key);
	try {
		std::ifstream stream;
		stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		stream.open(filename, std::ios::binary);
		T* a = new T();
		a->key = filename;
		a->grabCount = 0;
		pushKey(filename);
		a->load(*this, static_cast<std::istream&>(stream));
		popKey();
		stream.close();
		return a;
	} catch (std::ios::failure &fail) {
		throw Engine::Asset::IOException(fail);
	}
}

#endif // _ENGINE_ASSET_STORAGE_HPP_
