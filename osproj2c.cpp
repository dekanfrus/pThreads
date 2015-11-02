#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>


using namespace std;

vector<string>phrase;

void *con(void*)
{

	for (int it = 0; it < phrase.size(); ++it)
	{
		if (phrase.front().at(it) != 'A' || phrase.front().at(it) != 'a' || phrase.front().at(it) != 'E' || phrase.front().at(it) != 'e' || phrase.front().at(it) != 'I' || phrase.front().at(it) != 'i' || phrase.front().at(it) != 'O' || phrase.front().at(it) != 'o' || phrase.front().at(it) != 'U' || phrase.front().at(it) != 'u')
		{
			cout << "Con: " << phrase[it] << endl;
		}
		else
		{
			sched_yield();
		}
	}

	pthread_exit(NULL);
}

void *vow(void*)
{
	sched_yield();

	for (int i = 0; i < phrase.size(); i++)
	{
		if (phrase.front().at(i) == 'A' || phrase.front().at(i) == 'a' || phrase.front().at(i) == 'E' || phrase.front().at(i) == 'e' || phrase.front().at(i) == 'I' || phrase.front().at(i) == 'i' || phrase.front().at(i) == 'O' || phrase.front().at(i) == 'o' || phrase.front().at(i) == 'U' || phrase.front().at(i) == 'u')
		{
			cout << "Vow: " << phrase[i] << endl;
		}
		else
		{
			sched_yield();
		}
	}

	pthread_exit(NULL);
}


int main(int argc, char *argv[]) {

	pthread_t tid1, tid2;
	
	vector<string>input(argv, argv + argc);
	phrase = input;

	phrase.erase(phrase.begin());

	int size = phrase.size();

	pthread_create(&tid1, NULL, &con, NULL);
	pthread_create(&tid2, NULL, &vow, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);



	return 0;
}