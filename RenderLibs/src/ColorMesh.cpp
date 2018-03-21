#include "ColorMesh.h"

ColorMesh::ColorMesh(const GLuint id, const std::vector<ColorFace>& faces) : vboid(id) {
    GLsizeiptr length = faces.size() * 9 * 3;
    GLfloat data[length];

    int index = 0;
    for(ColorFace face : faces) {
        for(int i = 0; i < 3; i++) {
            data[index++] = face.getVerts()[i].get(0);
            data[index++] = face.getVerts()[i].get(1);
            data[index++] = face.getVerts()[i].get(2);
            data[index++] = face.getNorms()[i].get(0);
            data[index++] = face.getNorms()[i].get(1);
            data[index++] = face.getNorms()[i].get(2);
            data[index++] = face.getColor()[i].get(0);
            data[index++] = face.getColor()[i].get(1);
            data[index++] = face.getColor()[i].get(2);
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, length, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ColorMesh::~ColorMesh()
{
    //dtor
}
