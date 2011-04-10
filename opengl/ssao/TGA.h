/*
   TGA Loading
   Game Graphics Programming
   Created by Allen Sherrod
*/


#ifndef _GG_TGA_H_
#define _GG_TGA_H_

unsigned char* LoadTGAFromMemory(char *data, int length, int &width, int &height, int &components);
unsigned char* LoadTGA(char* file, int &width, int &height, int &components);
bool WriteTGA(char *file, int width, int height, int comp, unsigned char *outImage);


#endif