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
