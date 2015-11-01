//*********************************************************
//
//
// 
//*********************************************************


//*********************************************************
//
// Includes and Defines
//
//*********************************************************
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace std;

int num;
vector<int> fibNum;

void *fib(void*)
{
	int total;

	for (int i = 0; i <= num; i++) {
		if (i <= 1) {
			total = i;
		}

		else if (num == 0)
		{
			pthread_exit(0);
		}
		else
		{
			total = fibNum[i-1] + fibNum[i-2];
		}

		fibNum.push_back(total);
	}

	pthread_exit(0);
}

int main(int argc, char *argv[]) {

	pthread_t tid;

	double total;

	num = atoi(argv[1]);

	pthread_create(&tid, NULL, &fib, NULL);

	pthread_join(tid, NULL);

	cout << "Series: " << endl;
	for (int i = 0; i < num; i++)
		cout << fibNum[i] << endl;

	int size = fibNum.size();

	cout << "Total: ";
	total = fibNum[size] + fibNum[size - 1];
	cout << total << endl;

	return 0;
}