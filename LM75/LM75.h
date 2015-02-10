#ifndef _LM75_H
#define _LM75_H

#include <project.h>
#include <stdio.h>
#include <stdlib.h>

#define LM75_BASE_ADDRESS 0x48

enum temperatur_part {LOW = 0, HIGH = 1};
    
typedef struct LM75 *LM75_t;

LM75_t Create_LM75(size_t id);

void LM75_poll(LM75_t lm);

int16 LM75_temperature(LM75_t lm);

#endif
