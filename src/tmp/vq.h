#include<stdio.h>
#include<string.h>
#include"representativeVector.h"

int vectorQuantizer(char rawMap[], char codebook[], char vq[], char block[], int width, int height, int rowElem, int colElem, int start){
	//ファイルポインタ
	FILE *rawMap_fp, *codebook_fp, *vq_fp, *block_fp;
	//地図をブロック化したときのベクトルの縦と横それぞれの数
	int rowVec = (height + rowElem - 1) / rowElem;
	int colVec = (width + colElem - 1) / colElem;
	//ベクトルの要素数
	int vecElem = rowElem * colElem;
	//地図から得たデータの一部(１行分の要素)をファイルに受け渡すための配列
	unsigned char data[colElem];
	//地図から切り取ったベクトルを格納する配列
	unsigned char rawVec[vecElem];
	//入力された代表ベクトルの数と、処理をした結果の代表ベクトルの数
	unsigned short brepVecNum = 1;
	unsigned short repVecNum = 0;
	//ブロック化されたマップの同じ行のベクトル全体が持つ要素数
	int samerowElem = width * rowElem;
	//同じ行のベクトルのうち一番右のベクトルで使用
	int RElem = width % colElem;
	if(RElem == 0)
		RElem = colElem;

	int addElem = colElem - RElem;
	unsigned char RData[RElem];
	unsigned char addData[addElem];
	for(int l = 0; l < addElem ; l++)
		addData[l] = 0xCD;
	//一番下のベクトル群で使用
	int RRow = height % rowElem;
	if(RRow == 0)
		RRow = rowElem;

	int addRow = rowElem - RRow;
	int RRowElem = width * RRow;
	unsigned char addRowData[colElem];
	for(int i = 0; i < colElem; i++)
		addRowData[i] = 0xCD;



	//ファイルを開く。不具合があった場合エラーを返す
	if ((rawMap_fp = fopen(rawMap, "rb")) == NULL){
        	printf("ERROR: cannot open r file\n");
        	return 1;
        }
        if ((codebook_fp = fopen(codebook, "w+b")) == NULL){
                printf("ERROR: cannot open codebook file\n");
                return 1;
        }
        if ((vq_fp = fopen(vq, "wb")) == NULL){
                printf("ERROR: cannot open vq file\n");
                return 1;
        }
        if ((block_fp = fopen(block, "w+b")) == NULL){
                printf("ERROR: cannot open vq file\n");
                return 1;
        }
	
	//予め灰色(CD)一色(データなし)の代表ベクトルを作成
	unsigned char vecData[vecElem];
	unsigned char vq0[2] = {0, 0};
	for(int d = 0; d < vecElem; d++)
		vecData[d] = 0xCD;
	fwrite(vecData, sizeof(vecData), 1, codebook_fp);

//一番下のベクトル群を除いたベクトル
	for(int i = 0; i < rowVec - 1; i++){
		//右端のベクトルを除いた同じ行のベクトル
		for(int j = 0; j < colVec - 1; j++){
			for(int k = 0; k < rowElem; k++){
				fseek(rawMap_fp, start + samerowElem * i + colElem * j + width * k, SEEK_SET);
				fread(&data, sizeof(char), colElem, rawMap_fp);
				fwrite(&data, sizeof(char), colElem, block_fp);
			}
			//代表ベクトルと比較
			fseek(block_fp, -vecElem, SEEK_CUR);
			fread(&rawVec, sizeof(char), vecElem, block_fp);
			representativeVector(codebook_fp, vq_fp, rawVec, vecElem, brepVecNum, &repVecNum);
			brepVecNum = repVecNum;
		}
		//右端のベクトル
		for(int k = 0; k < rowElem; k++){
			fseek(rawMap_fp, start + samerowElem * i + colElem * (colVec - 1) + width * k, SEEK_SET);
			fread(&RData, sizeof(char), RElem, rawMap_fp);
			fwrite(RData, sizeof(char), RElem, block_fp);
			fwrite(addData, sizeof(char), addElem, block_fp);
		}
		//代表ベクトルと比較
		fseek(block_fp, -vecElem, SEEK_CUR);
		fread(&rawVec, sizeof(char), vecElem, block_fp);
		representativeVector(codebook_fp, vq_fp, rawVec, vecElem, brepVecNum, &repVecNum);
		brepVecNum = repVecNum;
	}

//一番下のベクトル群に含まれるベクトル
	//右端のベクトルを除いた同じ行のベクトル
	for(int j = 0; j < colVec - 1; j++){
		for(int k = 0; k < RRow; k++){
			fseek(rawMap_fp, start + samerowElem * (rowVec - 1) + colElem * j + width * k, SEEK_SET);
			fread(&data, sizeof(char), colElem, rawMap_fp);
			fwrite(&data, sizeof(char), colElem, block_fp);
		}
		for(int k = 0; k < addRow; k++)
			fwrite(&addRowData, sizeof(char), colElem, block_fp);
		//代表ベクトルと比較
		fseek(block_fp, -vecElem, SEEK_CUR);
		fread(&rawVec, sizeof(char), vecElem, block_fp);
		representativeVector(codebook_fp, vq_fp, rawVec, vecElem, brepVecNum, &repVecNum);
		brepVecNum = repVecNum;

	}
	//右端のベクトル
	for(int k = 0; k < RRow; k++){
		fseek(rawMap_fp, start + samerowElem * (rowVec - 1) + colElem * (colVec - 1) + width * k, SEEK_SET);
		fread(&RData, sizeof(char), RElem, rawMap_fp);
		fwrite(&RData, sizeof(char), RElem, block_fp);
		fwrite(&addData, sizeof(char), addElem, block_fp);
	}
	for(int k = 0; k < addRow; k++)
		fwrite(&addRowData, sizeof(char), colElem, block_fp);
	//代表ベクトルと比較
	fseek(block_fp, -vecElem, SEEK_CUR);
	fread(&rawVec, sizeof(char), vecElem, block_fp);
	representativeVector(codebook_fp, vq_fp, rawVec, vecElem, brepVecNum, &repVecNum);
	brepVecNum = repVecNum;

//ファイルを閉じる
        fclose(rawMap_fp);
        fclose(codebook_fp);
        fclose(vq_fp);
        fclose(block_fp);

	return 0;
}
