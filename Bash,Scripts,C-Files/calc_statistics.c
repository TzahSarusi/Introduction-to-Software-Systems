#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char **argv) {
        int count=0, sum=0;

	if (argc < 1) {
		fprintf(stderr, "Error\n");

		return 1;
	}
	/* opens a txt file course_statistics for write mode, reads grades.txt*/
	FILE *fp,*fpt;
	fp = fopen("/home/mamat/Mamat_HW/HW2/044101_stat/course_statistics.txt", "w");
	if(fp == NULL){
		printf("Cant open file for write\n");
		exit(1);
	}
	fpt = fopen("/home/mamat/Mamat_HW/HW2/grades.txt", "r");
	if(fpt == NULL){
		printf("Cant open grades.txt for read\n");
		exit(1);
	}
	char * line = NULL;
   	size_t len = 0;
	ssize_t read;

	//  count the number of students
	while ((read = getline(&line, &len, fpt)) != -1) {

		//printf("Retrieved line of length %zu:\n", read);
		count++;
    	}

	int grades[count];
	int i=0, pass = 0, grade = 0;
	int median;
	int hist[100];
	for(int i=0;i<100;i++)
		hist[i] = 0;
	fclose(fpt);
	fpt = fopen("/home/mamat/Mamat_HW/HW2/grades.txt", "r");
	if(fpt == NULL){
		printf("Cant open grades.txt for read\n");
		exit(1);
	}
	while ((read = getline(&line, &len, fpt)) != -1) {

        	//printf("Retrieved line of length %zu:\n", read);
		grade = atoi(line);
		grades[i] = grade;
        	i++;
		sum+=grade;
		if(grade >= 55)
			pass++;
		//printf("grade: %d\n",grade);
		hist[grade-1]=1;
    	}
	qsort(grades, count, sizeof(int), cmpfunc);
	median = grades[(count+1)/2]; // Ask in the forum its not clear from the instruction
	fprintf(fp,"num of students = %d\n", count);
	fprintf(fp,"avg =%.3f\n",((double)sum)/count);
	fprintf(fp,"the median is - %d\n",median);
	fprintf(fp,"max grade = %d, min grade = %d\n",grades[count-1],grades[0]);
	fprintf(fp,"pass rate = %.2f%%\n",((double)pass*100)/count);
	for(int i=0;i<100;i++){
		if(i%10 != 0 &&(i%10)%9 == 0)
			fprintf(fp,"%d\n",hist[i]);
		else
			fprintf(fp,"%d ",hist[i]);
	}
	fclose(fp);
	fclose(fpt);
	return 0;
}