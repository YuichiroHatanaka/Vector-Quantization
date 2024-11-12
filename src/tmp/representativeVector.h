#include<stdio.h>
#include<string.h>

int representativeVector(FILE *codebook_fp, FILE *vq_fp, char rawVec[], int vecElements, unsigned short brepVecNum, unsigned short *repVecNum){
	unsigned char repVec[vecElements];

	for(unsigned short i = 0; i < brepVecNum ; i++){
		int same = 0;
		fseek(codebook_fp, vecElements * i, SEEK_SET);
		fread(&repVec, sizeof(char), vecElements, codebook_fp);
		if(memcmp(rawVec, repVec, vecElements) == 0){
		//	printf("rep%x is same data.   \n", i);
			printf("%d\n", i);
			fwrite(&i, sizeof(short), 1, vq_fp);
			*repVecNum = brepVecNum;
			break;
		}

		if(i + 1 == brepVecNum){
			//printf("new repVec");
			*repVecNum = brepVecNum + 1;
			printf("%d\n", brepVecNum);
			fseek(codebook_fp, vecElements * brepVecNum, SEEK_SET);
			fwrite(rawVec, sizeof(char), vecElements, codebook_fp);
			fwrite(&brepVecNum, sizeof(short), 1, vq_fp);
		}
	}
	//printf("repvecnum is %x\n", *repVecNum);
	return 0;
}
