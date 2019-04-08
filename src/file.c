#include "file.h"

void saveToFile(int records_number, struct ranking_record *records, struct ranking_record player)
{
	FILE *fptr;
	fptr = fopen("ranking.dat", "w");

	if (fptr != NULL)
	{

		if (records != NULL)
			for (int i = 0; i < records_number; ++i)
			{
				if (player.score > records[i].score)
				{
					fprintf(fptr, "%d", player.score);
					fprintf(fptr, ",");
					for (int j = 0; j < 3; ++j)
						fprintf(fptr, "%c", player.name[j]);
					fprintf(fptr, ";\n");
					player.score = 0;
					if (records_number >= 10)
					{
						records_number -= 1;
					}

				}
				fprintf(fptr, "%d", records[i].score);
				fprintf(fptr, ",");
				for (int j = 0; j < 3; ++j)
					fprintf(fptr, "%c", records[i].name[j]);
				fprintf(fptr, ";\n");
			}
		if (player.score != 0 && records_number<10)
		{
			fprintf(fptr, "%d", player.score);
			fprintf(fptr, ",");
			for (int i = 0; i < 3; ++i)
				fprintf(fptr, "%c", player.name[i]);
			fprintf(fptr, ";\n");
		}


		fclose(fptr);
	}
}
void readFromFile(int *records_number, struct ranking_record **records)
{
	char tmp;
	*records_number = 0;
	FILE *fptr;


	if ((fptr = fopen("ranking.dat", "r")) != NULL)
	{

		while (!feof(fptr))
		{
			tmp = fgetc(fptr);
			if (tmp == '\n')
			{
				*records_number += 1;
			}
		}

		*records = (struct ranking_record *)malloc(sizeof(struct ranking_record)*(*records_number));



		fseek(fptr, 0, SEEK_SET);
		for (int i = 0; i<(*records_number); ++i)
		{
			fscanf(fptr, "%d", &(*records)[i].score);
			getc(fptr);
			fscanf(fptr, "%c", &(*records)[i].name[0]);
			fscanf(fptr, "%c", &(*records)[i].name[1]);
			fscanf(fptr, "%c", &(*records)[i].name[2]);
			do
				tmp = fgetc(fptr);
			while (tmp != '\n');

		}
		//printf("%d", *records_number);
		fclose(fptr);
	}
}