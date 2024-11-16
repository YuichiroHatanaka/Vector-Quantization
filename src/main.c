#include "vq/P5Header.h"
#include "vq/vq.h"
#include "vq/representativeVector.h"
#include "vq/deployment.h"

#define RAWMAP_PATH "map/sim.pgm"
#define BLOCK_DATA_PATH "sim/block.bin"
#define CODEBOOK_PATH "sim/codebook.bin"
#define VQ_DATA_PATH "sim/vq.bin"
#define ROW_ELEMENT 2
#define COLUMN_ELEMENT 2

int main(void) {
    //P5Header関数で使用する変数
	Header header;
    char rawMap[] = RAWMAP_PATH;
	//vectorQuantization関数で使用する変数
	VQ vq;
	vq.block_row_element = ROW_ELEMENT;
	vq.block_column_element = COLUMN_ELEMENT;
	strcpy(vq.rawMap, RAWMAP_PATH);
    strcpy(vq.block_data, BLOCK_DATA_PATH);
    strcpy(vq.vq_data, VQ_DATA_PATH);
    strcpy(vq.codebook_data, CODEBOOK_PATH);
    //deployment.h
    char re[] = "sim/restore.pgm";
    char reData[15] = {0x50, 0x35, 0x0A, 0x33, 0x38, 0x32, 0x20, 0x34, 0x34, 0x34, 0x0A, 0x32, 0x35, 0x35, 0x0A};
    int col = 382;
    char relength = sizeof(reData);


    P5Header(rawMap, &header);
	vq.header_length = header.start;
	vq.rawMap_width = header.width;
	vq.rawMap_height = header.height;
	vectorQuantization(vq);
	vqdep(vq.codebook_data, vq.vq_data, re, header.width, header.height, header.start, vq.block_row_element, vq.block_column_element, reData, col, relength);

    //確認
    printf("\nmain文\n");
    printf("幅　: %d\n高さ: %d\n", header.width, header.height);
    printf("ヘッダの長さ: %d\n", header.start);

    return 0;
}
