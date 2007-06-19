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
# * gnu make to understand some basic described here. 
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

APP_NAME=	VrjCinema

c++:
	$(MAKE) NO_DEPEND=0 cxx
	$(MAKE) $(APP_NAME)

all:
	$(MAKE) java_idl
	$(MAKE) NO_DEPEND=0 cxx
	$(MAKE) $(APP_NAME)
	$(MAKE) java
	$(MAKE) DtTweekBean.jar
	-$(MAKE) install


# Basic options.
#-------------------------------------------------------
BUILD_TYPE?=			opt

srcdir=				../src
EXTRA_PATH_FOR_SOURCES=		../src/Core		\
				../src/Util		\
				../src/Dev		\
				../java/src		\
				../tweek/dt	

VRJCINEMA_SRCS=			Controller.cpp			\
				Defs.cpp			\
				DtSharedData.cpp		\
				DtSubjectImpl.cpp		\
				DtUserData.cpp			\
				Globals.cpp			\
				KeyboardMouse.cpp		\
				Navigation.cpp			\
				OsgDashboard.cpp		\
				OsgInteraction.cpp 		\
				OssimInteraction.cpp 		\
				OsgVJApp.cpp			\
				VJApp.cpp			\
				VJKeyboardMouseCallback.cpp	
		
# Advanced options. 
#---------------------------------------------------------------
INSTALL=	$(VRJCINEMA_ROOT_DIR)/lib

STATICLIB_EXT=	.a

## This is needed to make java_idl
VPATH=		$(VRJCINEMA_ROOT_DIR)/tweek/dt

## Extra path for java src. 
EXTRA_SOURCEPATH_DIRS= 	../java/src

NO_DEPEND=	YES

IDL_CXX_FILES=	dtsubject.cpp dtsubject.h		
IDL_JAVA_FILES=	dtsubject.java	
		

idl_srcs=	$(filter-out $(VRJCINEMA_SRCS), $(notdir $(wildcard $(CXX_GEN_DIR)/*.cpp)))

SRCS=		$(VRJCINEMA_SRCS) $(APP_SRCS) $(idl_srcs)
JAVA_SRCS=	dt/DtTweek.java			\
		dt/DtObserverImpl.java	
	
ALL_CLASSES=	dt/*.class
CLASSPATH=	$(TWEEK_JARS)

include $(VJ_BASE_DIR)/share/vrjuggler/vrj.appdefs.mk
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.glapp.mk
include $(DZR_BASE_DIR)/ext/tweek/dzr.tweek.mk
include $(DZR_BASE_DIR)/mk/dzr.java-app.mk


CXX_GEN_DIR=		$(VRJCINEMA_ROOT_DIR)/tweek
CXX_IDL=		$(TWEEK_IDL_CXX)
CXX_IDL_OPTS=		$(TWEEK_IDLFLAGS_CXX)			\
			$(TWEEK_IDL_GENDIR_CXX)$(CXX_GEN_DIR)
CXX_IDL_INCLUDES=


EXTRA_INCLUDES+=	-I$(CXX_GEN_DIR) 			\
			-I../include 			\
			-I../tweek/dt 			\
			-I$(VJ_BASE_DIR)/include/tweek/idl 	\
			-I$(VJ_BASE_DIR)/include/tweek/CORBA	\
			-I$(OSG_INC_DIR)			\
			-I$(PRODUCER_INC_DIR)			\
			-I$(OPENTHREADS_INC_DIR)		\
			-I$(OSSIM_PLANET_INC_DIR) 		\
			-I$(OSSIM_INC_DIR)			\
			-I$(OSG_EPHEMERIS_INC_DIR) 	

# Java specific
#----------------------------------------------------------------------
JAVA_GEN_DIR=		../java/src
JAVA_IDL=			$(TWEEK_IDL_JAVA)
JAVA_IDL_OPTS=		$(TWEEK_IDLFLAGS_JAVA)			\
				$(TWEEK_IDL_GENDIR_JAVA)$(JAVA_GEN_DIR)
JAVA_IDL_INCLUDES=	


vpath %.idl $(srcdir)
vpath %.cpp $(CXX_GEN_DIR)
vpath %.h $(CXX_GEN_DIR)
vpath %.java $(JAVA_GEN_DIR)

# -----------------------------------------------------------------------------
# Application build targets.
# -----------------------------------------------------------------------------
cxx_idl: $(IDL_CXX_FILES)

%.cpp %.h: %.idl
	$(CXX_IDL) $(CXX_IDL_OPTS) $(CXX_IDL_INCLUDES) $<

java_idl: $(IDL_JAVA_FILES)

%.java: %.idl
	$(JAVA_IDL) $(JAVA_IDL_OPTS) $(JAVA_IDL_INCLUDES) $<

cxx: $(OBJS)

java: $(CLASSES)

VrjCinema: 
	ar rcs libIndra.a *.o
	@rm -rf 		$(INSTALL)
	@mkdir -p 		$(INSTALL)
	@mv libVrjCinema.a 	$(INSTALL)

DtTweekBean.jar: $(JAVA_CLASSES)
	$(JAR) cvf $@ $(ALL_CLASSES)

#install:
#	mv DtTweekBean.jar ../java/src

CLEAN_FILES+=	$(addprefix, $(IDL_CXX_FILES))		\
		$(addprefix ../java/src/dt/, ../lib, $(IDL_JAVA_FILES))	\
		$(CLASSES) dt/*.class, $(EXTRA_SOURCEPATH_DIRS)/DtTweekBean.jar
CLEAN_DIRS+=	./dt
CLOBBER_FILES+=	DtTweekBean.jar
