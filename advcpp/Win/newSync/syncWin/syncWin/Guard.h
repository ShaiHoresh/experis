#ifndef __GUARD_H__
#define __GUARD_H__

#include "uncopyable.h"
#include "Mutex.h"
namespace advcpp
{

namespace sync
{

class Guard : private uncopyable
{
public:
	explicit Guard(Mutex*);
	~Guard();

private:
	Mutex* m_mutex;
};

} // namespace sync
} // namespace advcpp
#endif /* __GUARD_H__ */

