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
	class GLProgram : public TextTokenizer, public GL::Program {
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
		
	private:
		
		std::vector<BaseAsset*> shaders;
		
	};
	
	
	
	/* Vertex shader */
	class GLVertexShader : public TextRaw, public GL::VertexShader {
	public:
		
		/* Load shader */
		void load(Storage &storage, std::vector<char> &data) override;
		
	};
	
	
	
	/* Fragment shader */
	class GLFragmentShader : public TextRaw, public GL::FragmentShader {
	public:
		
		/* Load shader */
		void load(Storage &storage, std::vector<char> &data) override;
		
	};
	
	
	
	/* Geometry shader */
	class GLGeometryShader : public TextRaw, public GL::GeometryShader {
	public:
		
		/* Load shader */
		void load(Storage &storage, std::vector<char> &data) override;
		
	};
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_GLPROGRAM_HPP_
