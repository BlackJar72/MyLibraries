#include "ColorFace.h"

ColorFace::ColorFace(const gamemath::Vec3f* verts, const gamemath::Vec3f* norms, const gamemath::Vec3f* c) {
    vertices[0] = verts[0];
    vertices[1] = verts[1];
    vertices[2] = verts[2];
    normals[0]  = norms[0];
    normals[1]  = norms[1];
    normals[2]  = norms[2];
    color[0]    = c[0];
    color[1]    = c[1];
    color[2]    = c[2];
}

ColorFace::~ColorFace()
{
    //dtor
}
