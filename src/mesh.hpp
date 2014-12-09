#include <glm/vec3.hpp>

class Mesh {
protected:
	
	GL::VAO vao;
	std::uint32_t triangleCount, vertexCount;
	std::vector<float> vertexBuffer;
	std::vector<std::uint32_t> elementBuffer;
	
	std::uint32_t addVertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color) {
		vertexBuffer.push_back(position.x);
		vertexBuffer.push_back(position.y);
		vertexBuffer.push_back(position.z);
		vertexBuffer.push_back(normal.x);
		vertexBuffer.push_back(normal.y);
		vertexBuffer.push_back(normal.z);
		vertexBuffer.push_back(color.x);
		vertexBuffer.push_back(color.y);
		vertexBuffer.push_back(color.z);
		return vertexCount++;
	}
	
	void addTriangle(std::uint32_t a, std::uint32_t b, std::uint32_t c) {
		elementBuffer.push_back(a);
		elementBuffer.push_back(b);
		elementBuffer.push_back(c);
		triangleCount++;
	}
	
public:
	
	Mesh() {
		vertexCount = 0;
		triangleCount = 0;
	}
	
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
		
		GL::ArrayBuffer vertexBufferGL;
		GL::ElementBuffer32 elementBufferGL;
		vertexBufferGL.data(sizeof(float) * vertexBuffer.size(), &vertexBuffer[0]);
		elementBufferGL.elements(elementBuffer.size(), &elementBuffer[0]);
		
		vao.bind();
		elementBufferGL.bind();
		vertexBufferGL.enableVertexAttribute(0, 3, GL_FLOAT, 9 * sizeof(float), 0);
		vertexBufferGL.enableVertexAttribute(1, 3, GL_FLOAT, 9 * sizeof(float), 3 * sizeof(float));
		vertexBufferGL.enableVertexAttribute(2, 3, GL_FLOAT, 9 * sizeof(float), 6 * sizeof(float));
		vao.unbind();
	}
	
	void draw() {
		vao.bind();
		glDrawElements(GL_TRIANGLES, 3 * triangleCount, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid*>(0));
		vao.unbind();
	}
	
};