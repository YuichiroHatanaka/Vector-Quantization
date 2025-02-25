#include<stdio.h>

#define RAWMAP_PATH "../map/tsudanuma.pgm"
#define BLOCK_DATA_PATH "/block.bin"
#define CODEBOOK_PATH "/codebook.bin"
#define VQ_DATA_PATH "/vq.bin"
#define RESTORE_MAP_PATH "/restore.pgm
	
int a;


int vqpath(int a){
	printf("%d\n", a);
	a++;
	printf("%d\n", a);
	return 0;
}


int main(int argc, char *argv[]){
	a = 1;
	vqpath(a);
	//check data
	printf("%d\n", a);
	return 0;
}
