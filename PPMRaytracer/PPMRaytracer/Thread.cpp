#include "Thread.h"

rtcr::Thread::Thread(int sleepPeriod, std::function<bool()> callback) :
	m_sleepPeriod(sleepPeriod),
	m_callback(callback),
	m_exit(false),
	m_wakeUp(false)
{
}

rtcr::Thread::~Thread()
{
	Terminate();
}

void rtcr::Thread::Start()
{
	m_thread = std::make_shared<std::thread>([this]()
		{
			do
			{
				if (!m_callback())
				{
					std::unique_lock<std::mutex> ul(m_mutex);
					auto status = m_event.wait_for(ul, std::chrono::milliseconds(m_sleepPeriod),
						[this]() { return m_wakeUp; });
					if (status && m_exit)
						break;
					else
						m_wakeUp = false;
				}
			} while (!m_exit);
		});

}

void rtcr::Thread::WakeUp()
{
	if (m_thread)
	{
		{
			std::lock_guard<std::mutex> ul(m_mutex);
			m_wakeUp = true;
		}
		m_event.notify_one();
	}
}

void rtcr::Thread::Terminate()
{
	if (m_thread)
	{
		{
			std::lock_guard<std::mutex> ul(m_mutex);
			m_exit = true;
			m_wakeUp = true;
		}

		m_event.notify_one();
		m_thread->join();
		m_thread = nullptr;
	}
}

void rtcr::Thread::SetSleepPeriod(int period)
{
	m_sleepPeriod = period;
}

void rtcr::Thread::SetSleepPeriodSeconds(int periodSeconds)
{
	m_sleepPeriod = periodSeconds * 1000;
}