lib-dirs:=libs

# The main target we want to generate
all: app-images

-include .config

include tools/common/project.mk

# Some example qemu invocations

# note: this relies on qemu after version 2.0
simulate-kzm:
	qemu-system-arm -nographic -M kzm \
		-kernel images/app1-image-arm-imx31

# This relies on a helper script to build a bootable image
simulate-beagle:
	beagle_run_elf images/app1-image-arm-omap3

simulate-ia32:
	qemu-system-i386 \
		-m 512 -nographic -kernel images/kernel-ia32-pc99 \
		-initrd images/app1-image-ia32-pc99

.PHONY: help
help:
	@echo "HOWTO create porject example"

