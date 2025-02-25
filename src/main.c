// SPDX-FileCopyrightText: 2024 Yuichiro Hatanaka
// SPDX-License-Identifier: BSD-3-Clause
#include<stdio.h>
#include<stdlib.h>

#include "vq/P5Header.h"
#include "vq/vq.h"
#include "vq/representativeVector.h"
#include "vq/restore.h"
#include "vq/roundup.h"

/* 引数の説明
引数1 マップ名 ex)hallway/
引数2 代表ベクトルの要素（次元）数
引数3 代表ベクトルの次元ごとの要素(違う値を指定したい場合は引数を増やして変更してください)
*/

#define RAWMAP_PATH "../map/tsudanuma.pgm"
#define BLOCK_DATA_PATH "/block.bin"
#define CODEBOOK_PATH "/codebook.bin"
#define VQ_DATA_PATH "/vq.bin"
#define RESTORE_MAP_PATH "/restore.pgm"


int main(int argc, char *argv[]) {
    //P5Header関数で使用する変数
    Header header;
    char rawMap[] = RAWMAP_PATH;
    char re[100];
	//vectorQuantization関数で使用する変数

    VQ vq;
	vq.block_row_element = atoi(argv[3]);
	vq.block_column_element = atoi(argv[3]);
	//ファイルパス指定の処理
    strcpy(vq.rawMap, RAWMAP_PATH);
    strcpy(vq.block_data, argv[1]);
    strcat(vq.block_data, argv[2]);
    strcpy(vq.vq_data, vq.block_data);
    strcpy(vq.codebook_data, vq.block_data);
    strcpy(vq.codebook_data, vq.block_data);
    strcpy(re, vq.block_data);
    strcat(vq.block_data, BLOCK_DATA_PATH);
    strcat(vq.vq_data, VQ_DATA_PATH);
    strcat(vq.codebook_data, CODEBOOK_PATH);
    strcpy(re, argv[1]);
    strcat(re, argv[2]);
    strcat(re, RESTORE_MAP_PATH);
	//ヘッダ確認
    P5Header(rawMap, &header);
    vq.rawMap_width = header.width;
    vq.rawMap_height = header.height;
	vq.header_length = header.start;

//roundup
	int recolumn = roundup(header.width, atoi(argv[3]));
	int rerow = roundup(header.height, atoi(argv[3]));
	printf("width: %d > %d\n", header.width, recolumn);
	printf("height: %d > %d\n", header.height, rerow);

	//ベクトル量子化
    vectorQuantization(vq);
	//復元
	restore(vq.codebook_data, vq.vq_data, re, header.width, header.height, vq.block_row_element, vq.block_column_element, recolumn, rerow);

    return 0;
}
