#include <stdio.h>
#include <stdlib.h>

int main(){

	
    	FILE *fptr1, *fptr2;
    	char src_path[100], dst_path[100], c;
	
	//Prompt for name of file to open
	printf("Enter the filename to open for reading: \n");
	//places input into src_path
	scanf("%s", src_path);

	//Prompt for name of file to write to
	printf("Enter the filename to open for writing: \n");
	//places input into dsc_path
	scanf("%s",dst_path);
	//attempt to open file
	fptr1 = fopen(src_path, "r");
	//if there is no file of that name, write an error and exit program
	if (fptr1 == NULL)
    	{
        	printf("Cannot open file %s \n", src_path);
        	exit(0);
    	}
	//attempt to open file
	fptr2 = fopen(dst_path, "w");
	//if there is no file of that name, write an error and exit program
    	if (fptr2 == NULL)
    	{
        	printf("Cannot open file %s \n", dst_path);
        	exit(0);
    	}
	
	//Read contents from first file
	c = fgetc(fptr1);
	while(c != EOF)
	{
		fputc(c,fptr2);
		c=fgetc(fptr1);
	}

	printf("\nContents copied to %s", dst_path);
  
 	fclose(fptr1);
 	fclose(fptr2);
 	return 0;
}