#ifndef COLORFACE_H
#define COLORFACE_H
#include "GameMath.h"


class ColorFace
{
    public:
        ColorFace() = delete;
        ColorFace(const gamemath::Vec3f* verts, const gamemath::Vec3f* norms, const gamemath::Vec3f* c);
        virtual ~ColorFace();
        inline gamemath::Vec3f* getVerts() {return vertices;}
        inline gamemath::Vec3f* getNorms() {return normals;}
        inline gamemath::Vec3f* getColor() {return color;}
    private:
        gamemath::Vec3f vertices[3];
        gamemath::Vec3f normals[3];
        gamemath::Vec3f color[3];
};

#endif // COLORFACE_H
