#pragma once

#define INTERRUPT_PRIORITY(X)								( (X & 0x7) << 5)

typedef unsigned int										Priority_T;
