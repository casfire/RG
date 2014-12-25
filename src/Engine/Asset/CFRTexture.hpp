#pragma once
#ifndef _ENGINE_ASSET_CFRTEXTURE_HPP_
#define _ENGINE_ASSET_CFRTEXTURE_HPP_

#include "Common.hpp"
#include "../GL/Texture.hpp"
#include <istream>

namespace Engine { namespace Asset {
	
	
	
	/* CFR 1D Texture asset */
	class CFRTexture1D : public virtual Asset {
	public:
		
		/* Load texture */
		void load(Storage &storage, std::istream &stream) override;
		
		/* Return loaded texture */
		const GL::Texture1D& get();
		
	private:
		
		GL::Texture1D texture;
		
	};
	
	
	
	/* CFR 2D Texture asset */
	class CFRTexture2D : public virtual Asset {
	public:
		
		/* Load texture */
		void load(Storage &storage, std::istream &stream) override;
		
		/* Return loaded texture */
		const GL::Texture2D& get();
		
	private:
		
		GL::Texture2D texture;
		
	};
	
	
	
	/* CFR 3D Texture asset */
	class CFRTexture3D : public virtual Asset {
	public:
		
		/* Load texture */
		void load(Storage &storage, std::istream &stream) override;
		
		/* Return loaded texture */
		const GL::Texture3D& get();
		
	private:
		
		GL::Texture3D texture;
		
	};
	
	
	
	/*
		CFR texture file format
		Byte order: little endian
		
		uint32_t  magic   = 0x54524643; // CFRT
		uint8_t   version = 1;
		uint16_t  width;    // Texture width in pixels
		uint16_t  height;   // Texture height in pixels
		uint16_t  depth;    // Texture depth in pixels
		uint8_t   channels; // Number of channels (1, 2, 3 or 4)
		uint8_t   bytes;    // Number of bytes per color (1, 2 or 4)
		uint8_t   pixels[width * height * depth * channels * bytes];
		
	*/
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_CFRTEXTURE_HPP_
