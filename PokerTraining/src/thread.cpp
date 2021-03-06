/*****************************************************************************
 * PokerTraining - THNL training software, based on the PokerTH GUI          *
 * Copyright (C) 2013 Marc Ennaji                                            *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU Affero General Public License as            *
 * published by the Free Software Foundation, either version 3 of the        *
 * License, or (at your option) any later version.                           *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 *****************************************************************************/

#include <thread.h>


// Helper class for thread creation.
class ThreadStarter
{
public:
	ThreadStarter(Thread &thread) : m_thread(thread) {}
	void operator()() {
		m_thread.MainWrapper();
	}

private:
	Thread &m_thread;
};

Thread::Thread()
	: m_isTerminatedSemaphore(0), m_shouldTerminateSemaphore(0)
{
}

Thread::~Thread()
{
}

void
Thread::Run()
{
	boost::mutex::scoped_lock threadLock(m_threadObjMutex);

	// Create the boost thread object.
	if (!m_threadObj.get()) {
		m_threadObj.reset(new boost::thread(ThreadStarter(*this)));
	}
}

void
Thread::SignalTermination()
{
	m_shouldTerminateSemaphore.post();
}

bool
Thread::Join(unsigned msecTimeout)
{
	if (!IsRunning())
		return true;

	bool tmpIsTerminated;
	if (msecTimeout == THREAD_WAIT_INFINITE) {
		// Wait infinitely.
		m_isTerminatedSemaphore.wait();
		tmpIsTerminated = true;
	} else {
		// Wait for the termination of the application code.
		tmpIsTerminated = m_isTerminatedSemaphore.timed_wait(boost::posix_time::microsec_clock::universal_time() + boost::posix_time::millisec(msecTimeout));
	}

	if (tmpIsTerminated) {
		boost::mutex::scoped_lock lock(m_threadObjMutex);
		// Wait for "real" termination of the thread.
		if (m_threadObj) {
			m_threadObj->join();
			m_threadObj.reset();
		}
	}

	return tmpIsTerminated;
}

void
Thread::Msleep(unsigned msecs)
{
	boost::this_thread::sleep(boost::posix_time::millisec(msecs));
}

void
Thread::MainWrapper()
{
	this->Main();
	m_isTerminatedSemaphore.post();
}

bool
Thread::ShouldTerminate() const
{
	return m_shouldTerminateSemaphore.try_wait();
}

bool
Thread::IsRunning() const
{
	boost::mutex::scoped_lock threadLock(m_threadObjMutex);
	return (m_threadObj.get() != NULL);
}

