CC = gcc
CPP := g++
AR := ar cru
RANLIB := ranlib 
RM := rm -rf

CPPFLAGS := 
CPPFLAGS += -I.   
#CPPFLAGS += -g -O2
CPPFLAGS += -g3 -O0

CPPFLAGS += -I./SDL-1.2.15/include

CPPFLAGS += -I./include

CPPFLAGS += -I./thirdparty/harfbuzz/src
CPPFLAGS += -I./thirdparty/jbig2dec
CPPFLAGS += -I./thirdparty/openjpeg/libopenjpeg 
CPPFLAGS += -I./thirdparty/jpeg 
CPPFLAGS += -I./thirdparty/mujs 
CPPFLAGS += -I./thirdparty/zlib 
CPPFLAGS += -I./thirdparty/freetype/include 

CPPFLAGS += -I./scripts/freetype 
CPPFLAGS += -I./scripts/jpeg 
CPPFLAGS += -I./scripts/openjpeg

CPPFLAGS += -I./source/fitz 
CPPFLAGS += -I./source/pdf 
CPPFLAGS += -I./source/xps 
CPPFLAGS += -I./source/cbz 
CPPFLAGS += -I./source/img 
CPPFLAGS += -I./source/tiff 

CPPFLAGS += -I./generated 

CPPFLAGS += -I./resources 

CPPFLAGS += -DFT2_BUILD_LIBRARY -DDARWIN_NO_CARBON -DHAVE_STDINT_H 
CPPFLAGS += -DOPJ_HAVE_STDINT_H 
CPPFLAGS += '-DFT_CONFIG_MODULES_H="slimftmodules.h"' 
CPPFLAGS += '-DFT_CONFIG_OPTIONS_H="slimftoptions.h"' 
CPPFLAGS += -Dhb_malloc_impl=hb_malloc -Dhb_calloc_impl=hb_calloc 
CPPFLAGS += -Dhb_realloc_impl=hb_realloc -Dhb_free_impl=hb_free 
CPPFLAGS += -DHAVE_OT -DHAVE_UCDN -DHB_NO_MT

ifdef MEMENTO
CPPFLAGS += -DMEMENTO -DMEMENTO_LEAKONLY
endif


#LOCAL_CFLAGS += -Wall -Wno-maybe-uninitialized

ifeq ($(TARGET_ARCH),arm)
#LOCAL_CFLAGS += -DARCH_ARM -DARCH_THUMB -DARCH_ARM_CAN_LOAD_UNALIGNED
endif

ifdef SUPPORT_GPROOF
#LOCAL_CFLAGS += -DSUPPORT_GPROOF
endif

#LOCAL_CFLAGS += -DAA_BITS=8

ifdef MEMENTO
#LOCAL_CFLAGS += -DMEMENTO -DMEMENTO_LEAKONLY
endif

#ifdef SSL_BUILD
#LOCAL_CFLAGS += -DHAVE_OPENSSL
#endif

#ifdef V8_BUILD
#CPPFLAGS += ./thirdparty/$(V8)/include
#endif

#ifdef SSL_BUILD
#CPPFLAGS += ./thirdparty/openssl/include
#endif

LDFLAGS := 
LDFLAGS += -lSDL -L./SDL-1.2.15 -lwinmm -lgdi32 
LDFLAGS += -lcomdlg32 -lgdi32 -lm -lstdc++

OBJS := 

