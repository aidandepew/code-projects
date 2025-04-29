/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Aidan DePew and Usman Ali
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include "buffer.h"

using namespace std;

Buffer buffer(5);

//Each producer generates an item, sleeps for a short time, 
//then inserts the item into the buffer prints the buffer content,
//and runs in an infinite loop
void* producer(void* param) {
	int id = *((int*)param);
	buffer_item item = id;

	while (true) {
		usleep(rand() % 1000000);
		buffer.insert_item(item);
		cout << "Producer " << id << ": Inserted item " << item << endl;
		buffer.print_buffer();
	}
	return NULL;
}

//Each consumer sleeps for a short time, removes item from the buffer,
//and prints the removed item and current buffer content,
//and runs in an infinite loop
void* consumer(void* param) {
	buffer_item item;

	while (true) {
		usleep(rand() % 1000000);
		buffer.remove_item(&item);
		cout << "Consumer Removed item " << item << endl;
		buffer.print_buffer();
	}
	return NULL;
}

//parses command-line arguements, initialize threads for producers and consumers,
//then sleeps for a specified time before exiting
//argc is the number of command-line arguments and argv is command-line arguments
int main(int argc, char* argv[]) {
	if (argc != 4) {
		cerr << "Usage: ./prog4 <sleep_time> <num_producers> <num_consumers>" << endl;
		return -1;
	}

	int sleep_time = atoi(argv[1]);
	int num_producers = atoi(argv[2]);
	int num_consumers = atoi(argv[3]);

	pthread_t producers[num_producers];
	pthread_t consumers[num_consumers];
	int thread_ids[100];

	// Create producer threads
	for (int i = 0; i < num_producers; ++i) {
		thread_ids[i] = i + 1;
		pthread_create(&producers[i], NULL, producer, &thread_ids[i]);
	}

	// Create consumer threads
	for (int i = 0; i < num_consumers; ++i) {
		thread_ids[50 + i] = i + 1;
		pthread_create(&consumers[i], NULL, consumer, &thread_ids[50 + i]);
	}

	//Main thread sleeps and exits
	sleep(sleep_time);
	cout << "Main thread done sleeping. Exiting." << endl;
	return 0;
}
