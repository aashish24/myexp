
CC = gcc
CFLAGS = -g -I/store/home/craig/ode-0.10.0/include -I/research/tools/gmtl/gmtl.0.5.4/linux.x86_64.gcc.debug/include 
LIBS = -L/usr/local/lib64 -L/usr/lib64 -L/usr/lib -L/usr/X11R6/lib -L/usr/X11R6/lib64 -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm /store/home/craig/ode-0.10.0/ode/src/.libs/libode.a  /store/home/craig/ode-0.10.0/drawstuff/src/.libs/libdrawstuff.a 

OBJS=main.cpp BmpImage.cpp TgaImage.cpp


Ragdoll: $(OBJS)
	$(CC) $(CFLAGS) -o  $@  ${OBJS} ${LIBS}  

clean: 
	rm -rf Ragdoll *.o
