#include<stdio.h>
#include<string.h>

#define RAWMAP_PATH "/home/yuichirohatanaka/VQ4/map/sim.pgm"
#define BLOCK_DATA_PATH "/home/yuichirohatanaka/VQ4/sim/block.bin"
#define CODEBOOK_PATH "/home/yuichirohatanaka/VQ4/sim/codebook.bin"
#define VQ_DATA_PATH "/home/yuichirohatanaka/VQ4/sim/vq.bin"
#define RAW_WIDTH 100
#define RAW_HEIGHT 100
#define ROW_ELEMENT 2
#define COLUMN_ELEMENT 2
#define MAX_PATH_LENGTH 255

//構造体Blocker型を定義
typedef struct {
	char rawMap[MAX_PATH_LENGTH];		//圧縮前の地図のパス
	char block_data[MAX_PATH_LENGTH];	//ブロック化したデータの格納場所のパス
	char codebook_data[MAX_PATH_LENGTH];//コードブックのパス
	char vq_data[MAX_PATH_LENGTH];		//量子化データへのパス
	char rawMap_width;					//圧縮前の地図の幅
	char rawMap_height;					//圧縮前の地図の高さ
	char row_element;					//ブロック化したときの行の要素
	char column_element;				//ブロック化したときの列の要素
} Blocker;


int blocker(Blocker data){
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
	int same_row_element = 
	

	//ファイルが開くか確認
	if ((rawMap_fp = fopen(data.rawMap, "rb")) == NULL){
 		perror("ERROR: cannot open r file\n");
		fclose(rawMap_fp);
      	return 1;
   	}
 	if ((block_fp = fopen(data.block_data, "w+b")) == NULL){
  		perror("ERROR: cannot open codebook file\n");
		fclose(rawMap_fp);
		fclose(block_fp);
   		return 1;
	}
	if ((vq_fp = fopen(vq, "wb")) == NULL){
 		printf("ERROR: cannot open vq file\n");
		fclose(rawMap_fp);
		fclose(block_fp);
		fclose(vq_fp);
      	return 1;
   	}
   	if ((codebook_fp = fopen(codebook, "w+b")) == NULL){
    	printf("ERROR: cannot open vq file\n");
		fclose(rawMap_fp);
		fclose(block_fp);
		fclose(vq_fp);
		fclose(codebook_fp);
     	return 1;
 	}

	
	for(int i = 0;, i < row_vector - 1; i++){
		//エリア1のデータを取得
		for(int j = 0; j < column_vector - 1; j++){
			//	データ取得し、ファイルに格納
			for(int k = 0; k < row_element; k++){
				fseek(rawMap_fp, start + samerowElem * i + columnElem * j + width * k, SEEK_SET);
				fread(&pixel_data, sizeof(char), colElem, rawMap_fp);
                fwrite(&pixel_data, sizeof(char), colElem, block_fp);
			}
			//	取得したベクトルと代表ベクトルを比較
			//fseek(block_fp, -vector_element, SEEK_CUR);
            //fread(&pixel_data, sizeof(char), vector_element, block_fp);
            //representativeVector(codebook_fp, vq_fp, rawVec, vecElem, brepVecNum, &repVecNum);
            //brepVecNum = repVecNum;
        }
		//エリア2のデータを取得
			for(int k = 0; k < rowElem; k++){
            	fseek(rawMap_fp, start + samerowElem * i + colElem * (colVec - 1) + width * k, SEEK_SET);
            	fread(&RData, sizeof(char), RElem, rawMap_fp);
            	fwrite(RData, sizeof(char), RElem, block_fp);
            	fwrite(addData, sizeof(char), addElem, block_fp);
        }

		}
	}
	
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
	block.rawMap_width = RAW_WIDTH;
	block.rawMap_height = RAW_HEIGHT;
	block.row_element = ROW_ELEMENT;
	block.column_element = COLUMN_ELEMENT;
	strcpy(block.rawMap, RAWMAP_PATH);
	strcpy(block.block_data, RAWMAP_PATH);
		
	printf("main\n");
	blocker(block);

	return 0;
}
