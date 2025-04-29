/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author ??? (TODO: your name)
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "buffer.h"
#include <iostream>
#include <vector>
#include <pthread.h>

using namespace std;

//Has all of the synchdonization primitives (mutex, condition variables),
//buffer data (circular array), and metadata for insert/remove logic
class BufferMonitor {
	public:
	vector<buffer_item> buffer;
	int size;
	int in, out, count;

	pthread_mutex_t mutex; // protects shared access
	pthread_cond_t not_full;
	pthread_cond_t not_empty;

	BufferMonitor(int s) : size(s), buffer(s), in(0), out(0), count(0) {
		pthread_mutex_init(&mutex, NULL);
		pthread_cond_init(&not_full, NULL);
		pthread_cond_init(&not_empty, NULL);
	}

	~BufferMonitor() {
		pthread_mutex_destroy(&mutex);
		pthread_cond_destroy(&not_full);
		pthread_cond_destroy(&not_empty);
	}
};

static BufferMonitor* monitor = nullptr;

//Initializes the internal monitor with a buffer of given side
Buffer::Buffer(int size) {
	if (!monitor)
	monitor = new BufferMonitor(size);
}

//Frees the internal monitor and its resources
Buffer::~Buffer() {
	delete monitor;
	monitor = nullptr;
}

//Insert and item into the buffer First In First Out
bool Buffer::insert_item(buffer_item item) {
	pthread_mutex_lock(&monitor->mutex);

	while (monitor->count == monitor->size)
	pthread_cond_wait(&monitor->not_full, &monitor->mutex);

	monitor->buffer[monitor->in] = item;
	monitor->in = (monitor->in + 1) % monitor->size;
	monitor->count++;

	//Signal that buffer is no longer empty
	pthread_cond_signal(&monitor->not_empty);
	pthread_mutex_unlock(&monitor->mutex);
	return true;
}

//Remove an item from the buffer First In First Out
bool Buffer::remove_item(buffer_item* item) {
	pthread_mutex_lock(&monitor->mutex);

	while (monitor->count == 0)
	pthread_cond_wait(&monitor->not_empty, &monitor->mutex);

	*item = monitor->buffer[monitor->out];
	monitor->out = (monitor->out + 1) % monitor->size;
	monitor->count--;

	//Signal that buffer is no longer full
	pthread_cond_signal(&monitor->not_full);
	pthread_mutex_unlock(&monitor->mutex);
	return true;
}

int Buffer::get_size() { return monitor->size; }
int Buffer::get_count() { return monitor->count; }
bool Buffer::is_empty() { return monitor->count == 0; }
bool Buffer::is_full() { return monitor->count == monitor->size; }

//prints in First in First Out order
void Buffer::print_buffer() {
	pthread_mutex_lock(&monitor->mutex);
	cout << "Buffer: [";
	for (int i = 0; i < monitor->count; ++i) {
		int index = (monitor->out + i) % monitor->size;
		cout << monitor->buffer[index];
		if (i < monitor->count - 1) cout << ", ";
	}
	cout << "]" << endl;
	pthread_mutex_unlock(&monitor->mutex);
}
