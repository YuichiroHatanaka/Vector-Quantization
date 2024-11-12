#include "P5Header.h"

#define RAWMAP_PATH "/home/yuichirohatanaka/Vector-Quantization/map/sim.pgm"

int main() {
    Header header;
    char rawMap[] = RAWMAP_PATH;

    P5Header(rawMap, &header);

    //確認
    printf("\nmain文\n");
    printf("幅　: %d\n高さ: %d\n", header.width, header.height);
    printf("ヘッダの長さ: %d\n", header.start);

    return 0;
}
