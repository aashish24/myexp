
// GLEW includes.
#include "GL/glew.h"

// C++ includes. 
#include <iostream>

// Mirage includes. 
#include "TgaReader.h"

namespace Mirage
{
  namespace System
  {
    TgaReader::TgaReader(void) :
      _image( 0x00 )
    {  
    }


    TgaReader::TgaReader(const std::string& name) :
      _image( 0x00 )
    {
        read(name);
    }


    TgaReader::~TgaReader()
    {      
    }

    const Core::Image* const TgaReader::getImage() const 
    {
      return _image.get();
    }


    Core::Image* TgaReader::editImage() 
    {
      return _image.get();
    }
    
     
    void TgaReader::read(const std::string& name)
    {
        GLubyte         TGAheader[12]    = {0,0,0,0,0,0,0,0,0,0,0,0};// TGA header
        GLubyte         header[6];                                   // First 6 useful bytes of the header
        GLuint          bytesPerPixel;                               // Holds the number of bytes per pixel used
        GLuint          imageSize;                                   // Used to store the image size
        GLuint          bpp;                                         // TgaReader color depth in bits per pixel.

        std::string fullname = name;

        // Open File    
        FILE *file;   

    #ifdef _MSC_VER
        fopen_s( &file, fullname.c_str(), "rb" );
    #else
        file = fopen( fullname.c_str(), "rb" );
    #endif 

        // Load the file and perform checks
        if(file == NULL)
        {
            std::cerr << "TgaReader::read: Error opening file " << fullname << std::endl;
            return;
        }
        
        if(fread(TGAheader,1,sizeof(TGAheader),file) != sizeof(TGAheader))
        {
            std::cerr << "TgaReader::read: Error reading header from " << fullname << std::endl;
            fclose(file);    
            return;       
        }

        if(TGAheader[2] != 2 && TGAheader[2] != 10)
        {
            std::cerr << "TgaReader::read: File " << fullname << " is no't ummapped RGB/RGBA!" << std::endl;
            fclose(file);    
            return;      
        }

        if(fread(header,1,sizeof(header),file) != sizeof(header))
        {
            std::cerr << "TgaReader::read: Error reading image header from " << fullname << std::endl;
            fclose(file);    
            return;  
        }

        // Create new image. 
        _image = new Core::Image();

        // Read TgaReader Identification
        if(TGAheader[0] != 0)
        {
            char *iid = new char [TGAheader[0]];
            fread(iid, TGAheader[0], 1, file);
        }
        
        // Determine the TGA _width and _height (highbyte*256+lowbyte)
        _image->_width  = header[1] * 256 + header[0];
        _image->_height = header[3] * 256 + header[2];
        
        // Check to make sure the targa is valid and is 24 bit or 32 bit
        if(_image->_width    <=0    ||                      // Is the _width less than or equal to zero
           _image->_height   <=0    ||                      // Is the _height less than or equal to zero
           (header[4] != 24 && header[4] != 32))            // Is it 24 or 32 bit?
        {
            fclose(file);                                   // If anything didn't check out then close the file and return
            return;
        }

        bpp              = header[4];                       // Grab the bits per pixel
        bytesPerPixel    = bpp / 8;                         // Divide by 8 to get the bytes per pixel
        imageSize        = _image->_width * _image->_height * bytesPerPixel;// Calculate the memory required for the data

        // Allocate the memory for the image data
        _image->_data = new GLubyte[imageSize];

        // Make sure the data is allocated write and load it
        if(_image->_data == NULL ||                               // Does the memory storage exist?
           fread(_image->_data, 1, imageSize, file) <= 0)      // Does the image size match the memory reserved?
        {
            if(_image->_data != NULL)                             // Was the image data loaded
                delete [] _image->_data;                          // If so, then release the image data
        
            _image->_data = NULL;
            fclose(file);                                   // Close the file
            return;
        }

        // Uncompress if compressed
        if(TGAheader[2] == 10)
        {
            GLubyte *_uncomppixels = new GLubyte[imageSize];
            
            GLubyte *p = _image->_data, *u = _uncomppixels;
            
            while(u < _uncomppixels + imageSize)
            {
                GLubyte com = *p++;
                GLubyte cnt = (com & 0x7f) + 1;
                
                if(com & 0x80)
                {
                    // RLE packet
                    if(bytesPerPixel == 3)
                    {
                        while(cnt-- > 0)
                        {
                            *u++ = p[0];
                            *u++ = p[1];
                            *u++ = p[2];
                        }
                        p+=3;
                    }
                    else
                    {
                        while(cnt-- > 0)
                        {
                            *u++ = p[0];
                            *u++ = p[1];
                            *u++ = p[2];
                            *u++ = p[3];
                        }
                        p+=4;
                    }
                }
                else
                {
                    // Raw packet
                    if(bytesPerPixel == 3)
                    {
                        while(cnt-- > 0)
                        {
                            *u++ = *p++;
                            *u++ = *p++;
                            *u++ = *p++;
                        }
                    }
                    else
                    {
                        while(cnt-- > 0)
                        {
                            *u++ = *p++;
                            *u++ = *p++;
                            *u++ = *p++;
                            *u++ = *p++;
                        }
                    }
                }
            }
            
            delete [] _image->_data;
            _image->_data = _uncomppixels;
        }
        
        
        // Loop through the image data and swap the 1st and 3rd bytes (red and blue)
        // Only for big-endian systems
        union 
        {
            int a;
            char b[4];
        } endian;
        
        endian.a = 1;
        
        if(endian.b[0] == 1)
        {    
          for(GLuint cswap = 0; cswap < (int)imageSize; cswap += bytesPerPixel)
          {
            unsigned char dum = _image->_data[cswap];
            _image->_data[cswap] = _image->_data[cswap+2];
            _image->_data[cswap+2] = dum;
          }
        }
        
        // We are done with the file so close it
        fclose(file);

        // Set the type
        if (bpp == 24)
        {
          _image->_format = GL_RGB;
        }
        else
        {
          _image->_format = GL_RGBA;
        }
            
        _image->_aspect = _image->_width / (float) _image->_height;            
    }
  }
}
