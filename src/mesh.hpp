#include <glm/vec3.hpp>

class Mesh {
protected:
	
	GL::VAO vao;
	std::vector<float> vertexBuffer;
	std::vector<std::uint32_t> elementBuffer;
	
	void addVertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color) {
		vertexBuffer.push_back(position.x);
		vertexBuffer.push_back(position.y);
		vertexBuffer.push_back(position.z);
		vertexBuffer.push_back(normal.x);
		vertexBuffer.push_back(normal.y);
		vertexBuffer.push_back(normal.z);
		vertexBuffer.push_back(color.x);
		vertexBuffer.push_back(color.y);
		vertexBuffer.push_back(color.z);
	}
	
	void addTriangle(std::uint32_t a, std::uint32_t b, std::uint32_t c) {
		elementBuffer.push_back(a);
		elementBuffer.push_back(b);
		elementBuffer.push_back(c);
	}
	
public:
	
	void create(const std::string& objfile) {
		
		Obj::TriangleReader obj;
		obj.read(objfile, std::cout);
		for (std::size_t i = 0; i < obj.vertices().size(); i++) {
			Obj::Vertex::Geometry position = obj.vertices()[i].geometry;
			Obj::Vertex::Normal normal = obj.vertices()[i].normal;
			addVertex(
				glm::vec3(position.x, position.y, position.z),
				glm::vec3(normal.i, normal.j, normal.k),
				glm::vec3(0.5, 0.8, 0.3)
			);
		}
		for (std::size_t i = 0; i < obj.triangles().size(); i++) {
			addTriangle(
				obj.triangles()[i].a,
				obj.triangles()[i].c,
				obj.triangles()[i].b
			);
		}
		obj.clear();
		
		GL::ArrayBuffer vertexBufferGL(sizeof(float) * vertexBuffer.size(), &vertexBuffer[0]);
		vao.set(GL::ElementBuffer32(elementBuffer.size(), &elementBuffer[0]));
		vao.attribute(0, vertexBufferGL, GL_FLOAT, 3, 9 * sizeof(float), 0);
		vao.attribute(1, vertexBufferGL, GL_FLOAT, 3, 9 * sizeof(float), 3 * sizeof(float));
		vao.attribute(2, vertexBufferGL, GL_FLOAT, 3, 9 * sizeof(float), 6 * sizeof(float));
		vao.enable(0);
		vao.enable(1);
		vao.enable(2);
		
		vertexBuffer.clear();
		elementBuffer.clear();
	}
	
	void draw() {
		vao.drawTriangles();
	}
	
};