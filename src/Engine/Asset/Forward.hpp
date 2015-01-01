#pragma once
#ifndef _ENGINE_ASSET_FORWARD_HPP_
#define _ENGINE_ASSET_FORWARD_HPP_

/* Forward declarations */

namespace Engine { namespace Asset {
	
	
	
	/* Base.hpp */
	class BaseAsset;
	class BaseException;
	class IOException;
	class CastException;
	class LoadException;
	
	/* Text.hpp */
	class TextRaw;
	class TextTokenizer;
	
	/* Storage.hpp */
	class Storage;
	
	/* GLProgram.hpp */
	class GLProgram;
	class GLVertexShader;
	class GLFragmentShader;
	class GLGeometryShader;
	
	/* CFRTexture.hpp */
	class CFRTexture1D;
	class CFRTexture2D;
	class CFRTexture3D;
	
	/* CFRGeometry.hpp */
	class CFRGeometry;
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_FORWARD_HPP_
