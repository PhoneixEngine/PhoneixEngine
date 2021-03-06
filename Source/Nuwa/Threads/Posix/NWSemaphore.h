//
// Copyright(c) 2020 - 2022 the NuwaEngine project.
// Open source is written by wangcan(crygl)��liuqian(SkySnow)��zhangshuangxue(Calence)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#pragma once
#include "NonCopyable.h"
#include <semaphore.h>
#include <errno.h>
#include "LogAssert.h"
namespace Nuwa
{
	class Semaphore :public NonCopyable
	{
		friend class ThreadSemaphore;
	protected:
		void Create();
		void Destroy();
		void WaitForSignal();
		void Signal();
	private:
		sem_t m_Semaphore;
	};

	inline void Semaphore::Create()
	{
		if (sem_init(&m_Semaphore, 0, 0) == -1)
		{
			NUWAERROR("Failed to open a semaphore(%s).", strerror(errno));
		}	
	}

	inline void Semaphore::Destroy()
	{
		if (sem_destroy(&m_Semaphore) == -1)
		{
			NUWAERROR("Filed to destroy a semaphore(%s).", strerror(errno));
		}	
	}
	inline void Semaphore::WaitForSignal()
	{
		int ret = 0;
		while ((ret = sem_wait(&m_Semaphore)) == -1 && errno == EINTR)
		{
			continue;
		}
		if (ret == -1)
			NUWAERROR("Filed to wait on a semaphore(%s).", strerror(errno));
	}
	inline void Semaphore::Signal()
	{
		if (sem_post(&m_Semaphore) == -1)
		{
			NUWAERROR("Filed to post to a semaphore(%s).", strerror(errno));
		}

	}
}