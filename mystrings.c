#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char **argv )
{
	FILE *fp;
	int counter, file_size, mem_loop_counter;
	char read;
	char *buffer;
	char *temp;

	if(argc < 2)
	{
		printf("ERROR: Needs a file argument\n");
		return -1;
	}

	fp = fopen(argv[1], "rb");
	if (fp == NULL)
	{
		perror("ERROR: ");
		return -1;
	}

	fseek(fp, 0L, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	buffer = malloc(4);
	for(mem_loop_counter = 0; mem_loop_counter < strlen(buffer); mem_loop_counter++)
	{
		buffer[mem_loop_counter] = 0;
	}

	counter = 0;
	while(counter < file_size)
	{
		counter++;
		fread(&read, 1, 1, fp);
		if(read >= 32 && read <= 126)
		{
			if(buffer[strlen(buffer) - 1] != 0)
			{
				temp = realloc(buffer, strlen(buffer) * 2);
				if(!temp)
				{
					perror("ERROR");
					return -1;
				}
				else
				{
					buffer = temp;
				}
			}
			strncat(buffer, &read, 1);
		}
		else
		{
			if(buffer[0] >= 32 && buffer[0] <= 126 && strlen(buffer) >= 4)
			{
				printf("%s\n", buffer);
			}
			/* memset(buffer, 0, sizeof(buffer));
			 *
			 * Instead of using memset, manually clear the buffer
			 */
			for(mem_loop_counter = 0; mem_loop_counter < strlen(buffer); mem_loop_counter++)
			{
				buffer[mem_loop_counter] = 0;
			}
		}
	}

	free(buffer);

	return 0;
}
