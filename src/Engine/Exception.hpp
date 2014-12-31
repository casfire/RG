#pragma once
#ifndef _ENGINE_EXCEPTION_HPP_
#define _ENGINE_EXCEPTION_HPP_

#include "Forward.hpp"
#include <exception>
#include <string>

namespace Engine {
	
	
	
	/* Base exception */
	class BaseException : public std::exception {
	public:
		
		/* Create exception and save information */
		BaseException(const std::string &info);
		
		/* Return saved information */
		const char* what() const throw();
		
	private:
		
		/* Saved information */
		const std::string info;
		
	};
	
	
	
	/* Thrown when engine initialization fails */
	class EngineInitException : public BaseException {
	public:
		
		/* Create exception */
		EngineInitException(const std::string &info);
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_EXCEPTION_HPP_
