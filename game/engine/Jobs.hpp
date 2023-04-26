#ifndef ENGINE_JOBS_HPP
#define ENGINE_JOBS_HPP

#include "Defines.hpp"
#include <functional>
#include <condition_variable>

namespace jobs {
	/**
	* Create the internal resources such as worker threads, etc. Call it once when initializing the application.
	*/
	void Initialize();

	/**
	* Add a job to execute asynchronously. Any idle thread will execute this job.
	* @param job
	*/
	GAPI void Execute(const std::function<void()>& job);

	/**
	* Check if any threads are working currently or not
	*/
	bool IsBusy();

	/**
	* Wait until all threads become idle
	*/
	GAPI void Wait();
};

#endif //ENGINE_JOBS_HPP

// Fixed size very simple thread safe ring buffer

template <typename T, size_t capacity>

class ThreadSafeRingBuffer
{
public:
	// Push an item to the end if there is free space
	// Returns true if succesful
	// Returns false if there is not enough space
	inline bool push_back(const T& item)
	{
		bool result = false;
		lock.lock();
		size_t next = (head + 1) % capacity;
		if (next != tail)
		{
			data[head] = item;
			head = next;
			result = true;
		}
		lock.unlock();
		return result;
	}

	/**
	* Get an item if there are any
	* @param item : The item we want.
	* @return True if successful, false if there are no items
	*/
	inline bool pop_front(T& item)
	{
		bool result = false;
		lock.lock();
		if (tail != head)
		{
			item = data[tail];
			tail = (tail + 1) % capacity;
			result = true;
		}
		lock.unlock();
		return result;
	}

private:
	T data[capacity];
	size_t head = 0;
	size_t tail = 0;
	std::mutex lock;

};