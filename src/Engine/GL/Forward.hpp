#pragma once
#ifndef _ENGINE_GL_FORWARD_HPP_
#define _ENGINE_GL_FORWARD_HPP_

/* Forward declarations */

namespace Engine { namespace GL {
	
	
	
	/* Core.hpp */
	class Object;
	class BaseException;
	
	/* Shader.hpp */
	class Shader;
	class ShaderFile;
	class VertexShader;
	class FragmentShader;
	class GeometryShader;
	class ShaderCompileException;
	
	/* Program.hpp */
	class Program;
	class ProgramLinkException;
	
	/* Uniform.hpp */
	class ProgramUniform;
	
	/* Buffer.hpp */
	class Buffer;
	class ElementBuffer;
	class ElementBuffer8;
	class ElementBuffer16;
	class ElementBuffer32;
	class ArrayBuffer;
	class UniformBuffer;
	
	/* Texture.hpp */
	class Texture;
	class Texture1D;
	class Texture2D;
	class Texture3D;
	
	/* VAO.hpp */
	class VAO;
	
	/* FrameBuffer.hpp */
	class FrameBuffer;
	
	
	
}} // namespace Engine::GL

#endif // _ENGINE_GL_FORWARD_HPP_
