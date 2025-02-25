// SPDX-FileCopyrightText: 2025 Yuichiro Hatanaka
// SPDX-License-Identifier: BSD-3-Clause

#include "vq/P5Header.h"

#define MAX_LINE_LENGTH 256

int P5Header(char rawMap[], Header *data) {
	FILE *rawMap_fp;								//圧縮前の地図のファイルポイント
	char map_data[MAX_LINE_LENGTH];					//データを１行ずつ格納
	char correct_format[MAX_LINE_LENGTH] = "P5\n";	//P5形式であることを確認
	char pixel_value[] = "255\n";					//画素値の範囲を確認
	int comment_length = 0;							//コメントの長さ（初期値は0）

	//マップファイルを開く
	rawMap_fp = fopen(rawMap, "r");

	//ファイルが開かない場合はエラーを出力
    if (rawMap_fp == NULL) {
		printf("## %sを開くことができません\n", rawMap);
    	return 1;
    }

	//PGMファイルがP5形式で記述されているかを確認
	//1行目の文字列を取得
	fgets(map_data, MAX_LINE_LENGTH, rawMap_fp);
	
	//P5形式でないならエラーを出力
	if(strcmp(map_data, correct_format) != 0){
		perror("# 入力ファイルの形式が違違います\n");
		return 1;
	}

	//圧縮前の地図の幅と高さのデータを取得
	for(;;){
	// データを取得
		fgets(map_data, MAX_LINE_LENGTH, rawMap_fp);

	//コメントが存在する場合は無視
		if(map_data[0] == '#'){
			comment_length += strlen(map_data);

	//幅と高さのデータを取得
		}else{
			sscanf(map_data, "%d %d", &data->width, &data->height);
			break;
		}
	}

	// 画素値の範囲を取得
	fgets(map_data, MAX_LINE_LENGTH, rawMap_fp);
	
	// 画素値が0~255出ない場合はエラーを出力
	if(strcmp(map_data, pixel_value) != 0){
		perror("画素値の範囲が違います\n");
		fclose(rawMap_fp);
		return 1;
	}
	
	// 画像データの先頭位置を取得
    data->start = ftell(rawMap_fp);

	//開いたファイルを閉じる
	fclose(rawMap_fp);
	
	return 0;
}
