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
		object.start = obj.start;
		object.end = obj.end;
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
		object.diffuse->bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		object.diffuse->unbind();
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
		glActiveTexture(GL_TEXTURE0);
		objects[i].diffuse->bind();
		scene.uDiffuseSampler->set1i(GL_TEXTURE0);
		objects[i].geometry->get().draw(
			GL_TRIANGLES,
			objects[i].end - objects[i].start,
			objects[i].start
		);
		objects[i].diffuse->unbind();
	}
}
