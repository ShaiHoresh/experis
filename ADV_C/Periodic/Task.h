#ifndef __TASK_H__
#define __TASK_H__

/*************************/
/*Task API FUNCTIONS*/
/*************************/

#include "scTime.h"

typedef struct Task Task;
typedef int (*TaskFunction) (void* _context);

/**
 *
 *
 * @warning be aware to use a valid clockid_t
 */
Task* TaskCreate(TaskFunction _taskFunction, void* _context, int _period_ms, const clockid_t _clockID);

void TaskDestroy(Task*);

/**
 *
 *
 * @warning be aware to use a valid clockid_t
 */
void TaskCalculateNext(Task* _task);

int TaskExecute(Task* _task);

int	TaskCompare(Task* _taskOne, Task* _taskTwo);

#endif /* #ifndef __TASK_H__ */
