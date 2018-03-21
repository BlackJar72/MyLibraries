#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>


class Texture
{
    public:
        Texture(GLuint id);
        virtual ~Texture();
    protected:
    private:
        GLuint glid;
};

#endif // TEXTURE_H
