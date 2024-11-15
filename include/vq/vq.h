#ifndef __VQ_H__
#define __VQ_H__

#include<stdio.h>
#include<string.h>

//構造体Blocker型を定義
typedef struct {
    char rawMap[MAX_PATH_LENGTH];       //圧縮前の地図のパス
    char block_data[MAX_PATH_LENGTH];   //ブロック化したデータの格納場所のパス
    char codebook_data[MAX_PATH_LENGTH];//コードブックのパス
    char vq_data[MAX_PATH_LENGTH];      //量子化データへのパス
    char rawMap_width;                  //圧縮前の地図の幅
    char rawMap_height;                 //圧縮前の地図の高さ
    char row_element;                   //ブロック化したときの行の要素
    char column_element;                //ブロック化したときの列の要素
} Blocker;

Blocker data;
//ファイルポインタ
FILE *rawMap_fp, *block_fp, *codebook_fp, *vq_fp;
//地図をブロック化して分割するときの縦の数と横の数(端数切り上げ)
int row_vector_number = (data.rawMap_height + data.row_element - 1) / data.row_element;
int column_vector_number = (data.rawMap_width + data.column_element - 1) / data.column_element;
//ベクトルの要素数
int vector_element = data.row_element * data.column_element;
//ブロック化された地図のデータの一部
unsigned char pixel_data[column_element];
//ブロック化された地図のデータ
unsigned char block_vector[vector_element];
//同じ行に存在するブロックの要素数すべての合計
int same_row_element = rawMap_width * row_element;
//行の端数についての変数
int remainder_row_element = rawMap_width % row_element;
int additional_row_element = (row_element - remainder_row) % row_element;
unsigned char remainder_row_data[remainder_row_element];
unsigned char additional_row_data[additional_row_element];
for(int i = 0; i < additional_row_element; i++)
	additional_row_data[l] = 0xCD;
//列の端数についての変数
int remainder_column_element = rawMap_height % column_element;
int additional_column_element = (column_element - remainder_column) % column_element;
unsigned char additional_column_data[column_element];
for(int i = 0; i < column_element; i++)
	additional_column_data[l] = 0xCD;


/*ベクトル量子化*/
int vq(Blocker data);

#endif
