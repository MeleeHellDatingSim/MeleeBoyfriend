
TARGET := mhds

OUTDIR := build
INCLUDE := include
SOURCES := \
	source/main.o \
	source/match3.o \
	source/scene.o \
	source/font.o \
	source/graphics.o \
	source/ui_scene.o \
	source/ui_label.o \
	source/ui_button.o \
	source/ui_grid.o \
	source/stb_truetype.o \
	source/stb_image.o \
	source/stb_vorbis.o

PC_SOURCES := \
	source/pc/platform.o

CXXFLAGS := -std=c++11 -Wall $(shell pkg-config --cflags glfw3) -g -I$(INCLUDE)
CFLAGS := -I$(INCLUDE)
LIBS := $(shell pkg-config glfw3 --static --libs)

.PHONY: all pc clean run

default: macosx

all:
	mkdir -p $(OUTDIR)
	$(MAKE) win32
	$(MAKE) clean_sources
	$(MAKE) macosx

win32 : $(OUTDIR)/mhds.exe
$(OUTDIR)/mhds.exe: CXXFLAGS += $(shell $(WIN_TOOLCHAIN)pkg-config --cflags glfw3)
$(OUTDIR)/mhds.exe: LIBS := $(shell $(WIN_TOOLCHAIN)pkg-config openal --static --libs) $(shell $(WIN_TOOLCHAIN)pkg-config glfw3 --static --libs)
$(OUTDIR)/mhds.exe: TOOLCHAIN := $(WIN_TOOLCHAIN)
$(OUTDIR)/mhds.exe: $(SOURCES) $(PC_SOURCES)
	$(WIN_TOOLCHAIN)$(CXX) -o $@ $^ $(LIBS) $(FRAMEWORKS)

macosx: $(OUTDIR)/mhds_macosx
$(OUTDIR)/mhds_macosx: CXXFLAGS += $(shell $(MAC_TOOLCHAIN)pkg-config --cflags glfw3)
$(OUTDIR)/mhds_macosx: LIBS := $(shell $(MAC_TOOLCHAIN)pkg-config glfw3 --static --libs) -framework OpenAL
$(OUTDIR)/mhds_macosx: TOOLCHAIN := $(MAC_TOOLCHAIN)
$(OUTDIR)/mhds_macosx: $(SOURCES) $(PC_SOURCES)
	$(MAC_TOOLCHAIN)$(CXX) -o $@ $^ $(LIBS) $(FRAMEWORKS)

%.o: %.c
	$(TOOLCHAIN)$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.cpp
	$(TOOLCHAIN)$(CXX) $(CXXFLAGS) -c $^ -o $@


run: default
	./$(OUTDIR)/$(TARGET)_macosx

clean_sources:
	rm -f $(SOURCES) $(PC_SOURCES)

clean:
	rm -f $(OUTDIR)/* $(SOURCES) $(PC_SOURCES)

doc:
	rm -rf build/doc
	mkdir -p build/doc
	doxygen doxygen.config
