#ifndef COLORMESH_H
#define COLORMESH_H

#include "ColorFace.h"
#include "GameMath.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <vector>


class ColorMesh
{
    public:
        ColorMesh() = delete;
        ColorMesh(const GLuint id, const std::vector<ColorFace>& faces);
        virtual ~ColorMesh();
        void draw() const;
        void draw(const gamemath::Vec3f& pos, const gamemath::Vec3f& rot) const;
        void draw(const gamemath::Mat4f& transform) const;
    private:
        const GLuint vboid;
};

#endif // COLORMESH_H
