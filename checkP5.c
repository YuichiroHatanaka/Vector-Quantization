#include<stdio.h>

int checkP5(char filename[]){
	FILE *fp;
	short P5;

//Check the file is written in P5 firmat.
        if ((fp = fopen(filename, "rb")) == NULL){
                printf("ERROR: cannot open file\n");
		return 1;
	}else
		printf("%s is exist.\n", filename);

	fread(&P5, sizeof(short), 1, fp);
	printf("the numbers read is %x.\n", P5);
                
	if (P5 != 0x3550){
		printf("ERROR: %s is not written in P5 format.\n", filename);
		fclose(fp);
		return 1;
	}else
	printf("%s is written in P5 format.\n", filename);
	fclose(fp);
//	printf("end the program.\n");
	
	return 0;
}

int main(void){
	char filename[] = "sample.pgm";
	checkP5(filename);
	return 0;
}
