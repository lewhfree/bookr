# to fix: compile manually the mupdf libs first...
# cd mupdf; make

#PSP_FW_VERSION = 661
#BUILD_PRX = 1 
PSP_EBOOT_ICON=data/icon0.png
TARGET=bookr
OBJS:=bkpdf.o bklayer.o bkdocument.o bkmainmenu.o bkfilechooser.o bkpagechooser.o bkcolorschememanager.o bklogo.o bkuser.o bookr.o bkbookmark.o bkpopup.o bkcolorchooser.o bkdjvu.o 
OBJS+=bkfancytext.o bkplaintext.o bkpalmdoc.o palmdoc/palm.o
OBJS+=fzrefcount.o fzinstreammem.o fzinstreamstd.o fzimage.o fzimagepng.o fztexture.o fzfont.o fzscreenpsp.o fzscreencommon.o
OBJS+=tinystr.o tinyxmlerror.o tinyxml.o tinyxmlparser.o bkmemcpy.o
OBJS+=res_uifont.o res_txtfont.o res_uitex.o res_logo.o res_uitex2.o 

INCDIR =
EXTRACFLAGS1 = -Oz -ffast-math -s -falign-functions=32 -fomit-frame-pointer -mno-abicalls -fno-pic -fno-stack-protector
CFLAGS = -Imupdf/include -Idjvu/libdjvupsp -G0 -Wall -O2 -I$(shell psp-config --pspdev-path)/psp/include/freetype2
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS=-Lmupdf/libs -Ldjvu/libs -ldjvulibre -lmupdf -lraster -lworld -lfonts -lstream -lbase -lpspgum -lpspgu -lpsppower -lpsprtc -lpng -lz -ljpeg -lm -lfreetype -lstdc++ -lsupc++ -lbz2

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Bookr - Book Reader

PSPSDK=$(shell psp-config --pspsdk-path)
#USE_PSPSDK_LIBC=1
include $(PSPSDK)/lib/build.mak

bkmemcpy.o: bkmemcpy.S
	psp-gcc -c $< -o $@

res_uifont.c: data/urwgothicb.pfb
	bin2c $< temp res_uifont
	sed s/static// temp > $@
	rm -f temp

res_txtfont.c: data/vera.ttf
	bin2c $< temp res_txtfont
	sed s/static// temp > $@
	rm -f temp

res_uitex.c: data/ui.png
	bin2c $< temp res_uitex
	sed s/static// temp > $@
	rm -f temp

res_uitex2.c: data/ui2.png
	bin2c $< temp res_uitex2
	sed s/static// temp > $@
	rm -f temp

res_logo.c: data/logo.png
	bin2c $< temp res_logo
	sed s/static// temp > $@
	rm -f temp

sce: kxploit
	rm -Rf __SCE__bookr
	rm -Rf __SCE__bookr%
	mv bookr __SCE__bookr
	mv bookr% %__SCE__bookr
