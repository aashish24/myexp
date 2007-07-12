
default=			c++

JAR_NAME= 			VedaTweek.jar
	
LIB_NAME= 			Veda

DEBUG_APP= 			FALSE
OPTIM_APP= 			TRUE

c++:
				$(MAKE) $(LIB_NAME)

all:
				$(MAKE) cxx_idl
				$(MAKE) java_idl
				$(MAKE) $(LIB_NAME)


#-----------------------Basic options-------------------------------------

#DEBUG_APP=              	TRUE
#OPTIM_APP=              	FALSE

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
		

SHLIB_PREFIX=			lib
SHLIB_EXT=			so
LIB_EXT=			a

SHARED_LIB_FILENAME=		$(SHLIB_PREFIX)$(LIB_NAME)$(SHLIB_EXT)
STATIC_LIB_FILENAME=		$(LIB_PREFIX)$(LIB_NAME)$(LIB_EXT)

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

DZR_BASE_DIR=   		$(shell flagpoll doozer --get-prefix)

CXX=				g++

CXX_GEN_DIR=			./Tweek
CXX_IDL=			$(TWEEK_IDL_CXX)
CXX_IDL_OPTS=			$(TWEEK_IDLFLAGS_CXX)			\
				$(TWEEK_IDL_GENDIR_CXX)$(CXX_GEN_DIR)
CXX_IDL_INCLUDES=

EXTRA_INCLUDES+=		-I$(CXX_GEN_DIR) 			\
				-I../					\
				-I$(OSG_INC_DIR)			\
				-I$(GMTL_INC_DIR)			\
				-I$(CPPDOM_INC_DIR)			\
				-I$(OMNIORB_INC_DIR)			\

EXTRA_LIBS+=			-L../../bin -lOsgTools -L$(OSG_LIB_DIR) -losg -losgDB -losgUtil


#-----------------------------Java specific-----------------------------------

JAVA_GEN_DIR=			./TweekJava
JAVA_IDL=			$(TWEEK_IDL_JAVA)
JAVA_IDL_OPTS=			$(TWEEK_IDLFLAGS_JAVA)			\
				$(TWEEK_IDL_GENDIR_JAVA) $(JAVA_GEN_DIR)
JAVA_IDL_INCLUDES=	

vpath %.idl 			./Tweek
vpath %.cpp 			$(CXX_GEN_DIR)
vpath %.h 			$(CXX_GEN_DIR)
vpath %.java 			$(JAVA_GEN_DIR)


include 			$(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.mk
include 			$(DZR_BASE_DIR)/ext/tweek/dzr.tweek.mk
include 			$(DZR_BASE_DIR)/mk/dzr.java-app.mk
include 			$(DZR_BASE_DIR)/mk/dzr.lib.mk

#---------------------------Application build targets-------------------------

cxx_idl: $(IDL_CXX_FILES)

%.cpp %.h: %.idl
				$(CXX_IDL) $(CXX_IDL_OPTS) $(CXX_IDL_INCLUDES) $<

java_idl: 			$(IDL_JAVA_FILES)

%.java: %.idl
				$(JAVA_IDL) $(JAVA_IDL_OPTS) $(JAVA_IDL_INCLUDES) $<

$(LIB_NAME): 			$(SHARED_LIB_FILENAME) $(STATIC_LIB_FILENAME)

$(SHARED_LIB_FILENAME): $(OBJS)
				$(SHARED_LINK) $(SHARED_OUT)$@ $(OBJS)

$(STATIC_LIB_FILENAME): $(OBJS)	
				$(STATIC_LINK) $(STATIC_OUT)$@ $(OBJS)


CLEAN_FILES+=			$(addprefix, $(IDL_CXX_FILES))		\
				$(addprefix ./, $(INSTALL)/lib*$(APP_NAME), $(IDL_JAVA_FILES))
		
CLEAN_DIRS+=			TweekJava

