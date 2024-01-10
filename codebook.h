#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int codebook(char filename[], char cbfilename[], char vqfilename[], char row, char column, int rowNum, int columnNum){

	int n = rowNum * columnNum;

	FILE *fp;
	FILE *cbfp;
	FILE *vqfp;
	char cb[row*column];
	char new[row*column];

	typedef struct {
    		int number;
    		char vec[row*column];
	} vq;
	
//Check the file can be opened.
        if ((fp = fopen(filename, "rb")) == NULL){
                printf("ERROR: cannot open file\n");
                return 1;
        }else
		printf("%s is exist.\n", filename);

	if ((cbfp = fopen(cbfilename, "wb")) == NULL){
                printf("ERROR: cannot open file\n");
                return 1;
        }else
                printf("%s is exist.\n", cbfilename);

	if ((vqfp = fopen(vqfilename, "wb")) == NULL){
                printf("ERROR: cannot open file\n");
                return 1;
        }else
                printf("%s is exist.\n", vqfilename);


//ベクトルを配列に入力
	int count;
	int count2 = 1;
	fseek(fp, 13, SEEK_SET);
	vq *codebook = (vq*)calloc(n, sizeof(vq));

//１番目のベクトルをコードブックに登録
	fread(&codebook[0].vec, sizeof(char), row*column, fp);
        codebook[0].number = 1;
        printf("1つ目のベクトルを取得\n");
	fwrite(&codebook[0].vec, sizeof(char), row*column, cbfp);
	fwrite(&codebook[0].number, sizeof(char), 1, vqfp);

//コードブックに登録されているベクトルと比較
        for (int i = 0; i < n - 1; i++){
		count = count2;
//		printf("%dつ目: ", i+2);
		fread(&new, sizeof(char), row*column, fp);
//		fwrite(&new, sizeof(char), row*column, cbfp);
		for(int j = 0; j < count; j++){
//			printf("%d ", j);
			strcpy(cb, codebook[j].vec);
//			fwrite(cb, sizeof(char), row*column, cbfp);
//			printf("合否%d ",memcmp(new, cb, sizeof(row*column)));
//同じベクトルがあった場合
			if(memcmp(new, cb, sizeof(row*column)) == 0){
//				printf("%d番目のベクトルと同じ\n", j + 1);
				fwrite(&codebook[j].number, sizeof(char), 1, vqfp);
//				fwrite(&new, sizeof(char), row*column, cbfp);
				break;
			}
//同じベクトルがなかった場合
			if(j + 1  == count){
				printf("%d番目のベクトルを取得\n", count + 1);
                		codebook[count].number = count + 1;
				strcpy(codebook[count].vec, new);
				fwrite(&codebook[count].vec, sizeof(char), row*column, cbfp);
				fwrite(&codebook[count].number, sizeof(char), 1, vqfp);
				count2++;
			}
		}

	}

    // 結果の出力
   /* for (int i = 0; i < count; i++) {
        printf("student #%d: %s\n", codebook[i].number, codebook[i].vec);
    }*/

    // メモリの解放
    free(codebook);
    fclose(fp);
    fclose(cbfp);
    fclose(vqfp);
	
	return 0;
}
