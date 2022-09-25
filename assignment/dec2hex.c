#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef unsigned char* pointer;
bool is64bit()
{
	if(sizeof(long) == 8)
		return true;
	return false;
}

bool isBigEndian(){
	unsigned int value = 0x1;
	char *r = (char *) &value;

	if (*r ==1)
		return true;
	else
		return false;
}

pointer convert_to_hex(unsigned int dec,unsigned int size){
	unsigned int remain = dec;
	int count =0;
	unsigned int tmp = 0;
	unsigned char slice[8] = " ";
	unsigned char c;
	static unsigned char hex[24] = " ";
	while(remain>0){
		*slice = (unsigned char)remain;
		for(int i = 0; i<2;i++){
			tmp = ((unsigned int)*slice) %16;
			switch (tmp){
				case 10 : c = 'A'; break;			
				case 11 : c = 'B'; break;			
				case 12 : c = 'C'; break;			
				case 13 : c = 'D'; break;			
				case 14 : c = 'E'; break;			
				case 15 : c = 'F'; break;			
				default : c = tmp + '0';
				}
			*slice = *slice >>size;
			hex[count] = c;
			count++;
		}
		remain = remain >> size*2;
	}
	hex[count] = '\0';
	return hex;	
}
void le_show_bytes(unsigned int dec, int size)
{
	printf("%8s\n",convert_to_hex(dec,size));
	return;
}

void be_show_bytes(unsigned int dec, int size){
	pointer tmp = " ";
	int len = 0;
	unsigned char result_hex[24];
	tmp = convert_to_hex(dec,size);
	while(tmp[len]!=0) len++;
	result_hex[len] = '\0';
	for (int i = 0;i<len;i++){
			result_hex[(len-1)-i] = tmp[i];
			}
	printf("%8s\n",result_hex);
	return;
}


int main(int argc, char* argv[])
{
	if(argc < 2){
		printf("Usage: ./a.out number\n");
		exit(0);
	}
	unsigned int a = atoi(argv[1]);

	printf("ARCH=%d\n", is64bit()? 64 : 32);
	printf("ORDERING=%s\n", isBigEndian()? "BIG_ENDIAN": "LITTLE_ENDIAN");

	printf("MYANS: DEC=%d HEX=", a);
	isBigEndian()? 
		be_show_bytes(a, sizeof(unsigned int)): le_show_bytes(a, sizeof(unsigned int));

	printf("CHECK: DEC=%d HEX=%.8X\n", a, a);
	return 0;
}
