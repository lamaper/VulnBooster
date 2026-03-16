static inline int handle_cpu_signal ( uintptr_t pc , unsigned long address , int is_write , sigset_t * old_set , void * puc ) {
 CPUArchState * env ;
 int ret ;


 return 1 ;
 }
 env = current_cpu -> env_ptr ;
 ret = cpu_handle_mmu_fault ( env , address , is_write , MMU_USER_IDX ) ;
 if ( ret < 0 ) {
 return 0 ;
 }
 if ( ret == 0 ) {
 return 1 ;
 }
 cpu_restore_state ( env , pc ) ;
 sigprocmask ( SIG_SETMASK , old_set , NULL ) ;
 exception_action ( env ) ;
 return 1 ;
 }