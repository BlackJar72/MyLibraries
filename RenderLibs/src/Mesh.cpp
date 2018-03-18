#include "Mesh.h"
#include "GameMath.h"

using namespace kfrender;

Mesh::Mesh(const GLuint id, const std::vector<ModelFace>& faces) : vboid(id) {
    GLsizeiptr length = faces.size() * 8 * 3;
    GLfloat data[length];

    int index = 0;
    for(ModelFace face: faces) {
        for(int i = 0; i < 3; i++) {
            data[index++] = face.getVerts()[i].get(0);
            data[index++] = face.getVerts()[i].get(1);
            data[index++] = face.getVerts()[i].get(2);
            data[index++] = face.getNorms()[i].get(0);
            data[index++] = face.getNorms()[i].get(1);
            data[index++] = face.getNorms()[i].get(2);
            data[index++] = face.getUV()[i].get(1);
            data[index++] = face.getUV()[i].get(0);
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, length, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh(){}