#thirdparty
OBJS += thirdparty/mujs/one.o
OBJS += thirdparty/harfbuzz/src/hb-blob.o 
OBJS += thirdparty/harfbuzz/src/hb-buffer.o 
OBJS += thirdparty/harfbuzz/src/hb-buffer-serialize.o 
OBJS += thirdparty/harfbuzz/src/hb-common.o 
OBJS += thirdparty/harfbuzz/src/hb-face.o 
OBJS += thirdparty/harfbuzz/src/hb-fallback-shape.o 
OBJS += thirdparty/harfbuzz/src/hb-font.o 
OBJS += thirdparty/harfbuzz/src/hb-ft.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-font.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-layout.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-map.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-complex-arabic.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-complex-default.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-complex-hangul.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-complex-hebrew.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-complex-indic-table.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-complex-indic.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-complex-myanmar.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-complex-thai.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-complex-tibetan.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-complex-use-table.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-complex-use.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-fallback.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape-normalize.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-shape.o 
OBJS += thirdparty/harfbuzz/src/hb-ot-tag.o 
OBJS += thirdparty/harfbuzz/src/hb-set.o 
OBJS += thirdparty/harfbuzz/src/hb-shape-plan.o 
OBJS += thirdparty/harfbuzz/src/hb-shape.o 
OBJS += thirdparty/harfbuzz/src/hb-shaper.o 
OBJS += thirdparty/harfbuzz/src/hb-ucdn.o 
OBJS += thirdparty/harfbuzz/src/hb-unicode.o 
OBJS += thirdparty/harfbuzz/src/hb-warning.o 
OBJS += thirdparty/jbig2dec/jbig2.o
OBJS += thirdparty/jbig2dec/jbig2_arith.o
OBJS += thirdparty/jbig2dec/jbig2_arith_iaid.o
OBJS += thirdparty/jbig2dec/jbig2_arith_int.o
OBJS += thirdparty/jbig2dec/jbig2_generic.o
OBJS += thirdparty/jbig2dec/jbig2_halftone.o
OBJS += thirdparty/jbig2dec/jbig2_huffman.o
OBJS += thirdparty/jbig2dec/jbig2_image.o
OBJS += thirdparty/jbig2dec/jbig2_metadata.o
OBJS += thirdparty/jbig2dec/jbig2_mmr.o
OBJS += thirdparty/jbig2dec/jbig2_page.o
OBJS += thirdparty/jbig2dec/jbig2_refinement.o
OBJS += thirdparty/jbig2dec/jbig2_segment.o
OBJS += thirdparty/jbig2dec/jbig2_symbol_dict.o
OBJS += thirdparty/jbig2dec/jbig2_text.o
OBJS += thirdparty/openjpeg/libopenjpeg/bio.o
OBJS += thirdparty/openjpeg/libopenjpeg/cidx_manager.o
OBJS += thirdparty/openjpeg/libopenjpeg/cio.o
OBJS += thirdparty/openjpeg/libopenjpeg/dwt.o
OBJS += thirdparty/openjpeg/libopenjpeg/event.o
OBJS += thirdparty/openjpeg/libopenjpeg/function_list.o
OBJS += thirdparty/openjpeg/libopenjpeg/image.o
OBJS += thirdparty/openjpeg/libopenjpeg/invert.o
OBJS += thirdparty/openjpeg/libopenjpeg/j2k.o
OBJS += thirdparty/openjpeg/libopenjpeg/jp2.o
OBJS += thirdparty/openjpeg/libopenjpeg/mct.o
OBJS += thirdparty/openjpeg/libopenjpeg/mqc.o
OBJS += thirdparty/openjpeg/libopenjpeg/openjpeg.o
OBJS += thirdparty/openjpeg/libopenjpeg/opj_clock.o
OBJS += thirdparty/openjpeg/libopenjpeg/phix_manager.o
OBJS += thirdparty/openjpeg/libopenjpeg/pi.o
OBJS += thirdparty/openjpeg/libopenjpeg/ppix_manager.o
OBJS += thirdparty/openjpeg/libopenjpeg/raw.o
OBJS += thirdparty/openjpeg/libopenjpeg/t1.o
#OBJS += thirdparty/openjpeg/libopenjpeg/t1_generate_luts.o #there is a main function
OBJS += thirdparty/openjpeg/libopenjpeg/t2.o
OBJS += thirdparty/openjpeg/libopenjpeg/tcd.o
OBJS += thirdparty/openjpeg/libopenjpeg/tgt.o
OBJS += thirdparty/openjpeg/libopenjpeg/thix_manager.o
OBJS += thirdparty/openjpeg/libopenjpeg/tpix_manager.o
OBJS += thirdparty/jpeg/jaricom.o
OBJS += thirdparty/jpeg/jcomapi.o
OBJS += thirdparty/jpeg/jdapimin.o
OBJS += thirdparty/jpeg/jdapistd.o
OBJS += thirdparty/jpeg/jdarith.o
OBJS += thirdparty/jpeg/jdatadst.o
OBJS += thirdparty/jpeg/jdatasrc.o
OBJS += thirdparty/jpeg/jdcoefct.o
OBJS += thirdparty/jpeg/jdcolor.o
OBJS += thirdparty/jpeg/jddctmgr.o
OBJS += thirdparty/jpeg/jdhuff.o
OBJS += thirdparty/jpeg/jdinput.o
OBJS += thirdparty/jpeg/jdmainct.o
OBJS += thirdparty/jpeg/jdmarker.o
OBJS += thirdparty/jpeg/jdmaster.o
OBJS += thirdparty/jpeg/jdmerge.o
OBJS += thirdparty/jpeg/jdpostct.o
OBJS += thirdparty/jpeg/jdsample.o
OBJS += thirdparty/jpeg/jdtrans.o
OBJS += thirdparty/jpeg/jerror.o
OBJS += thirdparty/jpeg/jfdctflt.o
OBJS += thirdparty/jpeg/jfdctfst.o
OBJS += thirdparty/jpeg/jfdctint.o
OBJS += thirdparty/jpeg/jidctflt.o
OBJS += thirdparty/jpeg/jidctfst.o
OBJS += thirdparty/jpeg/jidctint.o
OBJS += thirdparty/jpeg/jmemmgr.o
OBJS += thirdparty/jpeg/jquant1.o
OBJS += thirdparty/jpeg/jquant2.o
OBJS += thirdparty/jpeg/jutils.o
OBJS += thirdparty/zlib/adler32.o
OBJS += thirdparty/zlib/compress.o
OBJS += thirdparty/zlib/crc32.o
OBJS += thirdparty/zlib/deflate.o
OBJS += thirdparty/zlib/inffast.o
OBJS += thirdparty/zlib/inflate.o
OBJS += thirdparty/zlib/inftrees.o
OBJS += thirdparty/zlib/trees.o
OBJS += thirdparty/zlib/uncompr.o
OBJS += thirdparty/zlib/zutil.o
OBJS += thirdparty/freetype/src/base/ftbase.o
OBJS += thirdparty/freetype/src/base/ftbbox.o
OBJS += thirdparty/freetype/src/base/ftbitmap.o
OBJS += thirdparty/freetype/src/base/ftfntfmt.o
OBJS += thirdparty/freetype/src/base/ftgasp.o
OBJS += thirdparty/freetype/src/base/ftglyph.o
OBJS += thirdparty/freetype/src/base/ftinit.o
OBJS += thirdparty/freetype/src/base/ftstroke.o
OBJS += thirdparty/freetype/src/base/ftsynth.o
OBJS += thirdparty/freetype/src/base/ftsystem.o
OBJS += thirdparty/freetype/src/base/fttype1.o
OBJS += thirdparty/freetype/src/cff/cff.o
OBJS += thirdparty/freetype/src/cid/type1cid.o
OBJS += thirdparty/freetype/src/psaux/psaux.o
OBJS += thirdparty/freetype/src/pshinter/pshinter.o
OBJS += thirdparty/freetype/src/psnames/psnames.o
OBJS += thirdparty/freetype/src/raster/raster.o
OBJS += thirdparty/freetype/src/smooth/smooth.o
OBJS += thirdparty/freetype/src/sfnt/sfnt.o
OBJS += thirdparty/freetype/src/truetype/truetype.o
OBJS += thirdparty/freetype/src/type1/type1.o

