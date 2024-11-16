#include"vq/representativeVector.h"

int representativeVector(FILE *block_fp, FILE *codebook_fp, FILE *vq_fp, unsigned char raw_vector_data[], int vector_element, unsigned short *representative_vector_number){
	unsigned char representative_vector_data[vector_element];
	unsigned short *temporary_data = representative_vector_number;

	fseek(block_fp, -vector_element, SEEK_CUR);
	fread(raw_vector_data, sizeof(char), vector_element, block_fp);


	for(unsigned short i = 0; i < *temporary_data ; i++){
		fseek(codebook_fp, vector_element * i, SEEK_SET);
		fread(&representative_vector_data, sizeof(char), vector_element, codebook_fp);
		if(memcmp(raw_vector_data, representative_vector_data, vector_element) == 0){
			printf("data is %d", i);
			fwrite(&i, sizeof(short), 1, vq_fp);
			break;
		}

		if(i + 1 == *temporary_data){
			printf("data is %d new!", *temporary_data);
			fseek(codebook_fp, vector_element * *temporary_data, SEEK_SET);
			fwrite(raw_vector_data, sizeof(char), vector_element, codebook_fp);
			fwrite(&*temporary_data, sizeof(short), 1, vq_fp);
			*representative_vector_number = *temporary_data + 1;
			break;
		}
	}

	printf("number is %d\n", *representative_vector_number);

	return 0;
}
