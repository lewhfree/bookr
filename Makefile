PSP_EBOOT_ICON=data/icon0.png
TARGET=bookr
SOURCE_DIR=source
TINYXML_SOURCE_DIR=source/tinyxml
FITZ_SOURCE_DIR=source/fitz
BOOKR_SOURCE_DIR=source/bookr
FONTS_SOURCE_DIR=source/fonts
BASE_SOURCE_DIR=source/base
MUPDF_SOURCE_DIR=source/mupdf
RASTER_SOURCE_DIR=source/raster
STREAM_SOURCE_DIR=source/stream
WORLD_SOURCE_DIR=source/world

include $(FONTS_SOURCE_DIR)/objs.mk
include $(BASE_SOURCE_DIR)/objs.mk
include $(MUPDF_SOURCE_DIR)/objs.mk
include $(RASTER_SOURCE_DIR)/objs.mk
include $(STREAM_SOURCE_DIR)/objs.mk
include $(WORLD_SOURCE_DIR)/objs.mk

OBJS:= \
$(BOOKR_SOURCE_DIR)/bkpdf.o \
$(BOOKR_SOURCE_DIR)/bklayer.o \
$(BOOKR_SOURCE_DIR)/bkdocument.o \
$(BOOKR_SOURCE_DIR)/bkmainmenu.o \
$(BOOKR_SOURCE_DIR)/bkfilechooser.o \
$(BOOKR_SOURCE_DIR)/bkpagechooser.o \
$(BOOKR_SOURCE_DIR)/bkcolorschememanager.o\
$(BOOKR_SOURCE_DIR)/bklogo.o \
$(BOOKR_SOURCE_DIR)/bkuser.o \
$(SOURCE_DIR)/bookr.o \
$(BOOKR_SOURCE_DIR)/bkbookmark.o \
$(BOOKR_SOURCE_DIR)/bkpopup.o \
$(BOOKR_SOURCE_DIR)/bkcolorchooser.o \
$(BOOKR_SOURCE_DIR)/bkfancytext.o \
$(BOOKR_SOURCE_DIR)/bkplaintext.o \
$(FITZ_SOURCE_DIR)/fzrefcount.o \
$(FITZ_SOURCE_DIR)/fzinstreammem.o \
$(FITZ_SOURCE_DIR)/fzinstreamstd.o \
$(FITZ_SOURCE_DIR)/fzimage.o \
$(FITZ_SOURCE_DIR)/fzimagepng.o \
$(FITZ_SOURCE_DIR)/fztexture.o \
$(FITZ_SOURCE_DIR)/fzfont.o \
$(FITZ_SOURCE_DIR)/fzscreenpsp.o \
$(FITZ_SOURCE_DIR)/fzscreencommon.o \
$(TINYXML_SOURCE_DIR)/tinystr.o \
$(TINYXML_SOURCE_DIR)/tinyxmlerror.o \
$(TINYXML_SOURCE_DIR)/tinyxml.o \
$(TINYXML_SOURCE_DIR)/tinyxmlparser.o \
$(BOOKR_SOURCE_DIR)/bkmemcpy.o \
$(SOURCE_DIR)/res_uifont.o \
$(SOURCE_DIR)/res_txtfont.o \
$(SOURCE_DIR)/res_uitex.o \
$(SOURCE_DIR)/res_logo.o \
$(SOURCE_DIR)/res_uitex2.o \
$(addprefix $(MUPDF_SOURCE_DIR)/, $(MUPDF_OBJS)) \
$(addprefix $(RASTER_SOURCE_DIR)/, $(RASTER_OBJS)) \
$(addprefix $(WORLD_SOURCE_DIR)/, $(WORLD_OBJS)) \
$(addprefix $(FONTS_SOURCE_DIR)/, $(FONTS_OBJS)) \
$(addprefix $(STREAM_SOURCE_DIR)/, $(STREAM_OBJS)) \
$(addprefix $(BASE_SOURCE_DIR)/, $(BASE_OBJS)) \

INCDIR =
CFLAGS = -Iinclude -Iinclude/tinyxml -Iinclude/mupdf -G0 -Os -I$(shell psp-config --pspdev-path)/psp/include/freetype2 -fomit-frame-pointer
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS = -Wl,--as-needed -Wl,--strip-all
LIBS= \
	-lpspgum \
	-lpspgu \
	-lpsppower \
	-lpsprtc \
	-lpng \
	-lz \
	-ljpeg \
	-lm \
	-lfreetype \
	-lstdc++ \
	-lsupc++ \
	-lbz2

EXTRA_TARGETS = EBOOT.PBP
EXTRA_CLEAN += user.xml bookmark.xml \
$(addprefix $(FONTS_SOURCE_DIR)/, $(FONTS_OBJS)) \
$(addprefix $(BASE_SOURCE_DIR)/, $(BASE_OBJS)) \
$(addprefix $(MUPDF_SOURCE_DIR)/, $(MUPDF_OBJS)) \
$(addprefix $(RASTER_SOURCE_DIR)/, $(RASTER_OBJS)) \
$(addprefix $(STREAM_SOURCE_DIR)/, $(STREAM_OBJS)) \
$(addprefix $(WORLD_SOURCE_DIR)/, $(WORLD_OBJS))

PSP_EBOOT_TITLE = Bookr - Book Reader

PSPSDK=$(shell psp-config --pspsdk-path)
#USE_PSPSDK_LIBC=1
include $(PSPSDK)/lib/build.mak

EXTRA_TARGETS += \
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
