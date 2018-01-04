/*************************/
	/*STRUCTURES*/
/*************************/

#include <time.h> /* clockid_t */
#include "Heap.h"

typedef Heap PriorityQueue;

typedef struct PeriodicExecutor PeriodicExecutor;

typedef int (*TaskFunction) (void* _context); 



/*************************/
/*SCHEDULER API FUNCTIONS*/
/*************************/
/**
 * @brief:
 * @warning be aware to use a valid clockid_t
 */
PeriodicExecutor* PeriodicExecutorCreate(const char* _name, clockid_t _clockID);

void PeriodicExecutorDestroy(PeriodicExecutor* _executor);

/**
 */
int PeriodicExecutorAdd(PeriodicExecutor* _executor, TaskFunction _task, void* _context, int _period_ms);

size_t PeriodicExecutorRun(PeriodicExecutor* _executor);

size_t PeriodicExecutorPause(PeriodicExecutor* _executor);


