# **************** <Tweek heading BEGIN do not edit this line> ****************
# Tweek
#
# -----------------------------------------------------------------
# File:          Makefile.in,v
# Date modified: 2005/01/01 18:17:31
# Version:       1.17
# -----------------------------------------------------------------
# **************** <Tweek heading END do not edit this line> ******************

# ************** <auto-copyright.pl BEGIN do not edit this line> **************
#
# VR Juggler is (C) Copyright 1998-2005 by Iowa State University
#
# Original Authors:
#   Allen Bierbaum, Christopher Just,
#   Patrick Hartling, Kevin Meinert,
#   Carolina Cruz-Neira, Albert Baker
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#
# *************** <auto-copyright.pl END do not edit this line> ***************

# -----------------------------------------------------------------------------
# Makefile.in for tweek/test/NetworkTest.  It requires GNU make.
# -----------------------------------------------------------------------------

APP_NAME=			server

all:
				#$(MAKE) cxx_idl
				#$(MAKE) java_idl
				$(MAKE) NO_DEPEND=0 cxx
				$(MAKE) $(APP_NAME)
				#$(MAKE) java
				$(MAKE) TweekTestBean.jar

# Basic options.
srcdir=				.
EXTRA_PATH_FOR_SOURCES=		$(INDRA_ROOT_DIR)/modules/Veda

## This is needed to make java_idl
VPATH=				$(INDRA_ROOT_DIR)/modules/Veda/TweekJava

#------Extra path for java src----------
EXTRA_SOURCEPATH_DIRS= 		$(INDRA_ROOT_DIR)/modules/Veda/TweekJava

#------No need for this----------------
JAVA_CLASSPATH= 	

NO_DEPEND=			YES

IDL_JAVA_FILES=			TweekSubject.java	
		
base_srcs=			MyApp.cpp main.cpp		
idl_srcs=			$(filter-out $(base_srcs), $(notdir $(wildcard $(CXX_GEN_DIR)/*.cpp)))

SRCS=				$(base_srcs) $(idl_srcs)
JAVA_SRCS=			Veda/ITweek/TweekSubject.java		\
				Veda/ITweek/TweekObserverImpl.java	\
				Veda/ITweek/TweekSubjectHolder.java	\
				Veda/ITweek/TweekTest.java 		\
	
ALL_CLASSES=			Veda/ITweek/*.class

DZR_BASE_DIR=   		$(shell flagpoll doozer --get-prefix)

include 			$(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.mk
include 			$(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.glapp.mk
include 			$(DZR_BASE_DIR)/ext/tweek/dzr.tweek.mk
include 			$(DZR_BASE_DIR)/mk/dzr.java-app.mk

CXX_GEN_DIR=			$(VJCINEMA)/tweek/dt
CXX_IDL=			$(TWEEK_IDL_CXX)
CXX_IDL_OPTS=			$(TWEEK_IDLFLAGS_CXX)			\
				$(TWEEK_IDL_GENDIR_CXX)$(CXX_GEN_DIR)
CXX_IDL_INCLUDES=	

EXTRA_INCLUDES+=		-I$(INDRA_ROOT_DIR)/modules		\
				-I$(OSG_INC_DIR)			\
				-I$(CPPDOM_INC_DIR)			\
				-I$(GMTL_INC_DIR)			\
				-I$(OMNIORB_INC_DIR)			

EXTRA_LIBS+=			-L$(OSG_LIB_DIR) 			\
				-L$(INDRA_ROOT_DIR)/bin 		\
				-L$(OMNIORB_LIB_DIR)			\
				-L$(BOOST_LIB_DIR)			\
				-L$(CPPDOM_LIB_DIR)			\
				-lOsgTools -lVeda -losg -losgDB -losgGA -losgUtil -losgText -losgFX

JAVA_GEN_DIR=			.
JAVA_IDL=			$(TWEEK_IDL_JAVA)
JAVA_IDL_OPTS=			$(TWEEK_IDLFLAGS_JAVA)			\
				$(TWEEK_IDL_GENDIR_JAVA)$(JAVA_GEN_DIR)
JAVA_IDL_INCLUDES=	

JAVAC_FLAGS+=  			-classpath $(JAVA_CLASSPATH):$(CLASSPATH) 

vpath %.idl 			$(srcdir)
vpath %.cpp 			$(CXX_GEN_DIR)
vpath %.h 			$(CXX_GEN_DIR)
vpath %.java 			$(JAVA_GEN_DIR)

# Application build targets.

cxx_idl: 			$(IDL_CXX_FILES)

%.cpp %.h: %.idl
				$(CXX_IDL) $(CXX_IDL_OPTS) $(CXX_IDL_INCLUDES) $<

java_idl: 			$(IDL_JAVA_FILES)

%.java: %.idl
				$(JAVA_IDL) $(JAVA_IDL_OPTS) $(JAVA_IDL_INCLUDES) $<

cxx: 				$(OBJS)

java: 				$(CLASSES)

server: 			$(OBJS)
				$(LINK) $(LINK_OUT)$@ $(OBJS) $(TWEEK_LIBS) $(EXTRA_LIBS) $(LIBS)

TweekTestBean.jar: 		$(JAVA_CLASSES)
				$(JAR) cvf $@  $(ALL_CLASSES)


CLEAN_FILES+=			$(CLASSES) *.class, $(EXTRA_SOURCEPATH_DIRS)/TweekTestBean.jar

CLEAN_DIRS+=			

CLOBBER_FILES+=			TweekTestBean.jar

