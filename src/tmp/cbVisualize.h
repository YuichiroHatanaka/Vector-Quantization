#include<stdio.h>

int cbVisualize(char cb[], char cbpgm[], char vecElem, char hdata[], int cbMax, int headerlength){
	FILE *cb_fp, *cbpgm_fp;
	unsigned char data[vecElem];

	//ファイルをオープンする
        if ((cb_fp = fopen(cb, "rb")) == NULL){
                printf("ERROR: cannot open r file\n");
                return 1;
        }
        if ((cbpgm_fp = fopen(cbpgm, "ab")) == NULL){
                printf("ERROR: cannot open recodebook file\n");
                return 1;
        }
	//引数として渡された配列はサイズを取得できないらしい headerlength
	//int start = 16;

	fwrite(hdata, sizeof(char), headerlength, cbpgm_fp);
	
	for(int i = 0; i < cbMax; i++){
		fseek(cb_fp, vecElem * i, SEEK_SET);
		fread(&data, sizeof(char), vecElem, cb_fp);
		fseek(cbpgm_fp, headerlength + vecElem * i, SEEK_SET);
		fwrite(&data, sizeof(char), vecElem, cbpgm_fp);
	}

	free(cb_fp);
	free(cbpgm_fp);

	return 0;
}
