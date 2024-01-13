#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int codebook(char row, char column, int rowNum, int columnNum, int width, int start, char filename[], char cbfilename[], char tmpfilename[], char vqfilename[]){
//ファイル操作に使用
	FILE *fp;
        FILE *cbfp;
        FILE *tmpfp;
        FILE *vqfp;

//ベクトルの比較に使用
	typedef struct {
                int number;
                char vec[row*column];
        } vq;


	
	if ((fp = fopen(filename, "rb")) == NULL){
                printf("ERROR: cannot open file\n");
                return 1;
        }
        if ((cbfp = fopen(cbfilename, "w+b")) == NULL){
                printf("ERROR: cannot open file\n");
                return 1;
        }
        if ((tmpfp = fopen(tmpfilename, "w+b")) == NULL){
                printf("ERROR: cannot open file\n");
                return 1;
        }
       if ((vqfp = fopen(vqfilename, "wb")) == NULL){
                printf("ERROR: cannot open file\n");
                return 1;
        }


	char new[column];
        int goRow = width * row; 
        
        int count;
        int count2 = 1;

	vq *codebook = (vq*)calloc(rowNum * columnNum, sizeof(vq));
        
        for(int i = 0; i < rowNum; i++){
        	for(int j = 0; j < columnNum; j++){
        		int matrixStart = start + goRow * i + column * j;
        		char cb[row*column];
        		char vcb[row*column];
        		
        		for(int k = 0; k < row; k++){
				int readStart = matrixStart + width * k;
//スタート地点から行列データを読み取り、追記
				fseek(fp, readStart, SEEK_SET);
				fread(&new, sizeof(char), column, fp);
				fwrite(&new, sizeof(char), column, tmpfp);		
			}	
			fseek(tmpfp, 0, SEEK_SET);
			fread(&cb, sizeof(char), column*row, tmpfp);
//1つ目のベクトル
			if (i == 0 && j == 0){
				fseek(tmpfp, 0, SEEK_SET);
				fread(&cb, sizeof(char), row*column, tmpfp);
				codebook[0].number = 1;
				fwrite(&cb, sizeof(char), row*column, cbfp);
        		}
        		
        		count = count2;
        		
        		for(int l = 0; l < count; l++){
        			fseek(cbfp, row * column * l, SEEK_SET);
        			fread(&vcb, sizeof(char), row*column, cbfp);
				int end = 0;
				for(int m = 0; m < row*column; m++){
					if(cb[m] != vcb[m]){
						break;
					}
						
					if(m == row*column - 1){	
	                                	fwrite(&codebook[l].number, sizeof(char), 1, vqfp);
	                                	end = 1;
					}
				}
				if(end == 1)
					break;
				if(l == count - 1){
					codebook[count].number = count + 1;
					fwrite(&cb, sizeof(char), row*column, cbfp);
					fwrite(&codebook[count].number, sizeof(char), 1, vqfp);
					count2++;
				}						
			}
			fseek(tmpfp, 0, SEEK_SET);
		}
	
        }
	
	free(codebook);
	fclose(fp);
	fclose(cbfp);
	fclose(tmpfp);
	return 0;
}
