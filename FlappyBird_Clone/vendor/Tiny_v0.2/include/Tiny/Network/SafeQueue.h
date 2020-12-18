#pragma once
#include "Common.h"


namespace Tiny {
	
	/* This is a Thread Safe Queue
	   - Safety using locking via mutex  
	*/
	template<typename T>
	class SafeQueue
	{
	public:
		SafeQueue() = default;
		SafeQueue(const SafeQueue&) = delete;
		virtual ~SafeQueue();

		const T& front();
		T pop_front();

		const T& back();
		T pop_back();
		
		void push_back(const T& item);
		void push_front(const T& item);
		
		bool empty();
		size_t count();
		void clear();
		void wait();

	protected:
		std::mutex m_MQueue;
		std::deque<T> m_DeqQueue;
		std::condition_variable m_CVBlocking;
		std::mutex m_MBlocking;
	};

	template<typename T>
	Tiny::SafeQueue<T>::~SafeQueue()
	{
		clear();
	}

	template<typename T>
	void Tiny::SafeQueue<T>::wait()
	{
		while (empty())
		{
			std::unique_lock<std::mutex> ul(m_MBlocking);
			m_CVBlocking.wait(ul);
		}
	}

	template<typename T>
	void Tiny::SafeQueue<T>::clear()
	{
		std::scoped_lock lock(m_MQueue);
		m_DeqQueue.clear();
	}

	template<typename T>
	size_t Tiny::SafeQueue<T>::count()
	{
		std::scoped_lock lock(m_MQueue);
		return m_DeqQueue.size();
	}

	template<typename T>
	bool Tiny::SafeQueue<T>::empty()
	{
		std::scoped_lock lock(m_MQueue);
		return m_DeqQueue.empty();
	}

	template<typename T>
	void Tiny::SafeQueue<T>::push_front(const T& item)
	{
		std::scoped_lock lock(m_MQueue);
		m_DeqQueue.emplace_front(std::move(item));

		std::unique_lock<std::mutex> ul(m_MBlocking);
		m_CVBlocking.notify_one();
	}

	template<typename T>
	void Tiny::SafeQueue<T>::push_back(const T& item)
	{
		std::scoped_lock lock(m_MQueue);
		m_DeqQueue.emplace_back(std::move(item));

		std::unique_lock<std::mutex> ul(m_MBlocking);
		m_CVBlocking.notify_one();
	}

	template<typename T>
	T Tiny::SafeQueue<T>::pop_back()
	{
		std::scoped_lock lock(m_MQueue);
		auto t = std::move(m_DeqQueue.back());
		m_DeqQueue.pop_back();
		return t;
	}

	template<typename T>
	const T& Tiny::SafeQueue<T>::back()
	{
		std::scoped_lock lock(m_MQueue);
		return m_DeqQueue.back();
	}

	template<typename T>
	T Tiny::SafeQueue<T>::pop_front()
	{
		std::scoped_lock lock(m_MQueue);
		auto t = std::move(m_DeqQueue.front());
		m_DeqQueue.pop_front();
		return t;
	}

	template<typename T>
	const T& Tiny::SafeQueue<T>::front()
	{
		std::scoped_lock lock(m_MQueue);
		return m_DeqQueue.front();
	}

}
