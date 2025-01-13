#!/bin/bash
# SPDX-FileCopyrightText: 2025 Yuichiro Hatanaka
# SPDX-License-Identifier: BSD-3-Clause

ELEM=$1
MAP=$2
if [ -z "$1"]; then
ELEM=2
fi
if [ -z "$2"]; then
MAP=tsudanuma/
fi
mkdir -p $MAP/$ELEM/
make
./vq $ELEM $MAP/
make clean

