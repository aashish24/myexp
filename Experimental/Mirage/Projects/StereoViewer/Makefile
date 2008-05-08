
CC = gcc
CFLAGS = -g 
LIBS = -L/usr/local/lib64 -L/usr/lib64 -L/usr/lib -L/usr/X11R6/lib -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 

OBJS=main.cpp BmpImage.cpp 	\


StereoViewer: $(OBJS)
	$(CC) $(CFLAGS) -o  $@  ${LIBS} $(OBJS)  


