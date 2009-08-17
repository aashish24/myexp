#OPENSG_ROOT_DIR=${HOME}/usr

INC_DIRS=-I${GMTL_INC_DIR}/gmtl-0.5.4 -I${OPENSG_INC_DIR}

LIB_DIRS=-L${BOOST_LIB_DIR} -L${COLLADA_LIB_DIR} -L${OPENSG_LIB_DIR}

CXX=g++
CXXFLAGS=-m64 -g -O2


OSGCONFIG=${OPENSG_ROOT_DIR}/bin/osg2-config

CCFLAGS=$(shell ${OSGCONFIG} --cflags --${LIBTYPE} Base System GLUT Util State Group FileIO ImageFileIO)
LDFLAGS = $(shell ${OSGCONFIG} --libs --${LIBTYPE} Base System GLUT Util State Group FileIO ImageFileIO)

all: BoneInfo.o AsfParser.o Skeleton.o osgdemo.o 
	${CXX} ${CXXFLAGS} ${LIB_DIRS} ${LIBS} ${LDFLAGS} -o asfparser $?

%.o: %.cpp
	${CXX} ${CXXFLAGS} ${CCFLAGS} ${INC_DIRS} -c $< 

.PHONY: clean

clean:
	rm -f *.o asfparser 
