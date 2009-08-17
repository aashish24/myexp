
CC = gcc
CFLAGS = -g 
LIBS = -L/usr/local/lib64 -L/usr/lib64 -L/usr/lib -L/usr/X11R6/lib -L/usr/X11R6/lib64 -L/research/tools/glew/current/$$LITE_BUILD/lib -lX11 -lXi -lXmu -lGLEW -lglut -lGL -lGLU -lm 

OBJS=main.cpp BmpImage.cpp TgaImage.cpp


StereoViewer.$$LITE_ARCH: $(OBJS)
	$(CC) $(CFLAGS) -o  $@  ${LIBS} $(OBJS)  

clean: 
	rm -rf StereoViewer *.o
