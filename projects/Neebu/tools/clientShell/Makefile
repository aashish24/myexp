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
# -----------------------------------------------------------------
# File:          Makefile.in,v
# Date modified: 2005/01/02 01:48:06
# Version:       1.6
# -----------------------------------------------------------------
#
# *************** <auto-copyright.pl END do not edit this line> ***************

# -----------------------------------------------------------------------------
# Makefile.in for vrjuggler/samples/OpenSG/simple/OpenSGNav
# This requires GNU make.
# -----------------------------------------------------------------------------

APP_NAME=   clientShell

# Basic options.
BUILD_TYPE?=	dbg
OBJDIR?=     	./$(shell uname -s).$(shell uname -p).$(BUILD_TYPE)
DEPDIR?=		$(OBJDIR)
TARGET_DIR?= 	.

all: 		$(OBJDIR)/$(APP_NAME)

## BASIC SETUP ##

ifndef BOOST_DIR
	BOOST_DIR=/usr
endif

srcdir=     		.
SRCS=       		$(notdir $(shell ls --format=single-colum $(srcdir)/*.cpp) )

# includes for vrj 2.2
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.mk
#include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.glapp.mk


#BOOST_LIBS=     -L$(BOOST_DIR)/lib -lboost_program_options-mt -lboost_filesystem-mt -lboost_regex-mt
#BOOST_CFLAGS=   -I$(BOOST_DIR)/include

#EXTRA_CXXFLAGS+=    $(OPENSG_CFLAGS) $(LIB3DS_CFLAGS) $(BOOST_CFLAGS)
#EXTRA_LIBS+=        $(OPENSG_LIBS)   $(LIB3DS_LIBS)   $(BOOST_LIBS)


MAKE_THE_TARGET=	-@if [ ! -d $(TARGET_DIR) ]; then mkdir $(TARGET_DIR) ; fi

# -----------------------------------------------------------------------------
# Application build targets.
# -----------------------------------------------------------------------------
$(OBJDIR)/$(APP_NAME): $(OBJS)
	@echo "Linking with LIBS: $(LIBS)"
	@echo "DZR_BASE_DIR: $(DZR_BASE_DIR)"
	$(LINK) $(LINK_OUT) $@ $(OBJS) $(EXTRA_LIBS) $(LIBS)
	@echo "********************* This baby is DONE *********************" 

install: $(OBJDIR)/$(APP_NAME)
	-$(MAKE_THE_TARGET)
	cp -v $(OBJDIR)/$(APP_NAME) $(TARGET_DIR)
	@echo "********************* This baby is DONE *********************"

uninstall: 
	rm -v $(TARGET_DIR)/$(APP_NAME)
	@echo "********************* This baby is DONE *********************"

clean-local:
	rm -f $(OBJDIR)/*.o
	rm -f $(DEPDIR)/*.d
	rm -f $(OBJDIR)/$(APP_NAME)
	@echo "********************* This baby is DONE *********************"
    
help:
	@echo -e  "Possible build targets: \
	\\n all (default) : compile in OBJDIR    \
	\\n install       : compile and copy executable in TARGET_DIR\
	\\n uninstall     : delete executable from TARGET_DIR \
	\\n clean         : delete .o files  \
	\\n cleandepend   : delete .d files  \
	\\n clean-local   : delete OBJDIR/*.o, DEPDIR/*.d and OBJDIR/APP_NAME \
	\\nCurrent environment variables: \
	\\n APP_NAME   : $(APP_NAME) \
	\\n BUILD_TYPE : $(BUILD_TYPE) \
	\\n OBJDIR     : $(OBJDIR) \
	\\n DEPDIR     : $(DEPDIR) \
	\\n TARGET_DIR : $(TARGET_DIR) \
	"
	
	