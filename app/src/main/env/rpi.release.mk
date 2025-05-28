CC := g++-8.1.0
MAX_PARALLEL_JOBS := 4

LIB_DIRS := \
	/usr/local/gcc-8.1.0/lib \
	/usr/local/lib

INCLUDE_DIRS := \
	/usr/local/gcc-8.1.0/include \
	/usr/local/include

BUILD_DEPENDENCIES :=

LINK_LIBRARIES := \
	$(LINK_LIBRARIES) \
	X11

BUILD_FLAGS := \
	-pthread
