// SPDX-FileCopyrightText: 2024 Yuichiro Hatanaka
// SPDX-License-Identifier: BSD-3-Clause

#include"vq/vq.h"
#include"vq/representativeVector.h"

int vectorQuantization(VQ data){
	//ファイルポインタ
	FILE *rawMap_fp, *block_fp, *codebook_fp, *vq_fp;
	//地図をブロック化して分割するときの縦の数と横の数(端数切り上げ)
	int row_vector_number = (data.rawMap_width + data.block_row_element - 1) / data.block_row_element;
	int column_vector_number = (data.rawMap_height + data.block_column_element - 1) / data.block_column_element;
	//ベクトルの要素数
	int vector_element = data.block_row_element * data.block_column_element;
	//ブロック化された地図のデータの一部
	unsigned char block_row_data[data.block_row_element];
	//ブロック化された地図のデータ
	unsigned char raw_vector_data[vector_element];
	//同じ行に存在するブロックの要素数すべての合計
	int same_row_block_element = data.rawMap_width * data.block_column_element;
	//行の端数についての変数
	int remainder_row_element = (data.rawMap_width - 1) % data.block_row_element + 1;
	int additional_row_element = (data.block_row_element - remainder_row_element);
	unsigned char remainder_row_data[remainder_row_element];
	unsigned char additional_row_data[additional_row_element];
	for(int i = 0; i < additional_row_element; i++)
   		additional_row_data[i] = 0xCD;
	//列の端数についての変数
	int remainder_column_element = (data.rawMap_height - 1) % data.block_column_element + 1;
	int additional_column_element = (data.block_column_element - remainder_column_element);
	unsigned char unknown_block_row_data[data.block_row_element];
	for(int i = 0; i < data.block_row_element; i++)
	    unknown_block_row_data[i] = 0xCD;
	
	//代表ベクトルのカウンタ
	unsigned short representative_vector_number = 1;

	//ファイルが開くか確認
	if ((rawMap_fp = fopen(data.rawMap, "rb")) == NULL){
 		perror("ERROR: cannot open rawMap file\n");
		fclose(rawMap_fp);
      	return 1;
   	}
 	if ((block_fp = fopen(data.block_data, "w+b")) == NULL){
  		perror("ERROR: cannot open block file\n");
		fclose(rawMap_fp);
		fclose(block_fp);
   		return 1;
	}
	if ((vq_fp = fopen(data.vq_data, "w+b")) == NULL){
 		printf("ERROR: cannot open vq file\n");
		fclose(rawMap_fp);
		fclose(block_fp);
		fclose(vq_fp);
      	return 1;
   	}
   	if ((codebook_fp = fopen(data.codebook_data, "w+b")) == NULL){
    	printf("ERROR: cannot open codebook file\n");
		fclose(rawMap_fp);
		fclose(block_fp);
		fclose(vq_fp);
		fclose(codebook_fp);
     	return 1;
 	}
	
	//不明エリアを符号帳に追記
	unsigned char unknown_data[vector_element];
	for(int i = 0; i < vector_element; i++)
		unknown_data[i] = 0xCD;
	fwrite(unknown_data, sizeof(char), vector_element, codebook_fp);
	
	for(int i = 0; i < column_vector_number - 1; i++){
		//エリア1のデータを取得
		for(int j = 0; j < row_vector_number - 1; j++){
			//	データ取得し、ファイルに格納
			for(int k = 0; k < data.block_column_element; k++){
				fseek(rawMap_fp, data.header_length + same_row_block_element * i + data.block_row_element * j + data.rawMap_width * k, SEEK_SET);
				fread(block_row_data, sizeof(char), data.block_row_element, rawMap_fp);
                fwrite(block_row_data, sizeof(char), data.block_row_element, block_fp);
			}
			//	取得したベクトルと代表ベクトルを比較
            representativeVector(block_fp, codebook_fp, vq_fp, raw_vector_data, vector_element, &representative_vector_number);
        }
		//エリア2のデータを取得
		for(int k = 0; k < data.block_row_element; k++){
            fseek(rawMap_fp, data.header_length + same_row_block_element * i + data.block_row_element * (row_vector_number - 1) + data.rawMap_width * k, SEEK_SET);
            fread(remainder_row_data, sizeof(char), remainder_row_element, rawMap_fp);
            fwrite(remainder_row_data, sizeof(char), remainder_row_element, block_fp);
            fwrite(additional_row_data, sizeof(char), additional_row_element, block_fp);
        }
		representativeVector(block_fp, codebook_fp, vq_fp, raw_vector_data, vector_element, &representative_vector_number);
	}
	//エリア3
	for(int j = 0; j < row_vector_number - 1; j++){
		for(int k = 0; k < remainder_column_element; k++){
			fseek(rawMap_fp, data.header_length + same_row_block_element * (row_vector_number - 1) + data.block_row_element * j + data.rawMap_width * k, SEEK_SET);
			fread(block_row_data, sizeof(char), data.block_row_element, rawMap_fp);
			fwrite(block_row_data, sizeof(char), data.block_row_element, block_fp);
		}
		for(int k = 0; k < additional_column_element; k++)
			fwrite(&unknown_block_row_data, sizeof(char), data.block_row_element, block_fp);
		representativeVector(block_fp, codebook_fp, vq_fp, raw_vector_data, vector_element, &representative_vector_number);
	}
	//エリア４
	for(int k = 0; k < remainder_column_element; k++){
		fseek(rawMap_fp, data.header_length + same_row_block_element * (column_vector_number - 1) + data.block_row_element * (row_vector_number - 1) + data.rawMap_width * k, SEEK_SET);
		fread(remainder_row_data, sizeof(char), remainder_row_element, rawMap_fp);
		fwrite(remainder_row_data, sizeof(char), remainder_row_element, block_fp);
		fwrite(additional_row_data, sizeof(char), additional_row_element, block_fp);
	}
	for(int k = 0; k < additional_column_element; k++)
		fwrite(unknown_block_row_data, sizeof(char), data.block_row_element, block_fp);

	//代表ベクトルと比較
	representativeVector(block_fp, codebook_fp, vq_fp, raw_vector_data, vector_element, &representative_vector_number);

	//ファイルを閉じる
	fclose(rawMap_fp);
	fclose(block_fp);
	fclose(vq_fp);
	fclose(codebook_fp);

	return 0;
}
