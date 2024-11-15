#include<stdio.h>
#include<string.h>
#include"tmp/representativeVector.h"

#define RAWMAP_PATH "map/sim.pgm"
#define BLOCK_DATA_PATH "sim/block.bin"
#define CODEBOOK_PATH "sim/codebook.bin"
#define VQ_DATA_PATH "sim/vq.bin"
#define RAW_WIDTH 381
#define RAW_HEIGHT 443
#define ROW_ELEMENT 2
#define COLUMN_ELEMENT 2
#define MAX_PATH_LENGTH 255
#define HEADER_LENGTH 15

//構造体Blocker型を定義
typedef struct {
	int header_length;					//マップファイルのヘッダの長さ
	char rawMap[MAX_PATH_LENGTH];		//圧縮前の地図のパス
	char block_data[MAX_PATH_LENGTH];	//ブロック化したデータの格納場所のパス
	char codebook_data[MAX_PATH_LENGTH];//コードブックのパス
	char vq_data[MAX_PATH_LENGTH];		//量子化データへのパス
	int rawMap_width;					//圧縮前の地図の幅
	int rawMap_height;					//圧縮前の地図の高さ
	int block_row_element;				//ブロック化したときの行の要素
	int block_column_element;			//ブロック化したときの列の要素
} Blocker;




int vq(Blocker data){
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
	//int additional_row_element = (data.block_row_element - remainder_row_element) % data.block_row_element;
	int additional_row_element = (data.block_row_element - remainder_row_element);
	unsigned char remainder_row_data[remainder_row_element];
	unsigned char additional_row_data[additional_row_element];
	for(int i = 0; i < additional_row_element; i++)
   		additional_row_data[i] = 0xCD;
	//列の端数についての変数
	int remainder_column_element = (data.rawMap_height - 1) % data.block_column_element + 1;
	//int additional_column_element = (data.block_column_element - remainder_column_element) % data.block_column_element;
	int additional_column_element = (data.block_column_element - remainder_column_element);
	unsigned char unknown_block_row_data[data.block_row_element];
	for(int i = 0; i < data.block_row_element; i++)
	    unknown_block_row_data[i] = 0xCD;
	
	printf("rawMap_width: %d\n", data.rawMap_width);
	printf("rawMap_height: %d\n", data.rawMap_height);
	printf("block_row_element: %d\n", data.block_row_element);
	printf("block_column_element: %d\n", data.block_column_element);
	printf("row_vector_number: %d\n", row_vector_number);
	printf("column_vector_number: %d\n", column_vector_number);
	printf("vector_element: %d\n", vector_element);
	printf("size of block_row_data: %ld\n", sizeof(block_row_data));
	//printf("size of raw_vector_data: %ld\n", sizeof(raw_vector_data));
	printf("same row block element: %d\n", same_row_block_element);
	printf("remainder row element: %d\n", remainder_row_element);
	printf("additional row element: %d\n", additional_row_element);
	printf("size of remainder_row_data: %ld\n", sizeof(remainder_row_data));
	printf("size of additional_row_data: %ld\n", sizeof(additional_row_data));
	printf("remainder column element: %d\n", remainder_column_element);
	printf("additional column element: %d\n", additional_column_element);
	printf("size of unknown_block_row_data: %ld\n", sizeof(unknown_block_row_data));
	
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
			//fseek(block_fp, -vector_element, SEEK_CUR);
            //fread(&pixel_data, sizeof(char), vector_element, block_fp);
            //representativeVector(codebook_fp, vq_fp, rawVec, vecElem, brepVecNum, &repVecNum);
            //brepVecNum = repVecNum;
        }
		//エリア2のデータを取得
		for(int k = 0; k < data.block_row_element; k++){
            fseek(rawMap_fp, data.header_length + same_row_block_element * i + data.block_row_element * (row_vector_number - 1) + data.rawMap_width * k, SEEK_SET);
            fread(remainder_row_data, sizeof(char), remainder_row_element, rawMap_fp);
            fwrite(remainder_row_data, sizeof(char), remainder_row_element, block_fp);
            fwrite(additional_row_data, sizeof(char), additional_row_element, block_fp);
        }
	       //代表ベクトルと比較
    	    /*fseek(block_fp, -vecElem, SEEK_CUR);
       		fread(&rawVec, sizeof(char), vecElem, block_fp);
        	representativeVector(codebook_fp, vq_fp, rawVec, vecElem, brepVecNum, &repVecNum);
        	brepVecNum = repVecNum;*/
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
		//representativeVector;
		// b = r;
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
	//ファイルを閉じる
	fclose(rawMap_fp);
	fclose(block_fp);
	fclose(vq_fp);
	fclose(codebook_fp);

	return 0;
}



int main(void){
	//Blocker型の構造体blockにデータを入力
	Blocker block;
	block.header_length = HEADER_LENGTH;
	block.rawMap_width = RAW_WIDTH;
	block.rawMap_height = RAW_HEIGHT;
	block.block_row_element = ROW_ELEMENT;
	block.block_column_element = COLUMN_ELEMENT;
	strcpy(block.rawMap, RAWMAP_PATH);
	strcpy(block.block_data, BLOCK_DATA_PATH);
	strcpy(block.vq_data, VQ_DATA_PATH);
	strcpy(block.codebook_data, CODEBOOK_PATH);
		
	printf("main\n");
	vq(block);

	return 0;
}
