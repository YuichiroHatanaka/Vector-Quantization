//縦横の要素から
#include<stdio.h>

int numVec(int width, int height, char row, char column, int *rowNum, int *columnNum){
//	printf("numVec started.\n");

	*rowNum = height / row;
	*columnNum = width / column;
//	printf("numVec number: %d %d \n", *rowNum, *columnNum);

//	printf("width: %d\nheight: %d\n", width, height);
//	printf("row: %d\ncolumn: %d\n", row, column);

	

	return 0;
}

int main(void){
	printf("main started.\n");

	int width = 100000;
	int height = 200000;
	char row = 3;
	char column = 4;
	int rowNum, columnNum;
//	printf("width: %d\nheight: %d\n", width, height);
//	printf("row: %d\ncolumn: %d\n", row, column);

	numVec(width, height, row, column, &rowNum, &columnNum);
	printf("number of rows: %d\nnumber of columns: %d\n", rowNum, columnNum);

	return 0;
}
