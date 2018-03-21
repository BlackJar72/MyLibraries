#ifndef MODEL_H
#define MODEL_H

#include "GameMath.h"
#include "Mesh.h"
#include "Texture.h"

namespace kfrender {

class Model
{
    public:
        Model(Mesh m, Texture t, unsigned int s);
        virtual ~Model();
        void draw() const;
        void draw(gamemath::Vec3f pos, gamemath::Vec3f rot) const;
        void draw(gamemath::Mat4f transform);
    protected:
    private:
        Mesh mesh;
        Texture texture;
        unsigned int shader;
};

}
#endif // MODEL_H
