# Checksumming Elf Files

Three programs that will generate a 32 bit checksum based on the content of an Executable and Linkable Format (ELF) file.

## **Files Included:**

* this README
* prog1_1.c 
* prog1_2.c 
* prog1_3.c

## **Usage**

Compile with gcc and then pass in command line arguments in the following order.

./prog1_1 file_name

./prog1_2 file_name

./prog1_3 file_name section_name

Where file_name is a Elf binary executable and section_name is the name of a section header 
inside the target file. 

## **Design Choices**

Part 1 was straightforward, read the file passed in from the command line as binary, seek to the end to find 
the length, place the file into a buffer and then pass both through the crc32 
method. Part 2 was only slightly more complicated due to the fact that in order 
to find the size of the program header you needed to find two values, the number 
of entries in the program header table and the size of each. Thankful both are always
in the same spot in the file header. After these are aquired it's simple math to find the 
size, then you seek to the start of the program header and the rest is the same concept as
Part 2. Part 3 was tricky. First, three values are needed from the file header. The number and size of entries
as well as the index for the entry that points to the string table. After these are aquired you 
seek to the start of the string table header by multiplying the index by the entry sizes and add that to 
the start of the section headers. Once at the correct header you can find inside the offset to 
the string table that contains all the names of the sections. Once there you parce through the 
strings and finally make use of the second command line argument to compare to the names.
When a match is found you save the index and continue through the rest of the strings. After that 
all sections with a matching name are placed in buffers and sent through the crc method one at a time.

## **Common Bugs**

No bugs have been encountered using parts 1 & 2. 

## **To Be Fixed**

Part 3 will only checksum the first section header regardless of what is the second argument. 
