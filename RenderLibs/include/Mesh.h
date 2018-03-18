#ifndef MESH_H
#define MESH_H

#include "ModelFace.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <vector>

namespace kfrender {

class Mesh
{
    public:
        Mesh() = delete;
        Mesh(const GLuint id, const std::vector<ModelFace>& faces);
        virtual ~Mesh();
        inline GLuint id() const {return vboid;}
    protected:
    private:
        const GLuint vboid;
};

}
#endif // MESH_H
