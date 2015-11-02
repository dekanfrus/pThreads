#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <sstream>


using namespace std;

vector<string>phrase;

void *con(void*)
{
	int end = (int)phrase.size();


	for (int i = 0; i != end; i++)
	{
		if (phrase[i] != "A") cout << "Con: " << phrase[i] << endl;
		else if (phrase[i] != "a") cout << "Con: " << phrase[i] << endl;
		else if (phrase[i] != "E") cout << "Con: " << phrase[i] << endl;
		else if (phrase[i] != "e") cout << "Con: " << phrase[i] << endl;
		else if (phrase[i] != "I") cout << "Con: " << phrase[i] << endl;
		else if (phrase[i] != "i") cout << "Con: " << phrase[i] << endl;
		else if (phrase[i] != "O") cout << "Con: " << phrase[i] << endl;
		else if (phrase[i] != "o") cout << "Con: " << phrase[i] << endl;
		else if (phrase[i] != "U") cout << "Con: " << phrase[i] << endl;
		else if (phrase[i] != "u") cout << "Con: " << phrase[i] << endl;
		else sched_yield();

	}
	pthread_exit(NULL);
}

void *vow(void*)
{
	sched_yield();
	int end = (int)phrase.size();


	for (int i = 0; i != end; i++)
	{			
		if (phrase[i] == "A") cout << "Vow: " << phrase[i] << endl;
		else if (phrase[i] == "a") cout << "Vow: " << phrase[i] << endl;
		else if (phrase[i] == "E") cout << "Vow: " << phrase[i] << endl;
		else if (phrase[i] == "e") cout << "Vow: " << phrase[i] << endl;
		else if (phrase[i] == "I") cout << "Vow: " << phrase[i] << endl;
		else if (phrase[i] == "i") cout << "Vow: " << phrase[i] << endl;
		else if (phrase[i] == "O") cout << "Vow: " << phrase[i] << endl;
		else if (phrase[i] == "o") cout << "Vow: " << phrase[i] << endl;
		else if (phrase[i] == "U") cout << "Vow: " << phrase[i] << endl;
		else if (phrase[i] == "u") cout << "Vow: " << phrase[i] << endl;
		else sched_yield();
	}
	pthread_exit(NULL);
}


int main() {

	pthread_t tid1, tid2;
	string input;
	string buffer;

	cout << "Please enter a phrase: ";
	getline(cin, input);
		
	stringstream stream(input);

	while (stream >> buffer)
		phrase.push_back(buffer);

	phrase.erase(phrase.begin());

	pthread_create(&tid1, NULL, &con, NULL);
	pthread_create(&tid2, NULL, &vow, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);



	return 0;
}