#pragma once

#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

class Jobhandler
{
public:
	Jobhandler(int nThreads_);
	~Jobhandler(void);

	void addJob(std::function<void()> job);

	void start();

private:

	class JobThread {
	public:
		JobThread(Jobhandler &jobhandler);
		void operator()();
	private:
		Jobhandler &m_jobHandler;
	};

	std::atomic<bool> m_stop;

	std::condition_variable m_conditional;

	std::queue<std::function<void()>> m_jobqueue;

	std::mutex m_lock;

	std::vector<std::thread> m_jobThreads;
};

