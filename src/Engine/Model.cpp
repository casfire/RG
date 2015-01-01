#include "Model.hpp"
#include "MainEngine.hpp"
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
		object.diffuse = obj.diffuse;
		objects.push_back(object);
	}
}

Model::~Model()
{
	engine.storage.release(*model);
}

void Model::draw()
{
	for (std::size_t i = 0; i < objects.size(); i++) {
		objects[i].geometry->get().drawTriangles();
	}
}
