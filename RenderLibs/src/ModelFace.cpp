#include "ModelFace.h"

using namespace kfrender;
using namespace gamemath;

/**
 * This represents a single triangle in a model's mesh.
 */
ModelFace::ModelFace(const Vec3f* verts, const Vec3f* norms, const Vec2f* uv) {
    vertices[0] = verts[0];
    vertices[1] = verts[1];
    vertices[2] = verts[2];
    normals[0]  = norms[0];
    normals[1]  = norms[1];
    normals[2]  = norms[2];
    uvmap[0]    = uv[0];
    uvmap[1]    = uv[1];
}

ModelFace::~ModelFace() {}
