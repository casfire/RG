#pragma once
#ifndef _ENGINE_GL_PROGRAM_HPP_
#define _ENGINE_GL_PROGRAM_HPP_

#include "Forward.hpp"
#include "Core.hpp"
#include <vector>

namespace Engine { namespace GL {
	
	
	
	/* GLSL program object */
	class Program : public Object {
	public:
		
		/* Create a new program */
		Program();
		
		/* Delete program */
		~Program();
		
		/* Create and link a new program - throws ProgramLinkException */
		Program(
			const VertexShader   &vertex,
			const FragmentShader &fragment
		);
		Program(
			const VertexShader   &vertex,
			const FragmentShader &fragment,
			const GeometryShader &geometry
		);
		
		/* Attach a shader */
		void attach(const Shader &shader);
		
		/* Detach a shader */
		void detach(const Shader &shader);
		
		/* Link attached shaders - throws ProgramLinkException */
		void link();
		
		/* Use this program */
		void bind() const;
		
		/* Stop using program */
		void unbind() const;
		
		/* Getters */
		bool isLinked() const;
		bool isAttached(const Shader &shader) const;
		
		/* Retrieve uniform variable */
		ProgramUniform getUniform(const GLchar *name) const;
		
	};
	
	
	
	/* Exception thrown when program link fails */
	class ProgramLinkException : public Exception {
	public:
		
		/* Return entire link log */
		const char* log() const;
		
	private:
		
		friend class Program;
		std::vector<char> linkLog;
		ProgramLinkException(const Program &program);
		
	};
	
	
	
}} // namespace Engine::GL

#endif // _ENGINE_GL_PROGRAM_HPP_
