void run_on_cpu ( CPUState * cpu , void ( * func ) ( void * data ) , void * data ) {
 struct qemu_work_item wi ;
 if ( qemu_cpu_is_self ( cpu ) ) {
 func ( data ) ;
 return ;
 }
 wi . func = func ;
 wi . data = data ;
 if ( cpu -> queued_work_first == NULL ) {
 cpu -> queued_work_first = & wi ;
 }
 else {
 cpu -> queued_work_last -> next = & wi ;
 }
 cpu -> queued_work_last = & wi ;
 wi . next = NULL ;
 wi . done = false ;
 qemu_cpu_kick ( cpu ) ;
 while ( ! wi . done ) {
 CPUArchState * self_env = cpu_single_env ;
 qemu_cond_wait ( & qemu_work_cond , & qemu_global_mutex ) ;
 cpu_single_env = self_env ;
 }
 }