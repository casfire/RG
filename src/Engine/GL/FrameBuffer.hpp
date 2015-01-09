#pragma once
#ifndef _ENGINE_GL_FRAMEBUFFER_HPP_
#define _ENGINE_GL_FRAMEBUFFER_HPP_

#include "Forward.hpp"
#include "Core.hpp"

namespace Engine { namespace GL {
	
	
	
	/* Frame buffer object */
	class FrameBuffer : public Object {
	public:
		
		FrameBuffer();
		~FrameBuffer();
		
		void bind() const;
		void unbind() const;
		
	};
	
	
	
}} // namespace Engine::GL

#endif // _ENGINE_GL_FRAMEBUFFER_HPP_
