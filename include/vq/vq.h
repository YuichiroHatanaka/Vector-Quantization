// SPDX-FileCopyrightText: 2024 Yuichiro Hatanaka
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __VQ_H__
#define __VQ_H__

#include<stdio.h>
#include<string.h>

#define MAX_PATH_LENGTH 256

//構造体Blocker型を定義
typedef struct {
    char rawMap[MAX_PATH_LENGTH];       //圧縮前の地図のパス
    char block_data[MAX_PATH_LENGTH];   //ブロック化したデータの格納場所のパス
    char codebook_data[MAX_PATH_LENGTH];//コードブックのパス
    char vq_data[MAX_PATH_LENGTH];      //量子化データへのパス
	int header_length;					//マップファイルのヘッダの長さ
    int rawMap_width;                  	//圧縮前の地図の幅
    int rawMap_height;                 	//圧縮前の地図の高さ
    int block_row_element;              //ブロック化したときの行の要素
    int block_column_element;           //ブロック化したときの列の要素
} VQ;

int vectorQuantization(VQ data);

#endif
