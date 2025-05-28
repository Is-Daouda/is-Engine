MAX_PARALLEL_JOBS := 8
CLEAN_OUTPUT := true
DUMP_ASSEMBLY := false

_CFLAGS_STD := -std=c++17
_CFLAGS_WARNINGS := -Wall
_CFLAGS_OTHER := -fdiagnostics-color=always
CFLAGS := $(_CFLAGS_STD) $(_CFLAGS_WARNINGS) $(_CFLAGS_OTHER)

LINK_LIBRARIES := \
	sfml-graphics \
	sfml-audio \
	sfml-network \
	sfml-window \
	sfml-system

PRECOMPILED_HEADER := PCH

PRODUCTION_FOLDER := build

PRODUCTION_EXCLUDE := \
	*.psd \
	*.rar \
	*.7z \
	Thumbs.db \
	.DS_Store

PRODUCTION_DEPENDENCIES := \
	assets

