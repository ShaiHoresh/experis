#include <iostream>
#include "tsts.h"
#include "Dog.h"
using namespace advcpp;

void* CreateDog(void* _context)
{
	std::tr1::shared_ptr<Dog> dog;
	for (unsigned int i = 0; i < 10; i += 1)
	{
		std::tr1::shared_ptr<Dog> dog = Singleton<Dog>::GetInstance();
		std::cout << "thread got dog " << dog->thisDog << std::endl;
	}
}

int main (int argc, char const* argv[])
{
	const unsigned int nThreads = 100000;
	
	pthread_t threads[nThreads];
	
	for (unsigned int i = 0; i < nThreads; i += 1)
	{
		while (pthread_create(threads + i, NULL, CreateDog, NULL))
		{
			pthread_join(threads[i-1], NULL);
		}
	}	
	
	for (unsigned int i = 0; i < nThreads; i += 1)
	{
		pthread_join(threads[i], NULL);
	}
			
}
