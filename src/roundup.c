//#include"../include/vq/roundup.h"
#include"vq/roundup.h"

int roundup(int number, int multiple){
	int answer = 0;
	answer = (number / multiple + 1) * multiple;
	return answer;
}

/* //テスト
int main(int argc, char *argv[]){
	printf("%d\n", roundup(atoi(argv[1]), atoi(argv[2])));
	return 0;
}*/
