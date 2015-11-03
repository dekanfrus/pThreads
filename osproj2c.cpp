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
		if (phrase[i][0] != 'A' && phrase[i][0] != 'a' && phrase[i][0] != 'E' && phrase[i][0] != 'e' && phrase[i][0] != 'I' && phrase[i][0] != 'i' && phrase[i][0] != 'O' && phrase[i][0] != 'o' && phrase[i][0] != 'U' && phrase[i][0] != 'u')
			cout << "Con: " << phrase[i] << endl;
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
		if (phrase[i][0] == 'A' || phrase[i][0] == 'a' || phrase[i][0] == 'E' || phrase[i][0] == 'e' || phrase[i][0] == 'I' || phrase[i][0] == 'i' || phrase[i][0] == 'O' || phrase[i][0] == 'o' || phrase[i][0] == 'U' || phrase[i][0] == 'u')
			cout << "Vow: " << phrase[i] << endl;
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

	pthread_create(&tid1, NULL, &con, NULL);
	pthread_create(&tid2, NULL, &vow, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);



	return 0;
}