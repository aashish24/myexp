
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <GL/glut.h>

#include <string>

class TgaImage
{
    public:
    
        TgaImage(void);
        TgaImage(std::string name);
        ~TgaImage();
        
        void read(std::string name);

        int getWidth(void);
        int getHeight(void);
        unsigned char *getPixels(void);

        
    private:
    
        
        int             _width;
        int             _height;
        float           _aspect;
        unsigned char  *_pixels;
        GLenum          _format;
};


#endif
