#pragma once
#ifndef _GRAPHICS_ASSETSTORAGE_HPP_
#define _GRAPHICS_ASSETSTORAGE_HPP_

#include <string>
#include <map>
#include <exception>
#include <ios> // std::ios::failure

namespace Graphics {
	
	
	
	class AssetStorage;
	class Asset;
	class AssetException;
	class AssetIOException;
	
	
	
	/* Asset storage for pooling */
	class AssetStorage {
	public:
		
		/* Create a new empty asset storage */
		AssetStorage();
		
		/* Destroy all assets */
		~AssetStorage();
		void clear();
		
		/* Grab asset - throws AssetException */
		template<class T>
		T* grab(const std::string &key);
		
		/* Release asset */
		void release(Asset* asset);
		
	private:
		
		/* Storage */
		std::map<std::string, Asset*> storage;
		
		/* Retrieve already loaded asset or nullptr */
		Asset* get(const std::string &key);
		
		/* Load and create asset - throws AssetException */
		template<class T>
		T* load(const std::string &key);
		
		/* Prevent copying */
		AssetStorage(const AssetStorage&) = delete;
		AssetStorage& operator=(const AssetStorage&) = delete;
		
	};
	
	
	
	class Asset {
	public:
		
		/* Save key and set grab count to zero */
		Asset(const std::string &key);
		
		/* Virtual destructor so derived assets can be deleted */
		virtual ~Asset();
		
		/* Getters */
		const std::string& getAssetKey() const;
		unsigned int getAssetCount() const;
		
	private:
		
		/* Prevent copying */
		Asset(const Asset&) = delete;
		Asset& operator=(const Asset&) = delete;
		
		/* AssetStorage must have access to grab count and asset key */
		friend class AssetStorage;
		
		/* Asset key */
		const std::string assetKey;
		
		/* Grab count */
		unsigned int assetCount;
		
	};
	
	
	
	/* Base asset exception */
	class AssetException : public std::exception {
	public:
		
		/* Create exception and save information */
		AssetException(const std::string &info);
		
		/* Return saved information */
		const char* what() const throw();
		
	private:
		
		/* Saved exception information */
		const std::string exceptionInfo;
		
	};
	
	
	
	/* Asset IO exception */
	class AssetIOException : public AssetException {
	public:
		
		AssetIOException(const std::ios::failure &fail);
		
	};
	
	
	
} // namespace Graphics



#include <fstream>

template<class T>
T* Graphics::AssetStorage::grab(const std::string &key)
{
	Graphics::Asset* a = get(key);
	if (a == nullptr) storage[key] = (a = load<T>(key));
	a->assetCount++;
	return dynamic_cast<T*>(a);
}

template<class T>
T* Graphics::AssetStorage::load(const std::string &key)
{
	try {
		std::ifstream stream;
		stream.exceptions(std::ifstream::failbit);
		stream.open(key, std::ios::binary);
		T* a = new T(this, key, static_cast<const std::istream>(stream));
		stream.close();
		return a;
	} catch (std::ios::failure &fail) {
		throw Graphics::AssetIOException(fail);
	}
}



#endif // _GRAPHICS_ASSETSTORAGE_HPP_
