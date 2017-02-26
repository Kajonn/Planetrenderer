
#include "jobhandler.h"
#include <thread>
#include <mutex>
#include <queue>

Jobhandler::JobThread::JobThread(Jobhandler &jobhandler) :
	m_jobHandler(jobhandler) {
}

void Jobhandler::JobThread::operator()() {	
	std::function<void()> f;
	while(true) {
		{
			//Lock will be released when destroyed
			std::unique_lock<std::mutex> lock(m_jobHandler.m_lock);

			if(!m_jobHandler.m_stop && m_jobHandler.m_jobqueue.empty()) {
				m_jobHandler.m_conditional.wait(lock);
			}			

			if(m_jobHandler.m_stop)
				return;						

			f = m_jobHandler.m_jobqueue.front();
			m_jobHandler.m_jobqueue.pop();

			//Lock is relesed
		}

		f();
	}
}

Jobhandler::Jobhandler(int nThreads_) :
	m_stop(false)
{
	for (int i = 0; i < nThreads_; i++)
	{
		m_jobThreads.push_back(std::thread(JobThread(*this)));
	}
}


Jobhandler::~Jobhandler(void)
{

	m_stop = true;

	m_conditional.notify_all();

	for (int i = 0; i < (int)(m_jobThreads.size()); i++)
	{
		m_jobThreads[i].join();
	}
}

void Jobhandler::addJob(std::function<void()> job) {
	m_lock.lock();
	m_jobqueue.push(job);
	m_lock.unlock();

	m_conditional.notify_one();
}

void Jobhandler::start() {
		
	
}