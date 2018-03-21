#include "Model.h"

using namespace kfrender;

Model::Model(Mesh m, Texture t, unsigned int s) : mesh(m), texture(t), shader(s) {
    //ctor
}

Model::~Model()
{
    //dtor
}
