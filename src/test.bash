#!/bin/bash
# SPDX-FileCopyrightText: 2025 Yuichiro Hatanaka
# SPDX-License-Identifier: BSD-3-Clause

for((a=1;a<=$1;a++));do
i=$a
DIR="../VQMap/"
MAP="sim"
ELEM=$((i))
NUM=$((i*i))

if [ -z "$1" ]; then
i=2
fi

mkdir -p "$DIR""$MAP"/$NUM/
make
./vq "$DIR"$MAP/ $NUM $ELEM
make clean
done
