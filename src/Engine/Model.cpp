#include "Model.hpp"
#include "MainEngine.hpp"
#include "Scene.hpp"
#include "GL/GL.hpp"
#include "Asset/CFRModel.hpp"
#include "Asset/CFRGeometry.hpp"
#include "Asset/CFRTexture.hpp"

using Engine::MainEngine;
using Engine::Node;
using Engine::Camera;
using Engine::Scene;
using Engine::Model;
using Engine::ModelObject;

Model::Model(MainEngine &engine, const std::string &file)
: engine(engine)
{
	model = &engine.storage.grab<Asset::CFRModel>(file);
	for (std::size_t i = 0; i < model->count(); i++) {
		const Asset::CFRModelObject& obj = model->get(i);
		ModelObject object;
		object.geometry = &engine.storage.grab<Asset::CFRGeometry>(obj.geometry);
		object.start    = obj.start;
		object.end      = obj.end;
		object.emit     = obj.emit;
		object.shine    = obj.shine;
		
		if (!obj.diffuse_map.empty()) {
			object.diffuseCFRT = &engine.storage.grab<Asset::CFRTexture2D>(obj.diffuse_map);
			object.diffuse = &object.diffuseCFRT->get();
		} else {
			std::vector<float> pixels(3);
			pixels[0] = obj.diffuse.x;
			pixels[1] = obj.diffuse.y;
			pixels[2] = obj.diffuse.z;
			object.diffuse = new GL::Texture2D(1, 1, GL_RGB, GL_FLOAT, pixels.data(), false);
		}
		
		if (!obj.normal_map.empty()) {
			object.normalCFRT = &engine.storage.grab<Asset::CFRTexture2D>(obj.normal_map);
			object.normal = &object.normalCFRT->get();
		} else {
			std::vector<float> pixels(3);
			pixels[0] = 0.5;
			pixels[1] = 0.5;
			pixels[2] = 1.0;
			object.normal = new GL::Texture2D(1, 1, GL_RGB, GL_FLOAT, pixels.data(), false);
		}
		
		object.diffuse->bind();
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		object.diffuse->unbind();
		
		object.normal->bind();
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		object.normal->unbind();
		
		objects.push_back(object);
	}
}

Model::~Model()
{
	engine.storage.release(*model);
	for (std::size_t i = 0; i < objects.size(); i++) {
		if (objects[i].diffuseCFRT == nullptr) {
			delete objects[i].diffuse;
		} else {
			engine.storage.release(*objects[i].diffuseCFRT);
		}
	}
}

void Model::draw(Scene &scene)
{
	for (std::size_t i = 0; i < objects.size(); i++) {
		
		scene.uModelEmit ->set1f(objects[i].emit);
		scene.uModelShine->set1f(objects[i].shine);
		
		glActiveTexture(GL_TEXTURE0);
		objects[i].diffuse->bind();
		scene.uDiffuseSampler->set1i(GL_TEXTURE0);
		
		glActiveTexture(GL_TEXTURE1);
		objects[i].normal->bind();
		scene.uNormalSampler->set1i(1);
		
		objects[i].geometry->get().draw(
			GL_TRIANGLES,
			objects[i].end - objects[i].start,
			objects[i].start
		);
		
		objects[i].normal->unbind();
		objects[i].diffuse->unbind();
	}
}
