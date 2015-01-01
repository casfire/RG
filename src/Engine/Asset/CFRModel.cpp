#include "CFRModel.hpp"
#include <sstream>
#include "Storage.hpp"

using Engine::Asset::CFRModel;
using Engine::Asset::CFRModelObject;
using Engine::Asset::LoadException;

std::size_t CFRModel::count() const
{
	return objects.size();
}

const CFRModelObject& CFRModel::get(std::size_t index) const
{
	return objects[index];
}

void CFRModel::loadBegin(Storage&)
{
	version = 0;
	resetCurrent();
}

void CFRModel::loadEnd(Storage&)
{
	if (current.end <= current.start) return;
	objects.push_back(current);
	resetCurrent();
}

void CFRModel::resetCurrent()
{
	current.start = 0;
	current.end = 0;
	current.diffuse = glm::vec3(0, 0, 0);
	current.diffuse_map = "";
	current.normal_map = "";
}

void CFRModel::loadToken(
	Storage &storage,
	const std::string &key,
	const std::string &value)
{
	std::stringstream stream(value);
	if (key.compare("version") == 0) {
		if (version != 0) throw LoadException("Multiple versions.");
		stream >> version;
		if (version != 1) throw LoadException("Invalid version.");
		return;
	}
	if (version == 0) throw LoadException("Version not found.");
	if (key.compare("geometry") == 0) {
		current.geometry = storage.getPath() + value;
	} else if (key.compare("range") == 0) {
		stream >> current.start >> current.end;
	} else if (key.compare("diffuse") == 0) {
		stream >> current.diffuse.x >> current.diffuse.y >> current.diffuse.z;
	} else if (key.compare("diffuse_map") == 0) {
		current.diffuse_map = storage.getPath() + value;
	} else if (key.compare("normal_map") == 0) {
		current.normal_map = storage.getPath() + value;
	} else if (key.compare("end") == 0) {
		loadEnd(storage);
	}
}
