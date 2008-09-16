# *****************************************************************************
#
# @Author: Aashish Chaudhary, Carsten?? 
# @Date: 08/27/2008
#
# -----------------------------------------------------------------------------

APP_NAME=   OTCLoader

# Basic options.
BUILD_TYPE?=	dbg
OBJDIR?=     	./$(shell uname -s).$(shell uname -p).$(BUILD_TYPE)
DEPDIR?=		$(OBJDIR)
TARGET_DIR?= 	../bin

all: 		$(OBJDIR)/$(APP_NAME)

## BASIC SETUP ##
ifndef TOOL_DIR
TOOL_DIR=/research/tools
endif

ifndef OPENSG_CONFIG
OPENSG_CONFIG=$(OPENSG_ROOT_DIR)/bin/osg-config
endif

ifndef LIB3DS_CONFIG
LIB3DS_CONFIG=$(LIB3DS_ROOT_DIR)/bin/lib3ds-config
endif

srcdir=     		../source
EXTRA_INCLUDES+=	-I../include
SRCS=       		$(notdir $(shell ls --format=single-colum $(srcdir)/*.cpp) )

# includes for vrj 2.2
DZR_BASE_DIR=   $(shell flagpoll doozer --get-prefix)
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.mk
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.glapp.mk

OPENSG_LIBS=    $(shell  $(OPENSG_CONFIG) --$(BUILD_TYPE) --libs Base System)
OPENSG_CFLAGS=  $(shell  $(OPENSG_CONFIG) --$(BUILD_TYPE) --cflags Base System)

LIB3DS_LIBS=    $(shell $(LIB3DS_CONFIG) --libs)
LIB3DS_CFLAGS=  $(shell $(LIB3DS_CONFIG) --cflags)

ifeq ($(BUILD_TYPE), dbg)
BOOST_LIBS=     -L$(BOOST_LIB_DIR) -lboost_program_options-mt-d -lboost_filesystem-mt-d -lboost_regex-mt-d -lboost_system-mt-d -lboost_signals-mt-d 
else
BOOST_LIBS=     -L$(BOOST_LIB_DIR) -lboost_program_options-mt -lboost_filesystem-mt -lboost_regex-mt -lboost_system-mt -lboost_signals-mt 
endif

BOOST_CFLAGS=   -I$(BOOST_INC_DIR)

EXTRA_CXXFLAGS+=    $(OPENSG_CFLAGS) $(LIB3DS_CFLAGS) $(BOOST_CFLAGS)
EXTRA_LIBS+=        $(OPENSG_LIBS)   $(LIB3DS_LIBS)   $(BOOST_LIBS)

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

re-install: clean-local  install
		
	
