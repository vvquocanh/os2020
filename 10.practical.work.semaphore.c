
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>

pthread_mutex_t lock;

void* printPrime(void* args) {
	pthread_detach(pthread_self());
	for (int i = 2; i < 1000000; i++) {
		for (int j = i-1; j > 0; j--) {
			if (j == 1) {
				pthread_mutex_lock(&lock);
				printf("Prime: %d\n", i);
				pthread_mutex_unlock(&lock);
			} else if (i % j == 0) {
				break;
			}
		}
	}
	pthread_exit(NULL);
}

void* printFibonacci(void* args) {
	pthread_detach(pthread_self());
	int cur1 = 0;
	int cur2 = 1;
	int cur3 = cur1 + cur2;
	int check = 0;
	while (check == 0) {
		pthread_mutex_lock(&lock);
		printf("Fibonacci: %d\n", cur3);
		pthread_mutex_unlock(&lock);
		cur1 = cur2;
		cur2 = cur3;
		cur3 = cur1 + cur2;
		if (cur3 > 1000000) {
			check = 1;
		}
	}
	pthread_exit(NULL);
}
int main() {
	pthread_t tid1;
	pthread_t tid2;

	pthread_create(&tid1,NULL,printPrime,NULL);
	pthread_create(&tid2,NULL,printFibonacci,NULL);

	printf("Created new threads (%lu) and (%lu)\n",tid1,tid2);
	
	pthread_exit(NULL);
	pthread_mutex_destroy(&lock);
        return 0;
}
