#include "P5Header.h"

#define MAX_LINE_LENGTH 256

int P5Header(char rawMap[], Header *data) {
	FILE *rawMap_fp;								//圧縮前の地図のファイルポイント
	char map_data[MAX_LINE_LENGTH];					//データを１行ずつ格納
	char correct_format[MAX_LINE_LENGTH] = "P5\n";	//P5形式であることを確認
	char pixel_value[] = "255\n";					//画素値の範囲を確認

	//マップファイルが開くかを確認
	rawMap_fp = fopen(rawMap, "r");
    if (rawMap_fp == NULL) {
		perror("圧縮前のマップを開くことができません\n");
    	return 1;
    }

	//PGMファイルがP5形式で記述されているかを確認
	fgets(map_data, MAX_LINE_LENGTH, rawMap_fp);
	if(strcmp(map_data, correct_format) == 0){
		printf("圧縮前の地図はP5形式です\n");
		data->start = strlen(map_data);
	}else{
		perror("not P5");
		fclose(rawMap_fp);
		return 1;
	}

	//圧縮前の地図の幅と高さのデータを取得
	for(;;){
		fgets(map_data, MAX_LINE_LENGTH, rawMap_fp);
		//コメントが存在する場合は無視
		if(map_data[0] == '#'){
			data->start += strlen(map_data);
		//幅と高さのデータを取得
		}else{
			sscanf(map_data, "%d %d", &data->width, &data->height);
			data->start += strlen(map_data);
			break;
		}
	}

	//画素値の範囲を取得
	fgets(map_data, MAX_LINE_LENGTH, rawMap_fp);
	if(strcmp(map_data, pixel_value) == 0){
		printf("画素値の範囲は0~255\n");
		data->start += strlen(map_data);
	}else{
		perror("画素値の範囲が違います\n");
		fclose(rawMap_fp);
		return 1;
	}

	//開いたファイルを閉じる
	fclose(rawMap_fp);
	
	//入出力の確認
	printf("\nP5Header関数\n");
	printf("圧縮前の地図\nパス: %s\n", rawMap);
	printf("幅　: %d\n高さ: %d\n", data->width, data->height);
	printf("ヘッダの長さ: %d\n", data->start);
	
	return 0;
}
