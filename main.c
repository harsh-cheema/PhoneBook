#include <stdio.h>
#include <time.h>
#include "phone_book_.h"


int main(){
	clock_t start_time,end_time;
	double cpu_time_used;

	start_time=clock();

	start_phonebook();

	end_time=clock();
	cpu_time_used=(double)((end_time-start_time)/CLOCKS_PER_SEC);

	printf("CPU Time used: %f seconds\n",cpu_time_used);
}
