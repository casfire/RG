#pragma once
#ifndef _GRAPHICS_ASSET_COMMON_HPP_
#define _GRAPHICS_ASSET_COMMON_HPP_

#include <string>
#include <map>
#include <exception>
#include <ios> // std::ios::failure
#include <cstddef> // std::size_t

namespace Graphics { namespace Asset {
	
	
	
	class Storage;
	class Asset;
	class Exception;
	class IOException;
	class CastException;
	class FormatException;
	
	
	
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
		
		/* Retrieve already loaded asset or nullptr */
		Asset* get(const std::string &key);
		
		/* Load and create asset - throws Exception */
		template<class T>
		T* load(const std::string &key);
		
		/* Prevent copying */
		Storage(const Storage&) = delete;
		Storage& operator=(const Storage&) = delete;
		
	};
	
	
	
	/* Base asset class */
	class Asset {
	public:
		
		/* IMPORTANT!
		  All assets must have constructor in the form of
		  ExtendedAsset(Storage*, std::istream&);
		*/
		
		/* Getters */
		const std::string& getAssetKey() const;
		std::size_t getAssetCount() const;
		
	protected:
		
		/* Only derived assets can be constructed */
		Asset();
		
		/* Virtual destructor so derived assets can be deleted */
		virtual ~Asset();
		
	private:
		
		/* Asset key set by Storage */
		std::string assetKey;
		
		/* Grab count set by Storage */
		std::size_t assetCount;
		
		/* Prevent copying */
		Asset(const Asset&) = delete;
		Asset& operator=(const Asset&) = delete;
		
		/* Storage must have access to grab count and asset key */
		friend class Storage;
		
	};
	
	
	
	/* Base asset exception */
	class Exception : public std::exception {
	public:
		
		/* Return saved information */
		const char* what() const throw();
		const std::string& key() const;
		
	protected:
		
		/* Create exception and save information */
		Exception(const std::string &info);
		
	private:
		
		/* Saved exception information */
		std::string exceptionWhat;
		std::string exceptionKey;
		
		/* Storage sets exception key */
		friend class Storage;
		void setKey(const std::string &key);
		
	};
	
	
	
	/* Thrown when IO exception occurs */
	class IOException : public Exception {
	public:
		
		IOException(const std::ios::failure &fail);
		
	};
	
	
	
	/* Thrown when asset type casting fails */
	class CastException : public Exception {
	public:
		
		CastException();
		
	};
	
	
	
	/* Thrown when data has invalid asset format */
	class FormatException : public Exception {
	public:
		
		FormatException(const std::string &info);
		
	};
	
	
	
}} // namespace Graphics::Asset



#include <fstream>

template<class T>
T* Graphics::Asset::Storage::grab(const std::string &key)
{
	try {
		Graphics::Asset::Asset* a = get(key);
		if (a == nullptr) storage[key] = (a = load<T>(key));
		a->assetCount++;
		T* t = dynamic_cast<T*>(a);
		if (t == nullptr) throw CastException();
		return t;
	} catch (Graphics::Asset::Exception &fail) {
		fail.setKey(key);
		throw;
	}
}

template<class T>
T* Graphics::Asset::Storage::load(const std::string &key)
{
	try {
		std::ifstream stream;
		stream.exceptions(std::ifstream::failbit|std::ifstream::badbit);
		stream.open(key, std::ios::binary);
		T* a = new T(this, static_cast<std::istream&>(stream));
		a->assetKey = key;
		a->assetCount = 0;
		stream.close();
		return a;
	} catch (std::ios::failure &fail) {
		throw Graphics::Asset::IOException(fail);
	}
}



#endif // _GRAPHICS_ASSET_COMMON_HPP_
