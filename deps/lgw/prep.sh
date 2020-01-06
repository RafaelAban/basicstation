#!/bin/bash

# Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
#
# This file is subject to the terms and conditions defined in file 'LICENSE',
# which is part of this source code package.

set -e
cd $(dirname $0)

lgwversion="v${lgwversion:-5.0.1}"

if [[ ! -d git-repo ]]; then
    git clone https://github.com/Lora-net/lora_gateway.git git-repo
fi

if [[ -z "${platform}" ]] || [[ -z "${variant}" ]]; then
    echo "Expecting env vars platform/variant to be set - comes naturally if called from a makefile"
    echo "If calling manually try: variant=std platform=linux $0"
    exit 1
fi

if [[ ! -d platform-${platform} ]]; then
    git clone -b ${lgwversion} git-repo platform-${platform}

    cd platform-${platform}
    if [ -f ../${lgwversion}-${platform}.patch ]; then
        echo "Applying ${lgwversion}-${platform}.patch ..."
        git apply ../${lgwversion}-${platform}.patch
    fi
fi
