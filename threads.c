#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <malloc.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define SHARED_STRING_LENGTH 128
#define EXIT_ID "exit"

char*  shared_time_str;

pthread_mutex_t mutex;
pthread_cond_t cvar;
time_t tm;

void sayBye();

void* server_task(void* param){
	int counter = * (int *) param;
	int i; 
	for (i = 0; i < counter; i++){
		sleep(1);
		time(&tm);
		pthread_mutex_lock(&mutex);
		char* ctm = ctime(&tm);
		strcpy(shared_time_str, ctm);
		printf("Server thread prepared a new time.\n");
		pthread_cond_signal(&cvar);
		pthread_mutex_unlock(&mutex);
	}
	sayBye();
}

void sayBye(){
	sleep(1);
	pthread_mutex_lock(&mutex);
	strcpy(shared_time_str, EXIT_ID);
	printf("Server thread said bye and finished a task.\n");
	pthread_cond_signal(&cvar);
	pthread_mutex_unlock(&mutex);
}

void* client_task(void* param){
	while(1){
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cvar, &mutex);
		printf("Client thread read a new time: %s", shared_time_str);
		if (!strcmp(shared_time_str, EXIT_ID)){
			printf("\nClient thread finished a task.\n");
			return;
		}
		pthread_mutex_unlock(&mutex);
	}
}


void init(){
    shared_time_str = (char*) malloc(SHARED_STRING_LENGTH);
    pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&cvar, 0);
}

int main(int argc, char **argv)
{
	pthread_t thread0;
	pthread_t thread1;
    init();
    int counter = 10;
    pthread_create(&thread0, 0, &server_task, (void *) &counter);	
    pthread_create(&thread1, 0, &client_task, 0);
    pthread_join(thread0, 0);
    pthread_join(thread1, 0);
	return 0;
}

