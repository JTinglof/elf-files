#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <inttypes.h>

unsigned int GetCheckSum(unsigned char *message, int file_length) {
   int i, j;
   unsigned int byte, crc, mask;

   i = 0;
   crc = 0xFFFFFFFF;
   while (i < file_length) {
      byte = message[i];            // Get next byte.
      crc = crc ^ byte;
      for (j = 7; j >= 0; j--) {    // Do eight times.
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
      }
      i = i + 1;
   }
   return ~crc;
}

int main(int argc, char *argv[]){	
	printf("Assignment #1-1, Joseph Tinglof, jbtinglof@gmail.com\n");
	if(argc < 2){
		fprintf(stderr,"Incorrect number of arguments\n");
		return 1;
 }  
 
	unsigned char *buffer;
	int file_len, read_size;
	
	FILE *fptr = fopen(argv[1], "rb");
	fseek(fptr, 0, SEEK_END);
	file_len = ftell(fptr);
	rewind(fptr);

	buffer = (char *) malloc(file_len);
	read_size = fread(buffer, sizeof(char), file_len, fptr);
	fclose(fptr);
	
	unsigned int crc32 = GetCheckSum(buffer, file_len);
	printf("%x\n",crc32);
	return 0;
}
