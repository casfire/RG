#pragma once
#ifndef _ENGINE_ASSET_IMAGETGA_HPP_
#define _ENGINE_ASSET_IMAGETGA_HPP_

#include "Common.hpp"
#include <istream>
#include <cstdint>
#include <vector>

namespace Engine { namespace Asset {
	
	
	
	/* TGA image asset */
	class ImageTGA : public virtual Asset {
	public:
		
		ImageTGA();
		
		/* Load TGA */
		void load(Storage& storage, std::istream& stream) override;
		
		/* Getters */
		const uint8_t* getPixels() const;
		uint8_t  getBitsPerPixel() const;
		uint16_t getWidth() const;
		uint16_t getHeight() const;
		
	private:
		
		uint8_t bpp;
		uint16_t width, height;
		std::vector<uint8_t> pixels;
		
	};
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_IMAGETGA_HPP_
