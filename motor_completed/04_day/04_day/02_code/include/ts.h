#ifndef _TS_H_
#define _TS_H_

#include <stdio.h>
#include "tslib.h"

int read_ts(struct ts_sample  *ts_p);
int close_ts();
#endif