#OBJS += source/fitz/*.o
OBJS += source/fitz/bbox-device.o
OBJS += source/fitz/bidi-std.o
OBJS += source/fitz/bidi.o
OBJS += source/fitz/bitmap.o
OBJS += source/fitz/buffer.o
OBJS += source/fitz/colorspace.o
OBJS += source/fitz/compressed-buffer.o
OBJS += source/fitz/context.o
OBJS += source/fitz/crypt-aes.o
OBJS += source/fitz/crypt-arc4.o
OBJS += source/fitz/crypt-md5.o
OBJS += source/fitz/crypt-sha2.o
OBJS += source/fitz/device.o
OBJS += source/fitz/document-all.o
OBJS += source/fitz/document.o
OBJS += source/fitz/draw-affine.o
OBJS += source/fitz/draw-blend.o
OBJS += source/fitz/draw-device.o
OBJS += source/fitz/draw-edge.o
OBJS += source/fitz/draw-glyph.o
OBJS += source/fitz/draw-mesh.o
OBJS += source/fitz/draw-paint.o
OBJS += source/fitz/draw-path.o
OBJS += source/fitz/draw-scale-simple.o
OBJS += source/fitz/draw-unpack.o
OBJS += source/fitz/error.o
OBJS += source/fitz/filter-basic.o
OBJS += source/fitz/filter-dct.o
OBJS += source/fitz/filter-fax.o
OBJS += source/fitz/filter-flate.o
OBJS += source/fitz/filter-jbig2.o
OBJS += source/fitz/filter-leech.o
OBJS += source/fitz/filter-lzw.o
OBJS += source/fitz/filter-predict.o
OBJS += source/fitz/font.o
OBJS += source/fitz/ftoa.o
OBJS += source/fitz/function.o
OBJS += source/fitz/geometry.o
OBJS += source/fitz/getopt.o
OBJS += source/fitz/glyph.o
OBJS += source/fitz/halftone.o
OBJS += source/fitz/harfbuzz.o
OBJS += source/fitz/hash.o
OBJS += source/fitz/image.o
OBJS += source/fitz/jmemcust.o
OBJS += source/fitz/link.o
OBJS += source/fitz/list-device.o
OBJS += source/fitz/load-bmp.o
OBJS += source/fitz/load-gif.o
OBJS += source/fitz/load-jpeg.o
OBJS += source/fitz/load-jpx.o
OBJS += source/fitz/load-jxr.o
OBJS += source/fitz/load-png.o
OBJS += source/fitz/load-tiff.o
OBJS += source/fitz/memento.o
OBJS += source/fitz/memory.o
OBJS += source/fitz/noto.o
OBJS += source/fitz/outline.o
OBJS += source/fitz/output-pcl.o
OBJS += source/fitz/output-ps.o
OBJS += source/fitz/output-pwg.o
OBJS += source/fitz/output.o
OBJS += source/fitz/path.o
OBJS += source/fitz/pixmap.o
OBJS += source/fitz/pool.o
OBJS += source/fitz/printf.o
OBJS += source/fitz/separation.o
OBJS += source/fitz/shade.o
OBJS += source/fitz/stext-device.o
OBJS += source/fitz/stext-output.o
OBJS += source/fitz/stext-paragraph.o
OBJS += source/fitz/stext-search.o
OBJS += source/fitz/store.o
OBJS += source/fitz/stream-open.o
OBJS += source/fitz/stream-prog.o
OBJS += source/fitz/stream-read.o
OBJS += source/fitz/string.o
OBJS += source/fitz/strtod.o
OBJS += source/fitz/strtof.o
OBJS += source/fitz/svg-device.o
OBJS += source/fitz/tempfile.o
OBJS += source/fitz/test-device.o
OBJS += source/fitz/text.o
OBJS += source/fitz/time.o
OBJS += source/fitz/trace-device.o
OBJS += source/fitz/transition.o
OBJS += source/fitz/tree.o
OBJS += source/fitz/ucdn.o
OBJS += source/fitz/unzip.o
OBJS += source/fitz/util.o
OBJS += source/fitz/xml.o

