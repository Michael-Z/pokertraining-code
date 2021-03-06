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
/* Base class for threads (used by network client/server). */

#ifndef _THREAD_H_
#define _THREAD_H_

#include <boost/thread.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/shared_ptr.hpp>

#ifndef NANOSECONDS_PER_SECOND
#define NANOSECONDS_PER_SECOND 1000000000
#endif

#define THREAD_WAIT_INFINITE	0xFFFFFFFF

class Thread
{
public:
	Thread();
	virtual ~Thread();

	// Start the thread. Will do nothing if the
	// thread was already started.
	void Run();

	// Signal that the thread should be terminated
	virtual void SignalTermination();

	// Wait for the termination of the thread.
	// Only one Thread should wait for the termination!
	// You SHOULD always call join for a thread.
	bool Join(unsigned msecTimeout);

	// Sleep the currently active thread.
	static void Msleep(unsigned msecs);

protected:

	// Startup function.
	void MainWrapper();

	// Main function of the thread.
	virtual void Main() = 0;

	// Checks whether termination has been requested.
	bool ShouldTerminate() const;

	// Checks whether the thread is running.
	bool IsRunning() const;

private:

	// Flag specifying whether the application code within the
	// thread was terminated.
	mutable boost::interprocess::interprocess_semaphore m_isTerminatedSemaphore;

	// Flag specifying whether the thread should be terminated.
	mutable boost::interprocess::interprocess_semaphore m_shouldTerminateSemaphore;

	// The boost thread object.
	boost::shared_ptr<boost::thread> m_threadObj;
	mutable boost::mutex m_threadObjMutex;

	friend class ThreadStarter;
};

#endif
