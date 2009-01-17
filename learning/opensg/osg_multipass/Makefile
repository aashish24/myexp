# trivial makefile for OpenSG tutorials

# use debug or opt libs?
LIBTYPE :=dbg

# set the path to the installed OpenSG root directory here
# if you installed in /usr/local:
# OSGROOT := /usr/local
# use this if you just unpacked the binary distribution

#OSGROOT := ..

### System dependencies ###############################################

# Set the system we're running on
SYSTEM := $(shell uname)

# which extension to be used for executables
EXEEXT :=

# which extension to be used for executables
ADDLIB :=

# be very careful with these lines. There needs to be a space after the Unix
# lines and nothing after the win lines!!

ifeq ($(SYSTEM),IRIX)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
	ADDLIB := X
endif
ifeq ($(SYSTEM),IRIX64)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
	ADDLIB := X
endif
ifeq ($(SYSTEM),Linux)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
	ADDLIB := X
endif
ifeq ($(findstring WIN,$(SYSTEM)),WIN)
        OS := WIN32
        CCOUT := -Fo
        LDOUT := /out:
	LINK   := -link
	EXEEXT :=.exe
endif
ifeq ($(SYSTEM),HP-UX)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
	ADDLIB := X
endif
ifeq ($(SYSTEM),Darwin)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
endif

# Var settings

#CC = "$(shell $(OSGROOT)/bin/osg2-config --compiler)"
CC= 	g++


#OPENSG_LIBS=    $(shell  $(OPENSG_CONFIG) --$(BUILD_TYPE) --libs Base System Util State Group FileIO)
OPENSG_CONFIG=	$(OPENSG_ROOT_DIR)/bin/osg2-config 
OPENSG_CFLAGS=  $(shell  $(OPENSG_CONFIG) --$(LIBTYPE) --cflags Base System Util State Group FileIO)

#OPENSG_CONFIG=	$(OPENSG_ROOT_DIR)/bin/osg2-config 
#OPENSG_CFLAGS=  -I/research/tools/opensg/opensg.2.0.0-r1505/fc8.x86_64.gcc-4.1.2.debug/include 	\
		-I/usr/include/freetype2 							\
		-I/research/tools/collada-dom/collada-dom.2.1.0/fc8.x86_64.gcc-4.1.2.debug/include/colladadom	\
		-I/research/tools/collada-dom/collada-dom.2.1.0/fc8.x86_64.gcc-4.1.2.debug/include/colladadom/1.4
CCFLAGS = $(OPENSG_CFLAGS) -I/research/tools/glut/freeglut-2.4.0/centos5.x86_64.gcc-4_1_2.debug/include -I/research/tools/boost/boost.1.36.0/centos5.x86_64.gcc-4_1_2.debug/include/

LDFLAGS = $(LINK) $(shell $(OPENSG_ROOT_DIR)/bin/osg2-config --$(LIBTYPE) --libs Base System State Group FileIO WindowGLUT Util ImageFileIO)

#LDFLAGS= -L${OPENSG_LIB_DIR} -L/research/tools/collada-dom/collada-dom.2.1.0/centos5.x86_64.gcc-4.1.2.debug/lib -lOSGBase -lOSGSystem -lOSGState -lOSGGroup -lOSGFileIO -lOSGDrawable -lOSGImageFileIO -lOSGWindowGLUT -lOSGWindow -lOSGUtil -lOSGText -lGL -lGLU -lpthread -ldl -lm -lz -lcollada14dom -lxml2 -ljpeg -ltiff -lpng -lglut -lfreetype -lfontconfig 
EXTRA_LD_FLAGS= 


# all tutorials in this directory

PROGS := test

# program dependencies

default:	$(PROGS)

# make rules

.PHONY: clean Clean

clean:
	rm -f  *.o 
	rm -f  *.obj 
	rm -rf ii_files
	rm -f *.pdb
	rm -f *.ilk
	rm -f *.idb

Clean: clean
	rm -f $(PROGS) 

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $<

%: %.o
	$(CC) $(LDOUT)$@ $< $(LDFLAGS)

%$(EXEEXT): %.cpp
	$(CC) $(CCFLAGS) $< $(LDFLAGS) $(EXTRA_LD_FLAGS) $(LDOUT)$@ 