#OBJS += $(wildcard source/pdf/*.o)
OBJS += source/pdf/pdf-annot-edit.o
OBJS += source/pdf/pdf-annot.o
OBJS += source/pdf/pdf-appearance.o
OBJS += source/pdf/pdf-clean-file.o
OBJS += source/pdf/pdf-clean.o
OBJS += source/pdf/pdf-cmap-load.o
OBJS += source/pdf/pdf-cmap-parse.o
OBJS += source/pdf/pdf-cmap-table.o
OBJS += source/pdf/pdf-cmap.o
OBJS += source/pdf/pdf-colorspace.o
OBJS += source/pdf/pdf-crypt.o
OBJS += source/pdf/pdf-device.o
OBJS += source/pdf/pdf-encoding.o
OBJS += source/pdf/pdf-event.o
OBJS += source/pdf/pdf-field.o
OBJS += source/pdf/pdf-font.o
OBJS += source/pdf/pdf-form.o
OBJS += source/pdf/pdf-function.o
OBJS += source/pdf/pdf-graft.o
OBJS += source/pdf/pdf-image.o
OBJS += source/pdf/pdf-interpret.o
OBJS += source/pdf/pdf-lex.o
OBJS += source/pdf/pdf-metrics.o
OBJS += source/pdf/pdf-nametree.o
OBJS += source/pdf/pdf-object.o
OBJS += source/pdf/pdf-op-buffer.o
OBJS += source/pdf/pdf-op-filter.o
OBJS += source/pdf/pdf-op-run.o
OBJS += source/pdf/pdf-outline.o
OBJS += source/pdf/pdf-page.o
OBJS += source/pdf/pdf-parse.o
OBJS += source/pdf/pdf-pattern.o
OBJS += source/pdf/pdf-pkcs7.o
OBJS += source/pdf/pdf-repair.o
OBJS += source/pdf/pdf-resources.o
OBJS += source/pdf/pdf-run.o
OBJS += source/pdf/pdf-shade.o
OBJS += source/pdf/pdf-store.o
OBJS += source/pdf/pdf-stream.o
OBJS += source/pdf/pdf-type3.o
OBJS += source/pdf/pdf-unicode.o
OBJS += source/pdf/pdf-write.o
OBJS += source/pdf/pdf-xobject.o
OBJS += source/pdf/pdf-xref.o

