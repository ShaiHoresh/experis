#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "pdu.h"

CDRData CDRGenerator(int _index);

void CDRprint(CDRData _dt);

#endif /* #ifndef __PROCESSOR_H__ */
