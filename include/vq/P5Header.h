#ifndef __P5HEADER_H__
#define __P5HEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int width;
    int height;
    int start;
} Header;

/*ヘッダを確認する*/
int P5Header(char rawMap[], Header *data);

#endif
