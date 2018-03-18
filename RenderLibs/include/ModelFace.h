#ifndef MODELFACE_H
#define MODELFACE_H
#include "GameMath.h"

namespace kfrender {

class ModelFace
{
    public:
        ModelFace() = delete;
        ModelFace(const gamemath::Vec3f* verts, const gamemath::Vec3f* norms, const gamemath::Vec2f* uv);
        virtual ~ModelFace();
        inline gamemath::Vec3f* getVerts() {return vertices;}
        inline gamemath::Vec3f* getNorms() {return normals;}
        inline gamemath::Vec2f* getUV()    {return uvmap;}
    protected:
    private:
        gamemath::Vec3f vertices[3];
        gamemath::Vec3f normals[3];
        gamemath::Vec2f uvmap[3];
};

}
#endif // MODELFACE_H
