# Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
#
# This file is subject to the terms and conditions defined in file 'LICENSE',
# which is part of this source code package.

TD=../..
platform?=linux
variant?=std

all:
	platform=${platform} variant=${variant} make -C ${TD}
	${TD}/build-${platform}-${variant}/bin/station

rpi:
	platform=rpi variant=std make

kerlink:
	platform=kerlink variant=std make

clean:
	rm -rf cups.* cups-bak.* tc.* tc-bak.* station.log station.pid

.PHONY: all clean
