
#ifndef __TGA_H__
#define __TGA_H__

unsigned char* LoadTGAFromMemory(char *data, int length, int &width, int &height, int &components);
unsigned char* LoadTGA(char* file, int &width, int &height, int &components);

bool WriteTGA(char *file, int width, int height, int comp, unsigned char *outImage);


#endif
