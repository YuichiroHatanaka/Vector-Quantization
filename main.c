#include<stdio.h>
#include"checkP5.h"
#include"checkwh.h"
#include"numVec.h"
#include"codebook.h"

int main(void) {
	char filename[] = "Data/map0429.pgm";		//ベクトル量子化したいファイルを選択
	char cbfilename[] = "Data/sample/codebook.dat";	//量子化するときの代表ベクトルを格納するコードブック
	char vqfilename[] = "Data/sample/vq.dat";		//ベクトル量子化されたファイルのデータ

	char tmpfilename[] = "Data/tmp.dat";

	char row = 10;				//ベクトル化するとき取得する行の要素(未対応なため１で固定)
	char column = 10;			//ベクトル化をするとき取得する列の要素
	int width, height;			
	int rowNum, columnNum;
	int start = 13;

	checkP5(filename);

	checkwh(filename, &width, &height);
	printf("width: %d\nheight: %d\n\n", width, height);

	printf("VectorData\nrow: %d   column: %d\n\n", row, column);

	numVec(width, height, row, column, &rowNum, &columnNum);
	printf("number of rows: %d\nnumber of columns: %d\n\n", rowNum, columnNum);
	codebook(row, column, rowNum, columnNum, width, start, filename, cbfilename, tmpfilename, vqfilename);
	return 0;
}
