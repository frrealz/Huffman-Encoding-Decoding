# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <getopt.h>
# include <string.h>

int main(int argc, char const *argv[])
{

	int get;
	while ((get = getopt(argc, (char *const *)argv, "i:o:")) != -1)
	{
		switch (get)
      	{
      		case 'i':
        		FILE *inputFile; 								
				inputFile = fopen("optarg", "r");
				if(inputFile == NULL)
				{
					printf("Fatal error: failure to open input\n");
					return 0;
				}
        	break;
      		case 'o':
        		FILE *outputFile; 								
				outputFile = fopen("optarg", "r");
				if(outputFile == NULL)
				{
					printf("Fatal error: failure to open output\n");
					return 0;
				}
        	break;
        	default: 
        		printf("DEFAULT CASE\n");
        	break;
        }
    } 

    
    

    
	return 0;
}