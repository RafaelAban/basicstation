#!/bin/bash

# Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
#
# This file is subject to the terms and conditions defined in file 'LICENSE',
# which is part of this source code package.

set -e
cd $(dirname $0)

if [[ ! -d git-repo ]]; then
    git clone -b mbedtls-2.6 --single-branch --depth 1 https://github.com/ARMmbed/mbedtls.git git-repo
fi

if [[ -z "$platform" ]] || [[ -z "$variant" ]]; then
    echo "Expecting env vars platform/variant to be set - comes naturally if called from a makefile"
    echo "If calling manually try: variant=tests platform=nix $0"
    exit 1
fi

if [[ ! -d platform-$platform ]]; then
    git clone git-repo platform-$platform
fi

cd platform-$platform
git reset --hard
make clean
