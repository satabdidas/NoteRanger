
SHELL = /bin/sh

OBJDIR = obj
SRCDIR = src
SOURCES_TEMP = Main.cpp Parser.cpp TermDB.cpp DocumentDB.cpp
SOURCES = $(patsubst %.cpp, $(SRCDIR)/%.cpp, $(SOURCES_TEMP))
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
DEPS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.d, $(SOURCES))
EXEC = noteranger

CXXFLAGS += -g -std=c++14 -I$(CXX_INCLUDE) -I$(BOOST_INCLUDE)
LDFLAGS = -L$(BOOST_LIB) -lboost_regex -lboost_filesystem -lboost_system

all : $(OBJDIR) $(EXEC)

$(OBJDIR) :
	@-mkdir -p obj

$(OBJECTS) : $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(EXEC) : $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	\rm -rf $(OBJDIR) $(EXEC) $(DEPS)


ifneq ($(MAKECMDGOALS), clean)

$(DEPS) : $(OBJDIR)/%.d: $(SRCDIR)/%.cpp $(OBJDIR)
	rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< -MF $@; \
	sed -i bak 's:.*\.o:$(OBJDIR)/&:' $@

-include $(DEPS)
endif

.PHONY: clean all

print-%  : ; @echo $* = $($*)
