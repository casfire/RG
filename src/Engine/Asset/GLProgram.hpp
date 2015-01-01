#pragma once
#ifndef _ENGINE_ASSET_GLPROGRAM_HPP_
#define _ENGINE_ASSET_GLPROGRAM_HPP_

#include "Forward.hpp"
#include "Text.hpp"
#include "../GL/Shader.hpp"
#include "../GL/Program.hpp"
#include <istream>
#include <vector>

namespace Engine { namespace Asset {
	
	
	
	/* GLSL program */
	class GLProgram : public TextTokenizer {
	public:
		
		/* Load program */
		void loadBegin(Storage &storage) override;
		void loadEnd(Storage &storage) override;
		void loadToken(
			Storage &storage,
			const std::string &key,
			const std::string &value
		) override;
		
		/* Release all shaders */
		void unload(Storage &storage) override;
		
		/* Get program */
		const GL::Program& get();
		
	private:
		
		GL::Program program;
		std::vector<BaseAsset*> shaders;
		
	};
	
	
	
	/* Vertex shader */
	class GLVertexShader : public TextRaw {
	public:
		
		/* Load shader */
		void load(Storage &storage, std::vector<char> &data) override;
		
		/* Get shader */
		const GL::VertexShader& get();
		
	private:
		
		GL::VertexShader shader;
		
	};
	
	
	
	/* Fragment shader */
	class GLFragmentShader : public TextRaw {
	public:
		
		/* Load shader */
		void load(Storage &storage, std::vector<char> &data) override;
		
		/* Get shader */
		const GL::FragmentShader& get();
		
	private:
		
		GL::FragmentShader shader;
		
	};
	
	
	
	/* Geometry shader */
	class GLGeometryShader : public TextRaw {
	public:
		
		/* Load shader */
		void load(Storage &storage, std::vector<char> &data) override;
		
		/* Get shader */
		const GL::GeometryShader& get();
		
	private:
		
		GL::GeometryShader shader;
		
	};
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_GLPROGRAM_HPP_
