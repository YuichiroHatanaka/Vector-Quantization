#include<stdio.h>
#include<stdlib.h>

int checkwh(char filename[], int *wdata, int *hdata){
	FILE *fp;
	char wh;
	int width = 0;
	int height = 0;
	int wcount = 0;
	int hcount = 0;

//Check the file can be opened.
        if ((fp = fopen(filename, "rb")) == NULL){
                printf("ERROR: cannot open file\n");
		return 1;
	}else
		printf("%s is exist.\n", filename);

//幅と高さが格納されている場所に移動
	fseek(fp, 3, SEEK_SET);

//数の長さをカウント
	for(wcount = 0;; wcount++) {
		fread(&wh, sizeof(char), 1, fp);
		printf("the numbers read is %x.\n", wh);
		if (wh == 0x20)
			break;
	}
	
	printf("%d\n", wcount);
//
	char *w =  calloc(wcount, sizeof(char));
	if (w == NULL)
		puts("failed to allocate memory.");

	fseek(fp, 3, SEEK_SET);
	fread(w, sizeof(char), wcount, fp);
	for(int i = 0; i < wcount; i++) 
		printf("w[%d] = %x.\n", i, w[i]);


//widthに幅の数値を代入
	for(int i = 0; i < wcount; i++) {
		width = width * 10 + (w[i]  & 0x0F);
		printf("%d\n", width);
		}
	*wdata = width;
	free(w);


//height
//幅と高さが格納されている場所に移動
        fseek(fp, 3 + wcount + 1, SEEK_SET);

//数の長さをカウント
        for(hcount = 0;; hcount++) {
                fread(&wh, sizeof(char), 1, fp);
                printf("the numbers read is %x.\n", wh);
                if (wh == 0x0A)
                        break;
        }

        printf("%d\n", hcount);

        char *h =  calloc(hcount, sizeof(char));
        if (h == NULL)
                puts("failed to allocate memory.");

        fseek(fp, 3 + wcount + 1, SEEK_SET);
        fread(h, sizeof(char), hcount, fp);
        for(int i = 0; i < hcount; i++)
                printf("h[%d] = %x.\n", i, h[i]);

//heightに幅の数値を代入
        for(int i = 0; i < hcount; i++) {
                height = height * 10 + (h[i] & 0x0F);
                printf("%d\n", height);
                }
	*hdata = height;
	free(h);

	fclose(fp);
	printf("end the program.\n");
	return 0;
}

int main(void){
	int width, height;
	char filename[] = "sample.pgm";
	checkwh(filename, &width, &height);
	printf("width: %d\nheight: %d\n", width, height);
	return 0;
}
