//**********************************************************************************
//
// John Alves
// Operating Systems
// Project #2: Fibonacci Numbers
// November 2nd, 2015
// Instructor: Dr. Katangur
//
//**********************************************************************************


//**********************************************************************************
//
// Includes and Defines
//
//**********************************************************************************
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace std;

// Global Variable Declations
int num;
vector<int> fibNum;

//********************************************************************
//
// Fib  Function
//
// This function calculates the fibonacci sequence based on a value
// that is provided by the user.
//
// Global Parameters
// --------------------
// fibNum	vector<int>		Holds the value the user wishes to calculate
//
// Local Variables
// ----------------
// total	int				Holds the next value in the fibonacci sequence
// i		int				Iterator/counter for the for loop
//
//*******************************************************************
void *fib(void*)
{
	int total;

	// Iterates through and calculates the fibonnaci sequence
	for (int i = 0; i <= num; i++) {
		if (i <= 1) {
			total = i;
		}

		else if (num == 0)
		{
			// Quit the thread if the user's number was 0 as
			// there is nothing to calculate
			pthread_exit(0);
		}
		else
		{
			// Grab the values from the two previous indices
			// add them together and store them in total
			total = fibNum[i-1] + fibNum[i-2];
		}

		// Push the total to the end of the series vector
		fibNum.push_back(total);
	}

	// Exit the thread upon completion
	pthread_exit(0);
}

//********************************************************************
//
// Main Function
//
// This function is called upon program execution.  It reads in the
// number the user wishes to calculate from the command line.
// It then creates a new thread to run the fib function.
//
// Global Parameters
// --------------------
// fibNum		vector<int>		Holds the Fibonacci series
// num			int				Holds the user's value to be calculated		
//
// Local Variables
// ----------------
// tid			pthread_t		Holds the thread ID
// total		double			Holds the Fibonacci value
//
//*******************************************************************
int main(int argc, char *argv[]) {

	// Local variable declaration
	pthread_t tid;
	double total = 0;

	// Create a new thread and run the fib function
	pthread_create(&tid, NULL, &fib, NULL);

	// Join the thread to the main process and wait for it to complete
	// before continuing.
	pthread_join(tid, NULL);

	// Display the entire Fibonacci series 
	cout << "Series: " << endl;
	for (int i = 0; i < num; i++)
		cout << fibNum[i] << endl;

	int size = fibNum.size();

	// Display the actual Fibonacci value
	cout << "Total: ";
	total = fibNum[size] + fibNum[size - 1];
	cout << total << endl;

	return 0;
}