#pragma once
#ifndef _GRAPHICS_ASSET_GLPROGRAM_HPP_
#define _GRAPHICS_ASSET_GLPROGRAM_HPP_

#include "Common.hpp"
#include "../GL/Shader.hpp"
#include "../GL/Program.hpp"
#include <istream>

namespace Graphics { namespace Asset {
	
	
	
	class GLVertexShader;
	class GLFragmentShader;
	class GLGeometryShader;
	class GLProgram;
	
	
	
	/* Vertex shader */
	class GLVertexShader : public Asset {
	public:
		
		/* Create asset */
		GLVertexShader(Storage* storage, std::istream& stream);
		
		/* Delete asset */
		~GLVertexShader();
		
		/* Get shader */
		const GL::VertexShader& get();
		
	private:
		
		GL::VertexShader shader;
		
	};
	
	
	
	/* Fragment shader */
	class GLFragmentShader : public Asset {
	public:
		
		/* Create asset */
		GLFragmentShader(Storage* storage, std::istream& stream);
		
		/* Delete asset */
		~GLFragmentShader();
		
		/* Get shader */
		const GL::FragmentShader& get();
		
	private:
		
		GL::FragmentShader shader;
		
	};
	
	
	
	/* Geometry shader */
	class GLGeometryShader : public Asset {
	public:
		
		/* Create asset */
		GLGeometryShader(Storage* storage, std::istream& stream);
		
		/* Delete asset */
		~GLGeometryShader();
		
		/* Get shader */
		const GL::GeometryShader& get();
		
	private:
		
		GL::GeometryShader shader;
		
	};
	
	
	
	/* GLSL program */
	class GLProgram : public Asset {
	public:
		
		/* Create asset */
		GLProgram(Storage* storage, std::istream& stream);
		
		/* Delete asset */
		~GLProgram();
		
		/* Get program */
		const GL::Program& get();
		
	private:
		
		GL::Program program;
		
	};
	
	
	
}} // namespace Graphics::Asset

#endif // _GRAPHICS_ASSET_GLPROGRAM_HPP_
