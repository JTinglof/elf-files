#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

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
	printf("Assignment #1-3, Joseph Tinglof, jbtinglof@gmail.com\n");
	if(argc < 2){
		fprintf(stderr,"Incorrect number of arguments\n");
		return 1;
 }  
 
 char * buffer;
 long int shStart, tableOff, tableSize;
 short shSize, shNum, shIndex; 
 unsigned int crc32;
 
 FILE *fptr = fopen(argv[1],"rb");
 //start of the section table
 fseek(fptr, 0x28, SEEK_SET);
 fread(&shStart, sizeof(shStart), 1, fptr);
 rewind(fptr);
 
 fseek(fptr, 0x3A, SEEK_SET);
 fread(&shSize, sizeof(shSize), 1, fptr);
 fread(&shNum, sizeof(shSize), 1, fptr);
 fread(&shIndex, sizeof(shIndex), 1, fptr);
 rewind(fptr);
 
 //now at the header for the string table section
 fseek(fptr, shStart + (shIndex*shSize), SEEK_SET);
 //offset to the string table
 fseek(fptr, 0x18, SEEK_SET);
 fread(&tableOff, sizeof(tableOff), 1, fptr);
 fread(&tableSize, sizeof(tableSize), 1, fptr);
 
 fseek(fptr, tableOff, SEEK_SET);
 
 
 //temp
 rewind(fptr);
 long int finalSection = shStart;
 buffer = (char *) malloc(shSize);
 fseek(fptr, finalSection, SEEK_SET);
 fread(buffer, shSize, 1, fptr);

 crc32 = GetCheckSum(buffer, shSize);
	printf("%x\n",crc32);
	fclose(fptr);
	return 0;
}
