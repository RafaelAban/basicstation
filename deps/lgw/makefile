# Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
#
# This file is subject to the terms and conditions defined in file 'LICENSE',
# which is part of this source code package.

TD=../..
include ${TD}/setup.gmk
PLT=platform-${platform}

LGWLIB=${TD}/${BD}/lib/liblgw.a
LGWINC=${TD}/${BD}/include/lgw

LGWVERSION.default = 5.0.1
LGWVERSION ?= $(or ${LGWVERSION.${platform}}, ${LGWVERSION.default})

HFILES = $(wildcard ${PLT}/libloragw/inc/*.h)
SRCS = $(wildcard ${PLT}/libloragw/inc/*.c)
ARTEFACTS = ${LGWLIB} ${LGWINC} $(patsubst %, ${LGWINC}/%, $(notdir ${HFILES}) config.h)

all: $(if ${HFILES},${ARTEFACTS},${PLT})

${LGWINC}:
	@mkdir -p $@

${LGWLIB}: ${PLT}/libloragw/libloragw.a
	@mkdir -p ${@D}
	@echo "  CP    ${<F} -> $@"
	@cp $< $@

${PLT}/libloragw/libloragw.a: ${SRCS} ${HFILES}
	${MAKE} -C ${PLT}/libloragw libloragw.a CC=${CC} AR=${AR} LD=${LD} TDfull=${TDfull}

${PLT}/libloragw/inc/config.h: ${PLT}/libloragw/library.cfg
	${MAKE} -C ${PLT}/libloragw inc/config.h CC=${CC} AR=${AR} LD=${LD} TDfull=${TDfull}

${LGWINC}/%.h: ${PLT}/libloragw/inc/%.h | ${LGWINC}
	@echo "  CP    ${<F} -> $@"
	@cp $< $@

${PLT}: prep.sh
	platform=${platform} variant=${variant} lgwversion=${LGWVERSION} ./prep.sh
	$(MAKE) --no-print-directory all platform=${platform} variant=${variant}

clean:
	rm -rf ${ARTEFACTS}
	if [ -d ${PLT} ]; then ${MAKE} -C ${PLT}/libloragw clean; fi

super-clean: clean
	rm -rf git-repo platform-*

.PHONY: all clean super-clean platform-${platform}