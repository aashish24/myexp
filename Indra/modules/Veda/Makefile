#/**********************************************************************
# * @AUTHOR:
# * Aashish Chaudhary
# * Sr. Research Analyst at DT   
# * Arizona State University 
# *
# * @DATE: 
# * Jan 23 2006
# *
# *
# * @COMMENT:
# * This is a example makefile. This makefile assumes that 
# * user is using VrjCinema framework along with VRJuggler. 
# * OSG, OGL and OpenSG are optional though this makefile 
# * using OSG. This makefile is a standard gnu makefile using 
# * basic tools from VRJuggler to make it portable alond 
# * different architecture. Its higly recommended that you learn 
# * gnu make to understand some basics described here. 
# *
# * This makefile is divided into two parts basic and advanced. 
# * Which is described in detail below. 
# * 
# * @NOTE:
# * Only standard variables defined here. 
# *
# *  Basic options.
# *  -------------------------------------------------------------------
# *	1)	srcdir
# *		srcdir=		../src
# *
# *	This variable should be used to define the primary dir for the src 
# *	files. If you want to add more src dir then use EXTRA_PATH_FOR_SOURCES. 
# *
# *	2)	EXTRA_PATH_FOR_SOURCES
# *		
# *		EXTRA_PATH_FOR_SOURCES=		path1	\
# *						path2	
# * 
# *  This variable defines where the makefile will look for the src
# *	files. If there are more than one directory then they should be 
# *  included by a backslash. 
# *
# * @NOTE: 
# * Still need to seperate the java build from this makefile.  	
# *
# **********************************************************************
# */

APP_NAME= 	Veda
JAR_NAME= 	VedaTweek.jar

c++:
		$(MAKE) NO_DEPEND=0 cxx
		$(MAKE) $(APP_NAME)

all:
		$(MAKE) cxx_idl
		$(MAKE) java_idl
		$(MAKE) NO_DEPEND=0 cxx
		$(MAKE) $(APP_NAME)


#-----------------------Basic options-------------------------------------

BUILD_TYPE?=			dbg

srcdir=				./
EXTRA_PATH_FOR_SOURCES=		./Core				\
				./Design			\
				./Tweek				\



EXTRA_SOURCEPATH_DIRS=		./Tweek


INDRA_SRCS=			Controller.cpp			\
				Defs.cpp			\
				SharedData.cpp			\
				SubjectImpl.cpp			\
				UserData.cpp			\
				Globals.cpp			\
				Navigation.cpp			\
				OsgInteraction.cpp 		\
				OssimInteraction.cpp 		\
				OsgBase.cpp			\
				AppBase.cpp			\
		

#-------------------Advanced options--------------------------------------- 

CFLAGS_DYNLIB=          	-fPIC -DPIC

EXTRA_CXXFLAGS=			$(CFLAGS_DYNLIB)

INSTALL=			../../bin

STATICLIB_EXT=          	.a
DYNAMICLIB_EXT=         	.so

NO_DEPEND=			YES

IDL_CXX_FILES=			TweekSubject.cpp TweekSubject.h		
IDL_JAVA_FILES=			TweekSubject.java	
		

idl_srcs=			$(filter-out $(INDRA_SRCS), $(notdir $(wildcard $(CXX_GEN_DIR)/*.cpp)))

SRCS=				$(INDRA_SRCS) $(APP_SRCS) $(idl_srcs)

DZR_BASE_DIR=   $(shell flagpoll doozer --get-prefix)

include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.mk
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.glapp.mk
include $(DZR_BASE_DIR)/ext/tweek/dzr.tweek.mk
include $(DZR_BASE_DIR)/mk/dzr.java-app.mk

CXX=			g++

CXX_GEN_DIR=		./Tweek
CXX_IDL=		$(TWEEK_IDL_CXX)
CXX_IDL_OPTS=		$(TWEEK_IDLFLAGS_CXX)			\
			$(TWEEK_IDL_GENDIR_CXX)$(CXX_GEN_DIR)
CXX_IDL_INCLUDES=

CXX_DLL=                $(CXX) -shared -o lib$(APP_NAME)$(DYNAMICLIB_EXT)  $(DPP_EXTRA_LDFLAGS) $(EXTRA_LDFLAGS)

EXTRA_INCLUDES+=	-I$(CXX_GEN_DIR) 			\
			-I../					\
			-I$(OSG_INC_DIR)			\
			-I$(GMTL_INC_DIR)			\
			-I$(CPPDOM_INC_DIR)			\
			-I$(OMNIORB_INC_DIR)			\

EXTRA_LIBS+=		-L../../bin -lOsgTools -L$(OSG_LIB_DIR) -losg -losgDB -losgUtil


#-----------------------------Java specific-----------------------------------

JAVA_GEN_DIR=		./TweekJava
JAVA_IDL=		$(TWEEK_IDL_JAVA)
JAVA_IDL_OPTS=		$(TWEEK_IDLFLAGS_JAVA)			\
			$(TWEEK_IDL_GENDIR_JAVA) $(JAVA_GEN_DIR)
JAVA_IDL_INCLUDES=	


vpath %.idl ./Tweek
vpath %.cpp $(CXX_GEN_DIR)
vpath %.h $(CXX_GEN_DIR)
vpath %.java $(JAVA_GEN_DIR)


#---------------------------Application build targets-------------------------

cxx_idl: $(IDL_CXX_FILES)

%.cpp %.h: %.idl
				$(CXX_IDL) $(CXX_IDL_OPTS) $(CXX_IDL_INCLUDES) $<

java_idl: $(IDL_JAVA_FILES)


%.java: %.idl
				$(JAVA_IDL) $(JAVA_IDL_OPTS) $(JAVA_IDL_INCLUDES) $<

cxx: $(OBJS)


$(APP_NAME): 
				$(CXX_DLL) $(OBJS)
				@mv *.so $(INSTALL)


CLEAN_FILES+=			$(addprefix, $(IDL_CXX_FILES))		\
				$(addprefix ./, $(INSTALL)/lib*$(APP_NAME), $(IDL_JAVA_FILES))
		
CLEAN_DIRS+=			TweekJava

