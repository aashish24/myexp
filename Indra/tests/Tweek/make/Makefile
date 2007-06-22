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

APP_NAME=	server

all:
	$(MAKE) cxx_idl
	$(MAKE) java_idl
	$(MAKE) NO_DEPEND=0 cxx
	$(MAKE) $(APP_NAME)
	$(MAKE) java
	$(MAKE) DtTweekBean.jar
	-$(MAKE) install

# Basic options.
srcdir=		../src
EXTRA_PATH_FOR_SOURCES=		$(VJCINEMA)/src		\
				../java/src		\
				$(VJCINEMA)/tweek/dt	

## This is needed to make java_idl
VPATH=		$(VJCINEMA)/tweek/dt

## Extra path for java src. 
EXTRA_SOURCEPATH_DIRS= 	../java/src

NO_DEPEND=	YES

IDL_CXX_FILES=	dtsubject.cpp dtsubject.h		
IDL_JAVA_FILES=	dtsubject.java	
		

base_srcs=	DtUserData.cpp DtSubjectImpl.cpp OsgDigitalDashboard.cpp OsgInteractionEngine.cpp 	\
		Navigation.cpp Controller.cpp OsgVJApp.cpp MyApp.cpp main.cpp		
idl_srcs=	$(filter-out $(base_srcs), $(notdir $(wildcard $(CXX_GEN_DIR)/*.cpp)))

SRCS=		$(base_srcs) $(idl_srcs)
JAVA_SRCS=	dt/DtTweek.java			\
		dt/DtObserverImpl.java	
	
ALL_CLASSES=	dt/*.class
CLASSPATH=	$(TWEEK_JARS)

include $(VJ_BASE_DIR)/share/vrjuggler/vrj.appdefs.mk
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.glapp.mk
include $(DZR_BASE_DIR)/ext/tweek/dzr.tweek.mk
include $(DZR_BASE_DIR)/mk/dzr.java-app.mk


CXX_GEN_DIR=		$(VJCINEMA)/tweek/dt
CXX_IDL=		$(TWEEK_IDL_CXX)
CXX_IDL_OPTS=		$(TWEEK_IDLFLAGS_CXX)			\
			$(TWEEK_IDL_GENDIR_CXX)$(CXX_GEN_DIR)
CXX_IDL_INCLUDES=	
EXTRA_INCLUDES+=	-I$(CXX_GEN_DIR) -I$(VJCINEMA)/include -I$(VJCINEMA)/tweek/dt -I$(VJ_BASE_DIR)/include/tweek/idl -I$(VJ_BASE_DIR)/include/tweek/CORBA -I$(OSGHOME)/include -I$(OPENTHREADSHOME)/include
EXTRA_LIBS+=		-L$(OSGHOME)/lib/Linux64 -losg -losgDB -losgGA -losgUtil -losgText -losgFX

JAVA_GEN_DIR=		../java/src
JAVA_IDL=		$(TWEEK_IDL_JAVA)
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

server: $(OBJS)
	$(LINK) $(LINK_OUT)$@ $(OBJS) $(TWEEK_LIBS) $(EXTRA_LIBS) $(LIBS)

DtTweekBean.jar: $(JAVA_CLASSES)
	$(JAR) cvf $@ $(ALL_CLASSES)

install:
	mv DtTweekBean.jar ../java/src

CLEAN_FILES+=	$(addprefix $(VJCINEMA)/tweek/dt/, $(IDL_CXX_FILES))		\
		$(addprefix ../java/src/dt/, $(IDL_JAVA_FILES))	\
		$(CLASSES) dt/*.class, $(EXTRA_SOURCEPATH_DIRS)/DtTweekBean.jar
CLEAN_DIRS+=	./dt
CLOBBER_FILES+=	DtTweekBean.jar
