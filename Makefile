# to fix: compile manually the mupdf libs first...
# cd mupdf; make
PSP_EBOOT_ICON=data/icon0.png
TARGET=bookr
SOURCE_DIR=source

OBJS:= \
$(SOURCE_DIR)/bkpdf.o \
$(SOURCE_DIR)/bklayer.o \
$(SOURCE_DIR)/bkdocument.o \
$(SOURCE_DIR)/bkmainmenu.o \
$(SOURCE_DIR)/bkfilechooser.o \
$(SOURCE_DIR)/bkpagechooser.o \
$(SOURCE_DIR)/bkcolorschememanager.o\
$(SOURCE_DIR)/bklogo.o \
$(SOURCE_DIR)/bkuser.o \
$(SOURCE_DIR)/bookr.o \
$(SOURCE_DIR)/bkbookmark.o \
$(SOURCE_DIR)/bkpopup.o \
$(SOURCE_DIR)/bkcolorchooser.o \
$(SOURCE_DIR)/bkdjvu.o \
$(SOURCE_DIR)/bkfancytext.o \
$(SOURCE_DIR)/bkplaintext.o \
$(SOURCE_DIR)/bkpalmdoc.o \
palmdoc/palm.o \
$(SOURCE_DIR)/fzrefcount.o \
$(SOURCE_DIR)/fzinstreammem.o \
$(SOURCE_DIR)/fzinstreamstd.o \
$(SOURCE_DIR)/fzimage.o \
$(SOURCE_DIR)/fzimagepng.o \
$(SOURCE_DIR)/fztexture.o \
$(SOURCE_DIR)/fzfont.o \
$(SOURCE_DIR)/fzscreenpsp.o \
$(SOURCE_DIR)/fzscreencommon.o \
$(SOURCE_DIR)/tinystr.o \
$(SOURCE_DIR)/tinyxmlerror.o \
$(SOURCE_DIR)/tinyxml.o \
$(SOURCE_DIR)/tinyxmlparser.o \
$(SOURCE_DIR)/bkmemcpy.o \
$(SOURCE_DIR)/res_uifont.o \
$(SOURCE_DIR)/res_txtfont.o \
$(SOURCE_DIR)/res_uitex.o \
$(SOURCE_DIR)/res_logo.o \
$(SOURCE_DIR)/res_uitex2.o 

INCDIR =
CFLAGS = -Imupdf/include -Iinclude -Idjvu/libdjvupsp -G0 -O2 -I$(shell psp-config --pspdev-path)/psp/include/freetype2
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS=-Lmupdf/libs -Ldjvu/libs -ldjvulibre -lmupdf -lraster -lworld -lfonts -lstream -lbase -lpspgum -lpspgu -lpsppower -lpsprtc -lpng -lz -ljpeg -lm -lfreetype -lstdc++ -lsupc++ -lbz2

EXTRA_TARGETS = EBOOT.PBP
EXTRA_CLEAN += user.xml bookmark.xml
PSP_EBOOT_TITLE = Bookr - Book Reader

PSPSDK=$(shell psp-config --pspsdk-path)
#USE_PSPSDK_LIBC=1
include $(PSPSDK)/lib/build.mak

EXTRA_TARGETS= \
	$(SOURCE_DIR)/bkmemcpy.o \
	$(SOURCE_DIR)/res_uifont.c \
	$(SOURCE_DIR)/res_txtfont.c \
	$(SOURCE_DIR)/res_uitex.c \
	$(SOURCE_DIR)/res_uitex2.c \
	$(SOURCE_DIR)/res_logo.c

$(SOURCE_DIR)/bkmemcpy.o: $(SOURCE_DIR)/bkmemcpy.S
	psp-gcc -c $< -o $@

$(SOURCE_DIR)/res_uifont.c: data/urwgothicb.pfb
	bin2c $< temp res_uifont
	sed s/static// temp > $@
	rm -f temp

$(SOURCE_DIR)/res_txtfont.c: data/vera.ttf
	bin2c $< temp res_txtfont
	sed s/static// temp > $@
	rm -f temp

$(SOURCE_DIR)/res_uitex.c: data/ui.png
	bin2c $< temp res_uitex
	sed s/static// temp > $@
	rm -f temp

$(SOURCE_DIR)/res_uitex2.c: data/ui2.png
	bin2c $< temp res_uitex2
	sed s/static// temp > $@
	rm -f temp

$(SOURCE_DIR)/res_logo.c: data/logo.png
	bin2c $< temp res_logo
	sed s/static// temp > $@
	rm -f temp
