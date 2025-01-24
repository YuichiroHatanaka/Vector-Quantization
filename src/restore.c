// SPDX-FileCopyrightText: 2024 Yuichiro Hatanaka
// SPDX-License-Identifier: BSD-3-Clause

#include"vq/restore.h"

int restore(char codebook[], char vq[], char restore[], int width, int height, int rowElem, int colElem, int rewidth, int reheight){
	//ファイルポインタ
	FILE *codebook_fp, *vq_fp, *restore_fp;
	//ベクトル量子化されたデータ
	int vqData;
	//コードブックのデータ
	int vecElem = rowElem * colElem;
	unsigned char cbData[vecElem];
	

	//地図をブロック化したときのベクトルの縦と横それぞれの数
        int rowVec = (height + rowElem - 1) / rowElem;
        int colVec = (width + colElem - 1) / colElem;
        printf("地図は縦%d個、横%d個に分割されます\n", rowVec, colVec);

	//ファイルオープン
        if ((codebook_fp = fopen(codebook, "rb")) == NULL){
                printf("ERROR: cannot open codebook file\n");
                return 1;
        }
        if ((vq_fp = fopen(vq, "rb")) == NULL){
                printf("ERROR: cannot open vq file\n");
                return 1;
        }
        if ((restore_fp = fopen(restore, "w+b")) == NULL){
                printf("ERROR: cannot open vq file\n");
                return 1;
        }
	char data1[12], data2[12];
	sprintf(data1, "%d", rewidth);
	sprintf(data2, "%d", reheight);
    fwrite("P5\n", sizeof(char), 3, restore_fp);
    fwrite(data1, sizeof(char), strlen(data1), restore_fp);
    fwrite(" ", sizeof(char), 1, restore_fp);
    fwrite(data2, sizeof(char), strlen(data2), restore_fp);
    fwrite("\n255\n", sizeof(char), 5, restore_fp);

    int headerlength = 9 + strlen(data1) + strlen(data2);

	for(int i = 0; i < rowVec; i++){
		for(int j = 0; j < colVec; j++){
			fread(&vqData, sizeof(int), 1, vq_fp);
			fseek(codebook_fp, vecElem * vqData, SEEK_SET);
			fread(&cbData, sizeof(char), vecElem, codebook_fp);
			for(int k = 0; k < rowElem; k++){
				fseek(restore_fp, headerlength + vecElem * colVec * i + colElem * j + rewidth * k, SEEK_SET);
				for(int l = 0; l < colElem; l++)
					fwrite(&cbData[colElem * k + l], sizeof(char), 1, restore_fp);
			}
		}
	}

	//ファイルを閉じる
        fclose(codebook_fp);
        fclose(vq_fp);
        fclose(restore_fp);

	return 0;
}
