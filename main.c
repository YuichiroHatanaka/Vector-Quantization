#include<stdio.h>
#include"checkP5.h"
#include"checkwh.h"
#include"numVec.h"
#include"codebook.h"

int main(void) {
	char filename[] = "sample.pgm";		//ベクトル量子化したいファイルを選択
	char cbfilename[] = "codebook.dat";	//量子化するときの代表ベクトルを格納するコードブック
	char vqfilename[] = "vq.dat";		//ベクトル量子化されたファイルのデータ

	char row = 1;				//ベクトル化するとき取得する行の要素(未対応なため１で固定)
	char column = 2;			//ベクトル化をするとき取得する列の要素
	int width, height;			
	int rowNum, columnNum;

	checkP5(filename);

	checkwh(filename, &width, &height);
	printf("width: %d\nheight: %d\n\n", width, height);

	printf("VectorData\nrow: %d   column: %d\n\n", row, column);

	numVec(width, height, row, column, &rowNum, &columnNum);
	printf("number of rows: %d\nnumber of columns: %d\n\n", rowNum, columnNum);
	codebook(filename, cbfilename, vqfilename, row, column, rowNum, columnNum);
	return 0;
}
