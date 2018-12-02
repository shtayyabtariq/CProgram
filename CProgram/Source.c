#include<stdio.h>
#include<stdlib.h>
#include <math.h>


int get_record_count(char *);
int load_data(char*, int *, float *, int );
void print_data(int *, float *, int);
int highest_amount(float *, int);
int lowest_amount(float *, int);
float average_amount(float *, int);
int write_data(char*, int *, float *, int, int, int, float);

int main(int argc, char  *argv[])
{
	if (argc < 3)
	{

		printf("%s", "Arguments are less");
		return 0;

	}

	char *input = argv[1];
	char *output = argv[2];
	int lines = get_record_count(input);


	float *Float = malloc(lines * sizeof *Float);
	int * INT = malloc(lines * sizeof * INT);
	
	load_data(input, INT, Float, lines);

	print_data(INT, Float, lines);

	int hindex = highest_amount(Float, lines);
	
	int lindex = lowest_amount(Float, lines);
	

	float avg = average_amount(Float, lines);
	write_data(output, INT, Float, lines, hindex, lindex, avg);
}


int get_record_count(char *filename)
{

	FILE *fp;
	char ch;


	fp = fopen(filename, "r"); // read mode

	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	int lines = 0;
	//printf("The contents of %s file are:\n", file_name);

	while (!feof(fp))
	{
		ch = fgetc(fp);
		//printf("%c", ch);
		if (ch == '\n')
		{
			lines++;
		}
	}
	

	return lines;
}


int load_data(char*filename, int *account, float *balance, int size)
{

	FILE *fp;



	fp = fopen(filename, "r"); // read mode

	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	int i = 1;
	int k = 0;
	while (!feof(fp))
	{
		//ch = fgetc(fp);

		
		if (i % 2 != 0)
		{
			fscanf(fp, "%d", &account[k]);
			i++;
		}
		else
			if (i % 2 == 0)
			{

				fscanf(fp, "%f", &balance[k]);
				
				k++;
				
				i++;
			}


	}
	return 1;
}

void print_data(int *INT, float *Float, int lines)
{
	printf("%d%s\n", lines, " records in the file");
	printf("%s\t%s\n", "Account No.", "Amount");
	int i = 0;
	int hindex = highest_amount(Float, lines);

	int lindex = lowest_amount(Float, lines);


	float avg = average_amount(Float, lines);
	while (i < lines)
	{
		printf("%d\t", INT[i]);
		printf("%.2f\n", Float[i]);
		i++;
	}

	printf("%s%.2f%s%d\n", "The highest amount is $", Float[hindex], " in the account number ", INT[hindex]);
	printf("%s%.2f%s%d\n", "The lowest amount is $", Float[lindex], " in the account number ", INT[lindex]);

	printf("%s%.2f\n", "The average amount is $", avg);
}


int highest_amount(float *balance, int size)
{


	float highest = 0;
	int index = 0;
	int i = 0;
	while (i < size)
	{

		if (highest < balance[i])
		{
			index = i;
			highest = balance[i];

		}
		i++;
	}


	return index;

}


int lowest_amount(float *balance, int size)
{


	float lowest = balance[0];
	int index = 0;
	int i = 0;
	while (i < size)
	{

		if (lowest > balance[i])
		{
			index = i;
			lowest = balance[i];

		}
		i++;
	}


	return index;
}

float average_amount(float *balance, int size)
{


	float sum = 0;
	
	int i = 0;
	while (i < size)
	{

		
			sum += balance[i];

		
		i++;
	}


	return (sum/size);


}

int write_data(char* filename, int *account, float *balance, int size, int highest_ind, int lowest_ind, float avg)
{

	
	FILE *fp;



	fp = fopen(filename, "w"); // read mode

	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		return 0;
		exit(EXIT_FAILURE);
	}
	int i = 1;
	
	fprintf(fp, "%d%s\n", size, " records in the file");
	fprintf(fp,"%s\t%s\n", "Account No.", "Amount");
	while (i < size)
	{
		



		fprintf(fp, "%d\t", account[i]);
		


		fprintf(fp, "%.2f\n", balance[i]);
		i++;
		

		

	}
	fprintf(fp,"%s%.2f%s%d\n", "The highest amount is $",balance[highest_ind] , " in the account number ",account[highest_ind] );
	fprintf(fp, "%s%.2f%s%d\n", "The lowest amount is $", balance[lowest_ind], " in the account number ", account[lowest_ind]);

	fprintf(fp, "%s%.2f\n", "The average amount is $", avg);

	return 1;
}