#OBJS += $(wildcard source/xps/*.o)
OBJS += source/xps/xps-common.o
OBJS += source/xps/xps-doc.o
OBJS += source/xps/xps-glyphs.o
OBJS += source/xps/xps-gradient.o
OBJS += source/xps/xps-image.o
OBJS += source/xps/xps-link.o
OBJS += source/xps/xps-outline.o
OBJS += source/xps/xps-path.o
OBJS += source/xps/xps-resource.o
OBJS += source/xps/xps-tile.o
OBJS += source/xps/xps-util.o
OBJS += source/xps/xps-zip.o

#OBJS += $(wildcard source/cbz/*.o)
OBJS += source/cbz/mucbz.o
OBJS += source/cbz/muimg.o
OBJS += source/cbz/mutiff.o

#OBJS += $(wildcard source/gprf/*.o)
OBJS += source/gprf/gprf-doc.o
OBJS += source/gprf/gprf-skeleton.o

#OBJS += $(wildcard source/html/*.o)
OBJS += source/html/css-apply.o
OBJS += source/html/css-parse.o
OBJS += source/html/epub-doc.o
OBJS += source/html/html-doc.o
OBJS += source/html/html-font.o
OBJS += source/html/html-layout.o

#OBJS += $(wildcard generated/*.o)
OBJS += generated/CharisSIL-B.o
OBJS += generated/CharisSIL-BI.o
OBJS += generated/CharisSIL-I.o
OBJS += generated/CharisSIL-R.o
OBJS += generated/Dingbats.o
OBJS += generated/DroidSansFallback.o
OBJS += generated/DroidSansFallbackFull.o
OBJS += generated/NimbusMono-Bold.o
OBJS += generated/NimbusMono-BoldOblique.o
OBJS += generated/NimbusMono-Oblique.o
OBJS += generated/NimbusMono-Regular.o
OBJS += generated/NimbusRomNo9L-Med.o
OBJS += generated/NimbusRomNo9L-MedIta.o
OBJS += generated/NimbusRomNo9L-Reg.o
OBJS += generated/NimbusRomNo9L-RegIta.o
OBJS += generated/NimbusSanL-Bol.o
OBJS += generated/NimbusSanL-BolIta.o
OBJS += generated/NimbusSanL-Reg.o
OBJS += generated/NimbusSanL-RegIta.o
OBJS += generated/NotoEmoji-Regular.o
OBJS += generated/NotoKufiArabic-Regular.o
OBJS += generated/NotoNaskhArabic-Regular.o
OBJS += generated/NotoNastaliqUrdu-Regular.o
OBJS += generated/NotoSans-Regular.o
OBJS += generated/NotoSansArmenian-Regular.o
OBJS += generated/NotoSansAvestan-Regular.o
OBJS += generated/NotoSansBalinese-Regular.o
OBJS += generated/NotoSansBamum-Regular.o
OBJS += generated/NotoSansBatak-Regular.o
OBJS += generated/NotoSansBengali-Regular.o
OBJS += generated/NotoSansBrahmi-Regular.o
OBJS += generated/NotoSansBuginese-Regular.o
OBJS += generated/NotoSansBuhid-Regular.o
OBJS += generated/NotoSansCanadianAboriginal-Regular.o
OBJS += generated/NotoSansCarian-Regular.o
OBJS += generated/NotoSansCham-Regular.o
OBJS += generated/NotoSansCherokee-Regular.o
OBJS += generated/NotoSansCoptic-Regular.o
OBJS += generated/NotoSansCuneiform-Regular.o
OBJS += generated/NotoSansCypriot-Regular.o
OBJS += generated/NotoSansDeseret-Regular.o
OBJS += generated/NotoSansDevanagari-Regular.o
OBJS += generated/NotoSansEgyptianHieroglyphs-Regular.o
OBJS += generated/NotoSansEthiopic-Regular.o
OBJS += generated/NotoSansGeorgian-Regular.o
OBJS += generated/NotoSansGlagolitic-Regular.o
OBJS += generated/NotoSansGothic-Regular.o
OBJS += generated/NotoSansGujarati-Regular.o
OBJS += generated/NotoSansGurmukhi-Regular.o
OBJS += generated/NotoSansHanunoo-Regular.o
OBJS += generated/NotoSansHebrew-Regular.o
OBJS += generated/NotoSansImperialAramaic-Regular.o
OBJS += generated/NotoSansInscriptionalPahlavi-Regular.o
OBJS += generated/NotoSansInscriptionalParthian-Regular.o
OBJS += generated/NotoSansJavanese-Regular.o
OBJS += generated/NotoSansKaithi-Regular.o
OBJS += generated/NotoSansKannada-Regular.o
OBJS += generated/NotoSansKayahLi-Regular.o
OBJS += generated/NotoSansKharoshthi-Regular.o
OBJS += generated/NotoSansKhmer-Regular.o
OBJS += generated/NotoSansLao-Regular.o
OBJS += generated/NotoSansLepcha-Regular.o
OBJS += generated/NotoSansLimbu-Regular.o
OBJS += generated/NotoSansLinearB-Regular.o
OBJS += generated/NotoSansLisu-Regular.o
OBJS += generated/NotoSansLycian-Regular.o
OBJS += generated/NotoSansLydian-Regular.o
OBJS += generated/NotoSansMalayalam-Regular.o
OBJS += generated/NotoSansMandaic-Regular.o
OBJS += generated/NotoSansMeeteiMayek-Regular.o
OBJS += generated/NotoSansMongolian-Regular.o
OBJS += generated/NotoSansMyanmar-Regular.o
OBJS += generated/NotoSansNewTaiLue-Regular.o
OBJS += generated/NotoSansNKo-Regular.o
OBJS += generated/NotoSansOgham-Regular.o
OBJS += generated/NotoSansOlChiki-Regular.o
OBJS += generated/NotoSansOldItalic-Regular.o
OBJS += generated/NotoSansOldPersian-Regular.o
OBJS += generated/NotoSansOldSouthArabian-Regular.o
OBJS += generated/NotoSansOldTurkic-Regular.o
OBJS += generated/NotoSansOriya-Regular.o
OBJS += generated/NotoSansOsmanya-Regular.o
OBJS += generated/NotoSansPhagsPa-Regular.o
OBJS += generated/NotoSansPhoenician-Regular.o
OBJS += generated/NotoSansRejang-Regular.o
OBJS += generated/NotoSansRunic-Regular.o
OBJS += generated/NotoSansSamaritan-Regular.o
OBJS += generated/NotoSansSaurashtra-Regular.o
OBJS += generated/NotoSansShavian-Regular.o
OBJS += generated/NotoSansSinhala-Regular.o
OBJS += generated/NotoSansSundanese-Regular.o
OBJS += generated/NotoSansSylotiNagri-Regular.o
OBJS += generated/NotoSansSymbols-Regular.o
OBJS += generated/NotoSansSyriacEastern-Regular.o
OBJS += generated/NotoSansSyriacEstrangela-Regular.o
OBJS += generated/NotoSansSyriacWestern-Regular.o
OBJS += generated/NotoSansTagalog-Regular.o
OBJS += generated/NotoSansTagbanwa-Regular.o
OBJS += generated/NotoSansTaiLe-Regular.o
OBJS += generated/NotoSansTaiTham-Regular.o
OBJS += generated/NotoSansTaiViet-Regular.o
OBJS += generated/NotoSansTamil-Regular.o
OBJS += generated/NotoSansTelugu-Regular.o
OBJS += generated/NotoSansThaana-Regular.o
OBJS += generated/NotoSansThai-Regular.o
OBJS += generated/NotoSansTibetan-Regular.o
OBJS += generated/NotoSansTifinagh-Regular.o
OBJS += generated/NotoSansUgaritic-Regular.o
OBJS += generated/NotoSansVai-Regular.o
OBJS += generated/NotoSansYi-Regular.o
OBJS += generated/NotoSerif-Regular.o
OBJS += generated/NotoSerifArmenian-Regular.o
OBJS += generated/NotoSerifBengali-Regular.o
OBJS += generated/NotoSerifGeorgian-Regular.o
OBJS += generated/NotoSerifGujarati-Regular.o
OBJS += generated/NotoSerifKannada-Regular.o
OBJS += generated/NotoSerifKhmer-Regular.o
OBJS += generated/NotoSerifLao-Regular.o
OBJS += generated/NotoSerifMalayalam-Regular.o
OBJS += generated/NotoSerifTamil-Regular.o
OBJS += generated/NotoSerifTelugu-Regular.o
OBJS += generated/NotoSerifThai-Regular.o
OBJS += generated/StandardSymL.o

OBJS += source/pdf/js/pdf-js.o

HELLOCPP_OBJS :=
HELLOCPP_OBJS += platform/x11/pdfapp.o
HELLOCPP_OBJS += platform/x11/x11_image.o

all : mupdf-x11

sdl.a : 
	make -f Makefile.mingw -C ./SDL-1.2.15

mupdf.a : $(OBJS)
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

mupdf-x11: sdl.a mupdf.a $(HELLOCPP_OBJS)
	$(CC) ./SDL-1.2.15/src/main/dummy/SDL_dummy_main.c ./platform/x11/sdl_main.c $(HELLOCPP_OBJS) mupdf.a -o $@ -I. $(CPPFLAGS) $(LDFLAGS)

%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

%.o : %.cc
	$(CPP) $(CPPFLAGS) -o $@ -c $<

%.o : %.c
	$(CC) $(CPPFLAGS) -o $@ -c $<
	
test:
	./mupdf-x11 test_files/2.pdf 

clean :
	$(RM) $(OBJS) $(HELLOCPP_OBJS) mupdf.a mupdf-x11 *.exe *.a
	make -f Makefile.mingw -C ./SDL-1.2.15 clean
