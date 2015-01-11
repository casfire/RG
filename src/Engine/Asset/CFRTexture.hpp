#pragma once
#ifndef _ENGINE_ASSET_CFRTEXTURE_HPP_
#define _ENGINE_ASSET_CFRTEXTURE_HPP_

#include "Forward.hpp"
#include "Base.hpp"
#include "../GL/Texture.hpp"
#include <istream>

namespace Engine { namespace Asset {
	
	
	
	/* CFR 1D Texture asset */
	class CFRTexture1D : public BaseAsset, public GL::Texture1D {
	public:
		
		/* Load texture */
		void load(Storage &storage, std::istream &stream) override;
		
	};
	
	
	
	/* CFR 2D Texture asset */
	class CFRTexture2D : public BaseAsset, public GL::Texture2D {
	public:
		
		/* Load texture */
		void load(Storage &storage, std::istream &stream) override;
		
	};
	
	
	
	/* CFR 3D Texture asset */
	class CFRTexture3D : public BaseAsset, public GL::Texture3D {
	public:
		
		/* Load texture */
		void load(Storage &storage, std::istream &stream) override;
		
	};
	
	
	
	/*
		CFR texture file format
		Byte order: little endian
		
		Uint32  magic   = 0x54524643; // CFRT
		Uint32  version = 1;
		Uint16  width;    // Texture width  in pixels
		Uint16  height;   // Texture height in pixels
		Uint16  depth;    // Texture depth  in pixels
		Uint8   channels; // Number of channels (1, 2, 3 or 4)
		Uint8   bytes;    // Number of bytes per color (1, 2 or 4)
		Uint8   pixels[width * height * depth * channels * bytes];
		
	*/
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_CFRTEXTURE_HPP_
