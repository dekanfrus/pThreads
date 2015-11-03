//**********************************************************************************
//
// John Alves
// Operating Systems
// Project #2: Printing Words
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
#include <unistd.h>
#include <vector>
#include <sstream>


using namespace std;

// Global variable to hold the user's phrase
vector<string>phrase;

//********************************************************************
//
// Con  Function
//
// This function reads through the user's phrase and will output all 
// words that begin with a consonant.  If the word starts with a vowel
// the thread that is calling this function will yield to the thread
// that is calling the vowel function.
//
// Global Parameters
// --------------------
// phrase vector<string>    This variable holds the user's phrase
//
//*******************************************************************
void *con(void*)
{
	// Stores the length of the phrase vector as an integer.
	int end = (int)phrase.size();

	// Iterate through the phrase vector and look for consonants.
	// If the word begins with a consonant, print that word.
	// Otherwise, yield the CPU to the other thread.
	for (int i = 0; i != end; i++)
	{
		if (phrase[i][0] != 'A' && phrase[i][0] != 'a' && phrase[i][0] != 'E' && phrase[i][0] != 'e' && phrase[i][0] != 'I' && phrase[i][0] != 'i' && phrase[i][0] != 'O' && phrase[i][0] != 'o' && phrase[i][0] != 'U' && phrase[i][0] != 'u')
			cout << "Con: " << phrase[i] << endl;
		else sched_yield();
	}
	// Exit the thread once the function has completed running.
	pthread_exit(NULL);
}

//********************************************************************
//
// Vow  Function
//
// This function reads through the user's phrase and will output all 
// words that begin with a vowel.  If the word starts with a consonant
// the thread that is calling this function will yield to the thread
// that is calling the consonant function.
//
// Global Parameters
// --------------------
// phrase vector<string>	This variable holds the user's phrase
//
//*******************************************************************
void *vow(void*)
{
	// Initial yield to allow the other thread to begin operations first
	sched_yield();

	// Stores the length of the phrase vector as an integer.
	int end = (int)phrase.size();

	// Iterate through the phrase vector and look for vowels.
	// If the word begins with a vowel, print that word.
	// Otherwise, yield the CPU to the other thread.
	for (int i = 0; i != end; i++)
	{
		if (phrase[i][0] == 'A' || phrase[i][0] == 'a' || phrase[i][0] == 'E' || phrase[i][0] == 'e' || phrase[i][0] == 'I' || phrase[i][0] == 'i' || phrase[i][0] == 'O' || phrase[i][0] == 'o' || phrase[i][0] == 'U' || phrase[i][0] == 'u')
			cout << "Vow: " << phrase[i] << endl;
		else sched_yield();
	}
	// Exit the thread upon function completion.
	pthread_exit(NULL);
}

//********************************************************************
//
// Main function
//
// This function is called upon program execution and will prompt
// the user for a phrase.  That phrase is stored in a string variable
// which is then converted (with a stringstream) to a vector of strings.
// Once the input is read, two threads are created.  One for the vowel
// function, and the other for the consonant function.  The main function
// is joined to those threads with the pthread_join command.  The main
// function (and therefore the program) will not continue until both
// threads have exited.
//
//
// Global Parameters
// --------------------
// phrase	vector<string>	Holds the user phrase
//
// Local Variables
// ---------------
// tid1     p_thread        Holds the thread identifier
// tid2		p_thread		Holds the thread identifier
// input	string			Holds the user input
// buffer	string			Temp variable to hold string contents
//
//*******************************************************************
int main() {

	pthread_t tid1, tid2;
	string input;
	string buffer;

	cout << "Please enter a phrase: ";
	getline(cin, input);
		
	stringstream stream(input);

	while (stream >> buffer)
		phrase.push_back(buffer);

	pthread_create(&tid1, NULL, &con, NULL);
	pthread_create(&tid2, NULL, &vow, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);



	return 0;
}
