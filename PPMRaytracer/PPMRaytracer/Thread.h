#ifndef THREAD_H
#define THREAD_H

#include <functional>
#include <mutex>

namespace rtcr
{
	class Thread
	{
	public:
		Thread(int sleepPeriod, std::function<bool()> callback);
		~Thread();

	public:
		void Start();
		void WakeUp();
		void Terminate();
		void SetSleepPeriod(int period);
		void SetSleepPeriodSeconds(int periodSeconds);

	private:
		std::mutex m_mutex;
		std::shared_ptr<std::thread> m_thread;
		std::condition_variable m_event;
		bool m_exit;
		bool m_wakeUp;

		std::function<bool()> m_callback;
		int m_sleepPeriod;
	};

	using ThreadPtr = std::shared_ptr<Thread>;
}

#endif
