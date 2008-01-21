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
	cd $(BINDIR) && rm -f $(CLI_EXE)
	cd $(OBJDIR) && rm -f $(OBJ) $(CLI_OBJ)

distclean: clean
	rm -rf $(DOCDIR)/html
	rmdir $(BINDIR)
	rmdir $(OBJDIR)
	
.PHONY: dirs clean
