
SHELL = /bin/sh

OBJDIR = obj
SRCDIR = src
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
DEPS := $(patsubst $(SRCDIR)/%.cpp, %.d, $(SOURCES))
EXEC = noteranger

CXX = clang++-3.8
CXXFLAGS = -g -std=c++14 -stdlib=libc++ -I/usr/local/opt/llvm38/lib/llvm-3.8/include/c++/v1

all : init $(EXEC)

init :
	@-mkdir -p obj

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(EXEC) : $(OBJECTS)
	$(CXX) -o $@ $^

clean:
	\rm -rf $(OBJDIR) $(EXEC) $(DEPS)


ifneq ($(MAKECMDGOALS), clean)

%.d : $(SRCDIR)/%.cpp
	rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $^ -MF $@

-include $(DEPS)
endif

.PHONY: clean all init

print-%  : ; @echo $* = $($*)
