
SHELL = /bin/sh

OBJDIR = obj
SRCDIR = src
SOURCES_TEMP = Main.cpp Parser.cpp TermDB.cpp DocumentDB.cpp
SOURCES = $(patsubst %.cpp, $(SRCDIR)/%.cpp, $(SOURCES_TEMP))
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
DEPS := $(patsubst $(SRCDIR)/%.cpp, %.d, $(SOURCES))
EXEC = noteranger

CXX = clang++-3.8
CXXFLAGS = -g -std=c++14 -stdlib=libc++ -I/usr/local/opt/llvm38/lib/llvm-3.8/include/c++/v1 -I/usr/local/Cellar/boost/1.61.0_1/include/boost
LDFLAGS = -L/usr/local/Cellar/boost/1.61.0_1/lib -lboost_regex

all : init $(EXEC)

init :
	@-mkdir -p obj

$(OBJECTS) : $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(EXEC) : $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	\rm -rf $(OBJDIR) $(EXEC) $(DEPS)


ifneq ($(MAKECMDGOALS), clean)

$(DEPS) : %.d: $(SRCDIR)/%.cpp
	rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $^ -MF $@

-include $(DEPS)
endif

.PHONY: clean all init

print-%  : ; @echo $* = $($*)
