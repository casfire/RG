#pragma once
#ifndef _ENGINE_ASSET_GLPROGRAM_HPP_
#define _ENGINE_ASSET_GLPROGRAM_HPP_

#include "Common.hpp"
#include "../GL/Shader.hpp"
#include "../GL/Program.hpp"
#include <istream>
#include <vector>

namespace Engine { namespace Asset {
	
	
	
	class GLProgram;
	class GLVertexShader;
	class GLFragmentShader;
	class GLGeometryShader;
	
	
	
	/* GLSL program */
	class GLProgram : public virtual Asset {
	public:
		
		/* Create, delete, load */
		GLProgram();
		~GLProgram();
		void load(Storage& storage, std::istream& stream) override;
		void unload(Storage& storage) override;
		
		/* Get program */
		const GL::Program& get();
		
	private:
		
		GL::Program program;
		std::vector<Asset*> shaders;
		
	};
	
	
	
	/* Vertex shader */
	class GLVertexShader : public virtual Asset {
	public:
		
		/* Create, delete, load */
		GLVertexShader();
		~GLVertexShader();
		void load(Storage& storage, std::istream& stream) override;
		
		/* Get shader */
		const GL::VertexShader& get();
		
	private:
		
		GL::VertexShader shader;
		
	};
	
	
	
	/* Fragment shader */
	class GLFragmentShader : public virtual Asset {
	public:
		
		/* Create, delete, load */
		GLFragmentShader();
		~GLFragmentShader();
		void load(Storage& storage, std::istream& stream) override;
		
		/* Get shader */
		const GL::FragmentShader& get();
		
	private:
		
		GL::FragmentShader shader;
		
	};
	
	
	
	/* Geometry shader */
	class GLGeometryShader : public virtual Asset {
	public:
		
		/* Create, delete, load */
		GLGeometryShader();
		~GLGeometryShader();
		void load(Storage& storage, std::istream& stream) override;
		
		/* Get shader */
		const GL::GeometryShader& get();
		
	private:
		
		GL::GeometryShader shader;
		
	};
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_GLPROGRAM_HPP_
