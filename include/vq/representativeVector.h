#ifndef __REPRESENTATIVEVECTOR_H__
#define __REPRESENTATIVEVECTOR_H__

#include<stdio.h>
#include<string.h>

int representativeVector(FILE *block_fp, FILE *codebook_fp, FILE *vq_fp, unsigned char raw_vector_data[], int vector_element, unsigned short *representative_vector_number);

#endif
