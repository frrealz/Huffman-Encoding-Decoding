# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <getopt.h>
# include <string.h>
#include  <fcntl.h>


int main(int argc, char **argv)
{
	uint32_t histogram[256] = {0};		//histogram
	for(int i = 0; i < 256; i++)		//initialize everything to 0
	{
		histogram[i] = 0;
	}
	
	char *inputFile = NULL;
	int c;
	while ((c = getopt(argc, argv, "i:o:v")) != -1)
	{
		switch(c)
		{
			case 'i':
			{
				inputFile = optarg;
				break;
			}
			case 'o':
			{
				break;
			}
			case 'v':
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
	printf("%s\n", inputFile);
	
	char buffer[1];
	FILE *file;
	file = fopen(inputFile, "r");
	if (file == NULL)
	{
        printf("Error Opening %s\n", inputFile);
		return 0;
    }
	fseek(file, SEEK_SET, 0);		//beginning of file
	
	while( fread(buffer, 1, 1, file) == 1 )
	{
		int index = (int) buffer[0];
		histogram[ index ]++;
	}
	histogram[0]++;
	histogram[255]++;
	
	
	for(int i = 0; i < 256; i++)
	{
		printf("%d: %u\n", i, histogram[i]);
	}		
	
	
	
	
	return 0;
}

