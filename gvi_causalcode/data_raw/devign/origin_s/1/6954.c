static inline void gdb_continue(GDBState *s)

{


    s->running_state = 1;


    vm_start();


}
