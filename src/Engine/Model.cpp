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

Engine::GL::Texture2D* createPixelTexture(float r, float g, float b) {
	std::vector<float> pixels(3);
	pixels[0] = r;
	pixels[1] = g;
	pixels[2] = b;
	return new Engine::GL::Texture2D(1, 1, GL_RGB, GL_FLOAT, pixels.data(), false);
}

Engine::GL::Texture2D* createPixelTexture(float r) {
	return new Engine::GL::Texture2D(1, 1, GL_RED, GL_FLOAT, &r, false);
}

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
		object.specular_exp = obj.specular_exp;
		
		if (!obj.diffuse_map.empty()) {
			object.diffuseCFRT = &engine.storage.grab<Asset::CFRTexture2D>(obj.diffuse_map);
			object.diffuse = &object.diffuseCFRT->get();
		} else {
			object.diffuse = createPixelTexture(obj.diffuse.x, obj.diffuse.y, obj.diffuse.z);
		}
		
		if (!obj.normal_map.empty()) {
			object.normalCFRT = &engine.storage.grab<Asset::CFRTexture2D>(obj.normal_map);
			object.normal = &object.normalCFRT->get();
		} else {
			object.normal = createPixelTexture(.5f, .5f, 1.f);
		}
		
		if (!obj.specular_map.empty()) {
			object.specularCFRT = &engine.storage.grab<Asset::CFRTexture2D>(obj.specular_map);
			object.specular = &object.specularCFRT->get();
		} else {
			object.specular = createPixelTexture(obj.specular.x, obj.specular.y, obj.specular.z);
		}
		
		if (!obj.mask_map.empty()) {
			object.maskCFRT = &engine.storage.grab<Asset::CFRTexture2D>(obj.mask_map);
			object.mask = &object.maskCFRT->get();
		} else {
			object.mask = createPixelTexture(1.f);
		}
		
		if (!obj.emit_map.empty()) {
			object.emitCFRT = &engine.storage.grab<Asset::CFRTexture2D>(obj.emit_map);
			object.emit = &object.emitCFRT->get();
		} else {
			object.emit = createPixelTexture(obj.emit.x, obj.emit.y, obj.emit.z);
		}
		
		object.diffuse->bind();
		if (ogl_ext_EXT_texture_filter_anisotropic != ogl_LOAD_FAILED) {
			float aniso = 0.f;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		object.diffuse->unbind();
		
		object.normal->bind();
		if (ogl_ext_EXT_texture_filter_anisotropic != ogl_LOAD_FAILED) {
			float aniso = 0.f;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		object.normal->unbind();
		
		object.specular->bind();
		if (ogl_ext_EXT_texture_filter_anisotropic != ogl_LOAD_FAILED) {
			float aniso = 0.f;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		object.specular->unbind();
		
		object.mask->bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		object.mask->unbind();
		
		object.emit->bind();
		if (ogl_ext_EXT_texture_filter_anisotropic != ogl_LOAD_FAILED) {
			float aniso = 0.f;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		object.emit->unbind();
		
		objects.push_back(object);
	}
}

Model::~Model()
{
	engine.storage.release(*model);
	for (std::size_t i = 0; i < objects.size(); i++) {
		if (objects[i].diffuseCFRT == nullptr) delete objects[i].diffuse;
		else engine.storage.release(*objects[i].diffuseCFRT);
		
		if (objects[i].normalCFRT == nullptr) delete objects[i].normal;
		else engine.storage.release(*objects[i].normalCFRT);
		
		if (objects[i].specularCFRT == nullptr) delete objects[i].specular;
		else engine.storage.release(*objects[i].specularCFRT);
		
		if (objects[i].maskCFRT == nullptr) delete objects[i].mask;
		else engine.storage.release(*objects[i].maskCFRT);
		
		if (objects[i].emitCFRT == nullptr) delete objects[i].emit;
		else engine.storage.release(*objects[i].emitCFRT);
	}
}

void Model::draw(Scene &scene)
{
	for (std::size_t i = 0; i < objects.size(); i++) {
		
		scene.uModelSpecularExp.set1f(objects[i].specular_exp);
		
		glActiveTexture(GL_TEXTURE0);
		objects[i].diffuse->bind();
		scene.uDiffuseSampler.set1i(0);
		
		glActiveTexture(GL_TEXTURE1);
		objects[i].normal->bind();
		scene.uNormalSampler.set1i(1);
		
		glActiveTexture(GL_TEXTURE2);
		objects[i].specular->bind();
		scene.uSpecularSampler.set1i(2);
		
		glActiveTexture(GL_TEXTURE3);
		objects[i].mask->bind();
		scene.uMaskSampler.set1i(3);
		
		glActiveTexture(GL_TEXTURE4);
		objects[i].emit->bind();
		scene.uEmitSampler.set1i(4);
		
		objects[i].geometry->get().draw(
			GL_TRIANGLES,
			objects[i].end - objects[i].start,
			objects[i].start
		);
		
		objects[i].emit->unbind();
		objects[i].mask->unbind();
		objects[i].specular->unbind();
		objects[i].normal->unbind();
		objects[i].diffuse->unbind();
	}
}
