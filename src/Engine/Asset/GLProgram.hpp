#pragma once
#ifndef _ENGINE_ASSET_GLPROGRAM_HPP_
#define _ENGINE_ASSET_GLPROGRAM_HPP_

#include "Forward.hpp"
#include "Base.hpp"
#include "../GL/Shader.hpp"
#include "../GL/Program.hpp"
#include <istream>
#include <vector>

namespace Engine { namespace Asset {
	
	
	
	/* GLSL program */
	class GLProgram : public BaseAsset {
	public:
		
		/* Load program */
		void load(Storage &storage, std::istream &stream) override;
		
		/* Release all shaders */
		void unload(Storage &storage) override;
		
		/* Get program */
		const GL::Program& get();
		
	private:
		
		GL::Program program;
		std::vector<BaseAsset*> shaders;
		
	};
	
	
	
	/* Vertex shader */
	class GLVertexShader : public BaseAsset {
	public:
		
		/* Load shader */
		void load(Storage &storage, std::istream &stream) override;
		
		/* Get shader */
		const GL::VertexShader& get();
		
	private:
		
		GL::VertexShader shader;
		
	};
	
	
	
	/* Fragment shader */
	class GLFragmentShader : public BaseAsset {
	public:
		
		/* Load shader */
		void load(Storage &storage, std::istream &stream) override;
		
		/* Get shader */
		const GL::FragmentShader& get();
		
	private:
		
		GL::FragmentShader shader;
		
	};
	
	
	
	/* Geometry shader */
	class GLGeometryShader : public BaseAsset {
	public:
		
		/* Load shader */
		void load(Storage &storage, std::istream &stream) override;
		
		/* Get shader */
		const GL::GeometryShader& get();
		
	private:
		
		GL::GeometryShader shader;
		
	};
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_GLPROGRAM_HPP_
