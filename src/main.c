#include "vq/P5Header.h"
#include "vq/vq.h"
#include "vq/representativeVector.h"
#include "vq/restore.h"

#define RAWMAP_PATH "map/tsudanuma.pgm"
#define BLOCK_DATA_PATH "/block.bin"
#define CODEBOOK_PATH "/codebook.bin"
#define VQ_DATA_PATH "/vq.bin"
#define RESTORE_MAP_PATH "/restore.pgm"
#define START 17

//argv[1]は、要素の幅と高さ
//argv[2]は、マップの名前(マップ名の後ろに/を忘れずに)

int main(int argc, char *argv[]) {
    //P5Header関数で使用する変数
    Header header;
    char rawMap[] = RAWMAP_PATH;
    //vectorQuantization関数で使用する変数
    VQ vq;
    vq.block_row_element = atoi(argv[1]);
    vq.block_column_element = atoi(argv[1]);
    strcpy(vq.rawMap, RAWMAP_PATH);
    //BLOCK_DATA_PATH
    strcpy(vq.block_data, argv[2]);
    strcat(vq.block_data, argv[1]);
    strcat(vq.block_data, BLOCK_DATA_PATH);
    //VQ_DATA_PATH
    //strcpy(vq.block_data, BLOCK_DATA_PATH);
    strcpy(vq.vq_data, argv[2]);
    strcat(vq.vq_data, argv[1]);
    strcat(vq.vq_data, VQ_DATA_PATH);
    //CODEBOOK_PATH
    strcpy(vq.codebook_data, argv[2]);
    strcat(vq.codebook_data, argv[1]);
    strcat(vq.codebook_data, CODEBOOK_PATH);
    //restore.h
    char re[100];
    strcpy(re, argv[2]);
    strcat(re, argv[1]);
    strcat(re, RESTORE_MAP_PATH);
    char reData[START] = {0x50, 0x35, 0x0A, 0x35, 0x38, 0x38, 0x38, 0x20, 0x34, 0x30, 0x30, 0x30, 0x0A, 0x32, 0x35, 0x35, 0x0A};
    int col = 5888;
    char relength = sizeof(reData);


    P5Header(rawMap, &header);
	vq.header_length = header.start;
	vq.rawMap_width = header.width;
	vq.rawMap_height = header.height;
	vectorQuantization(vq);
	restore(vq.codebook_data, vq.vq_data, re, header.width, header.height, START, vq.block_row_element, vq.block_column_element, reData, col, relength);

    //確認
    printf("\nmain文\n");
    printf("幅　: %d\n高さ: %d\n", header.width, header.height);
    printf("ヘッダの長さ: %d\n", header.start);

    return 0;
}
