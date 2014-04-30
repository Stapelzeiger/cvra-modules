#ifndef TRACE_H
#define TRACE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct trace_var_s trace_var_t;

struct trace_var_s {
    bool trace_en;
    const char *name;
    float last_val;
    trace_var_t *next;
};

void trace_init(void);
void trace_var_add(trace_var_t *v, const char *name);
void trace_var_delete(trace_var_t *v);
void trace_var_enable(trace_var_t *v);
void trace_var_disable(trace_var_t *v);
void trace_var_disable_all(void);
void trace_var_update(trace_var_t *t, float val);
char *trace_var_output(void);
trace_var_t *trace_var_lookup(const char *name);

#endif // TRACE_H
