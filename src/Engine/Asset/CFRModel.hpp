#pragma once
#ifndef _ENGINE_ASSET_CFRMODEL_HPP_
#define _ENGINE_ASSET_CFRMODEL_HPP_

#include "Forward.hpp"
#include "Text.hpp"
#include <string>
#include <glm/vec3.hpp>
#include <cstddef> // std::size_t
#include <vector>

namespace Engine { namespace Asset {
	
	
	
	/* CFR Model */
	struct CFRModelObject {
		std::string geometry;
		std::size_t start, end;
		glm::vec3   diffuse;
		std::string diffuse_map;
		std::string normal_map;
		float       specular;
		float       specular_exp;
		std::string specular_map;
		std::string mask_map;
		float emit;
	};
	
	
	
	/* CFR Model asset */
	class CFRModel : public TextTokenizer {
	public:
		
		/* Get number of objects */
		std::size_t count() const;
		
		/* Get model */
		const CFRModelObject& get(std::size_t index) const;
		
		/* Load objects */
		void loadBegin(Storage &storage) override;
		void loadEnd(Storage &storage) override;
		void loadToken(
			Storage &storage,
			const std::string &key,
			const std::string &value
		) override;
		
	private:
		
		std::vector<CFRModelObject> objects;
		int version;
		std::string geometry;
		CFRModelObject current;
		void resetCurrent();
		void addCurrent();
		
	};
	
	
	
}} // namespace Engine::Asset

#endif
