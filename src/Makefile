CC=g++
CFLAGS=-Wall -O2 -ggdb

OBJ=SerialRS232.o Communication.o
CLI_EXE=cli_lx200
CLI_OBJ=client.o

ROOTDIR=..
OBJDIR=$(ROOTDIR)/object
BINDIR=$(ROOTDIR)/bin
INCDIR=$(ROOTDIR)/include
DOCDIR=$(ROOTDIR)/doc
LIBDIR=$(ROOTDIR)/lib

VPATH=$(OBJDIR):$(BINDIR):$(INCDIR)

all: dirs $(CLI_EXE) doc

dirs:
	if ! test -d $(BINDIR) ; then mkdir $(BINDIR) ; fi
	if ! test -d $(OBJDIR) ; then mkdir $(OBJDIR) ; fi

$(CLI_EXE): $(OBJ) $(CLI_OBJ)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(CLI_EXE) $(addprefix $(OBJDIR)/,$^)

%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $(OBJDIR)/$@

doc: $(wildcard *.cpp) $(wildcard *.h)
	@echo Making doc...
	@cd $(DOCDIR) && doxygen Doxyfile &> /dev/null

clean:
	if test -d $(BINDIR) ; then\
		cd $(BINDIR) && rm -f $(CLI_EXE);\
	fi
	if test -d $(OBJDIR) ; then\
		cd $(OBJDIR) && rm -f $(OBJ) $(CLI_OBJ);\
	fi

distclean: clean
	rm -rf $(DOCDIR)/html
	if test -d $(BINDIR); then rmdir $(BINDIR); fi
	if test -d $(OBJDIR); then rmdir $(OBJDIR); fi
	
.PHONY: dirs clean
