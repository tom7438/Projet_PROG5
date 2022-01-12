ACLOCAL_AMFLAGS = -I ../m4

if HAVE_ARM_COMPILER

# big endian and no code transformations to work with thumb
AM_CFLAGS=-mbig-endian -mno-thumb-interwork
AM_CCASFLAGS=-mbig-endian -mno-thumb-interwork

# common flags to link without any additionnal std stuff
AM_LDFLAGS=-nostdlib --entry main -n

# Start addresses of various sections can be set using linker options or linker script
# (uncomment one of the following two lines)
#AM_LDFLAGS+=-T linker_script
AM_LDFLAGS+=-Wl,--section-start -Wl,.text=0x20 -Wl,--section-start -Wl,.data=0x2800

# Big endian
AM_LDFLAGS+=-Wl,-EB

noinst_PROGRAMS=example1 example2 example3 example4 example6 example7 example8 example9 example16 

example1_SOURCES=example1.s
example2_SOURCES=example2.s
example3_SOURCES=example3.s
example4_SOURCES=example4.s
example6_SOURCES=example6.s
example7_SOURCES=example7.s
example8_SOURCES=example8.s
example9_SOURCES=example9.s
example16_SOURCES=example16.s

endif
