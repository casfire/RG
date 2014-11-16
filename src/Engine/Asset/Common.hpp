#pragma once
#ifndef _ENGINE_ASSET_COMMON_HPP_
#define _ENGINE_ASSET_COMMON_HPP_

#include <string>
#include <exception>
#include <vector>
#include <ios> // std::ios::failure
#include <cstddef> // std::size_t

namespace Engine { namespace Asset {
	
	
	
	class Asset;
	class Exception;
	class IOException;
	class CastException;
	class LoadException;
	class Storage;
	
	
	
	/* Base asset class */
	class Asset {
	protected:
		
		/* Only derived assets can be constructed */
		Asset();
		
		/* Virtual destructor so derived assets can be deleted */
		virtual ~Asset();
		
		/* Pure virtual method for asset deserialization */
		virtual void load(Storage& storage, std::istream &in) = 0;
		
	private:
		
		/* Asset key set by Storage */
		std::string key;
		
		/* Grab count set by Storage */
		std::size_t grabCount;
		
		/* Storage must have access to grab count and asset key */
		friend class Storage;
		
		/* Prevent copying */
		Asset(const Asset&) = delete;
		Asset& operator=(const Asset&) = delete;
		
	};
	
	
	
	/* Base asset exception */
	class Exception : public std::exception {
	public:
		
		/* Return saved information */
		const char* what() const throw();
		
	protected:
		
		/* Create exception and save information */
		Exception(const std::string &info);
		
	private:
		
		/* Saved exception information */
		std::string info;
		
		/* Asset keys */
		std::vector<std::string> keys;
		void pushKey(const std::string &key);
		
		/* Storage must be able to push keys */
		friend class Storage;
		
	};
	
	
	
	/* Thrown when IO exception occurs */
	class IOException : public Exception {
	public:
		
		IOException(const std::ios::failure &fail);
		
	};
	
	
	
	/* Thrown when asset type casting fails */
	class CastException : public Exception {
	public:
		
		CastException(const char *from, const char *to);
		
	};
	
	
	
	/* Thrown when asset load fails */
	class LoadException : public Exception {
	public:
		
		LoadException(const std::string &info);
		
	};
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_COMMON_HPP_
