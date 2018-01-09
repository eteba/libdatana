NAME     := libdatana
TARGET   := $(NAME).so

MAJOR    := 1
MINOR    := 0
RELEASE  := 1

OBJECTS  := $(NAME).o
SRCS     := $(NAME).cc

CXXFLAGS += -std=gnu++11 -fPIC -g -c -Wall
LDFLAGS  += -shared -Wl,-soname,$(TARGET).$(MAJOR)
LDLIBS   += -lc
INCDIR   += `root-config --incdir`

DESTDIR  = /
hdrdir   := $(DESTDIR)usr/local/include
libdir   := $(DESTDIR)usr/local/lib64

$(TARGET) : $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET).$(MAJOR).$(MINOR).$(RELEASE) $(OBJECTS) $(LDLIBS)

$(OBJECTS) : $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -I$(INCDIR)

.PHONY: clean
clean :
	rm $(OBJECTS) $(TARGET).$(MAJOR).$(MINOR).$(RELEASE)

.PHONY: install
install :
	mkdir -p $(hdrdir) $(libdir)
	rm -f $(libdir)/$(TARGET)*
	install -m 0755 $(NAME).h $(hdrdir)
	install -m 0755 $(TARGET).$(MAJOR).$(MINOR).$(RELEASE) $(libdir)
	ln -s $(libdir)/$(TARGET).$(MAJOR).$(MINOR).$(RELEASE) $(libdir)/$(TARGET).$(MAJOR)
	ln -s $(libdir)/$(TARGET).$(MAJOR).$(MINOR).$(RELEASE) $(libdir)/$(TARGET)

#.PHONY: link
#link :
#	&& ldconfig && ln -s $(libdir)$(TARGET).$(MAJOR) $(libdir)$(TARGET)

.PHONY: uninstall
uninstall :
	rm $(hdrdir)/$(NAME).h $(libdir)/$(TARGET)* -v
