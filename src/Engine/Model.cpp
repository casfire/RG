#include "Model.hpp"
#include "MainEngine.hpp"
#include "Asset/CFRGeometry.hpp"

using Engine::MainEngine;
using Engine::Node;
using Engine::Camera;
using Engine::Scene;
using Engine::Model;

Model::Model(MainEngine &engine, const std::string &file)
: engine(engine)
{
	geometry = &engine.storage.grab<Asset::CFRGeometry>(file);	
}

Model::~Model()
{
	engine.storage.release(*geometry);
}

void Model::draw()
{
	geometry->get().drawTriangles();
}
