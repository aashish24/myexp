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

all: OpenSGNav

APP_NAME=	OpenSGNav

# Basic options.
srcdir=		.
SRCS=		OpenSGNav.cpp app.cpp


DZR_BASE_DIR=   $(shell flagpoll doozer --get-prefix)
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.mk
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.glapp.mk
include $(DZR_BASE_DIR)/ext/tweek/dzr.tweek.mk

OPENSG_LIBS=	$(shell  /research/tools/opensg/opensg.1.8.0/linux.x86_64.gcc.debug/bin/osg-config --libs) -lOSGBase -lOSGSystem
OPENSG_CFLAGS=	$(shell  /research/tools/opensg/opensg.1.8.0/linux.x86_64.gcc.debug/bin/osg-config --cflags)

EXTRA_CXXFLAGS+=	$(OPENSG_CFLAGS)
EXTRA_LIBS+=		$(OPENSG_LIBS)

# -----------------------------------------------------------------------------
# Application build targets.
# -----------------------------------------------------------------------------
OpenSGNav: $(OBJS)
	$(LINK) $(LINK_OUT)$@ $(OBJS) $(EXTRA_LIBS) $(LIBS)
