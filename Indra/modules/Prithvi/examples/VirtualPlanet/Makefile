#/**********************************************************************
# * @Author: Aashish Chaudhary
# *          
# * @Comment:
# *	This is a example makefile. This makefile assumes that 
# * user is using Indra framework along with VRJuggler. 
# * OSG, OGL and OpenSG are optional though this makefile 
# * using OSG. This makefile is a standard gnu makefile using 
# * basic tools from VRJuggler to make it portable along 
# * different architectures. 
# *
# *
# *	Basic options.
# *
# * 1. srcdir
# *	srcdir=		../src
# *
# *	This variable should be used to define the primary folder for the source 
# *	files. If you want to add more source paths then use EXTRA_PATH_FOR_SOURCES. 
# *
# *	2. EXTRA_PATH_FOR_SOURCES
# *		
# *	EXTRA_PATH_FOR_SOURCES=		path1	\
# *						                path2	
# * 
# *	
# **********************************************************************
# */

default:	all

APP_NAME=	virtualplanet

BUILD_TYPE?=	opt

srcdir=		../src

SRCS=		MyApp.cpp			\
		main.cpp

NO_DEPEND=	YES
		
EXTRA_INCLUDES=	-I../../../			\
		-I$(OSG_INC_DIR)		\
		-I$(GMTL_INC_DIR)		\
		-I$(CPPDOM_INC_DIR)		\
		-I$(OSSIMPLANET_INC_DIR)	\
		-I$(CPPDOM_INC_DIR)		\
		-I$(OMNIORB_INC_DIR)


EXTRA_LIBS=	-L../../../../bin			\
		-L$(OSG_LIB_DIR) 			\
		-L$(BOOST_LIB_DIR)	        	\
		-L$(OMNIORB_LIB_DIR)        		\
		-L$(CPPDOM_LIB_DIR)	        	\
		-L$(OSSIM_LIB_DIR)	        	\
		-L$(OSSIMPLANET_LIB_DIR)        	\
		-lVeda -lOsgTools -lNeiv		\
		-lPrithvi -losg -losgDB -losgGA    	\
		-losgUtil -losgText -losgFX 		\
		-losgViewer -lomniORB4 -lomnithread 

DZR_BASE_DIR=   $(shell flagpoll doozer --get-prefix)
include         $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.mk
include         $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.glapp.mk
include         $(DZR_BASE_DIR)/ext/tweek/dzr.tweek.mk

#vpath %.cpp    $(CXX_GEN_DIR)
#vpath %.h      $(CXX_GEN_DIR)

all:		
		$(MAKE) $(APP_NAME)

$(APP_NAME): 	$(OBJS)
		$(LINK) $(LINK_OUT)$@ $(OBJS) $(EXTRA_LIBS) $(LIBS)

CLEAN_FILES+=	$(APP_NAME)

