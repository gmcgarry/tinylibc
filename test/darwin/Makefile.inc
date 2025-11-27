CC ?= clang
CFLAGS += -nostdinc -fno-builtin
CFLAGS += -Wno-nullability-completeness

SDK=$(shell xcrun --show-sdk-path)
TOOLCHAIN=$(shell xcrun --show-toolchain-path)
INC += -I$(SDK)/usr/include -I$(TOOLCHAIN)/usr/include -I$(TOOLCHAIN)/usr/lib/clang/17/include
