#pragma once
#ifndef _ENGINE_ASSET_TEXT_HPP_
#define _ENGINE_ASSET_TEXT_HPP_

#include "Forward.hpp"
#include "Base.hpp"
#include <istream>
#include <vector>
#include <string>

namespace Engine { namespace Asset {
	
	
	
	/* Base raw text asset */
	class TextRaw : public BaseAsset {
	public:
		
		/* Load raw file */
		void load(Storage &storage, std::istream &stream) override;
		
	protected:
		
		/* Called when file is loaded entirely (adds '\0' at the end) */
		virtual void load(Storage &storage, std::vector<char> &data) = 0;
		
	};
	
	
	
	/* Base tokenizer asset */
	class TextTokenizer : public BaseAsset {
	public:
		
		/* Parse tokens */
		void load(Storage &storage, std::istream &stream) override;
		
	protected:
		
		/* Called before any tokens */
		virtual void loadBegin(Storage &storage) = 0;
		
		/* Called when there are no more tokens */
		virtual void loadEnd(Storage &storage) = 0;
		
		/* Called for each token */
		virtual void loadToken(
			Storage &storage,
			const std::string &token,
			const std::string &contents
		) = 0;
		
	};
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_TEXT_HPP_
