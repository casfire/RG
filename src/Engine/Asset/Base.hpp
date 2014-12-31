#pragma once
#ifndef _ENGINE_ASSET_BASE_HPP_
#define _ENGINE_ASSET_BASE_HPP_

#include "Forward.hpp"
#include <string>
#include <exception>
#include <ios> // std::ios::failure
#include <cstddef> // std::size_t

namespace Engine { namespace Asset {
	
	
	
	/* Base asset class */
	class BaseAsset {
	protected:
		
		/* Only derived assets can be constructed */
		BaseAsset();
		
		/* Virtual destructor so derived assets can be deleted */
		virtual ~BaseAsset();
		
		/* Called by Storage to load this asset */
		virtual void load(Storage &storage, std::istream &in) = 0;
		
		/* Called by Storage before deleting this asset */
		virtual void unload(Storage &storage);
		
	private:
		
		/* File set by Storage */
		std::string file;
		
		/* Grab count set by Storage */
		std::size_t grabCount;
		
		/* Storage must have access to grab count and file */
		friend class Storage;
		
		/* Prevent copying */
		BaseAsset(const BaseAsset&) = delete;
		BaseAsset& operator=(const BaseAsset&) = delete;
		
	};
	
	
	
	/* Base asset exception */
	class BaseException : public std::exception {
	public:
		
		/* Return saved information */
		const char* what() const throw();
		
	protected:
		
		/* Create exception and save information */
		BaseException(const std::string& info);
		
	private:
		
		/* Saved exception information */
		std::string info;
		
		/* Called by Storage when unwinding the file stack */
		void pushFile(const std::string &file);
		friend class Storage;
		
	};
	
	
	
	/* Thrown when IO exception occurs */
	class IOException : public BaseException {
	public:
		
		IOException(const std::ios::failure &fail);
		
	};
	
	
	
	/* Thrown when asset type casting fails */
	class CastException : public BaseException {
	public:
		
		CastException(const char *from, const char *to);
		
	};
	
	
	
	/* Thrown when asset load fails */
	class LoadException : public BaseException {
	public:
		
		LoadException(const std::string &info);
		
	};
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_BASE_HPP_
