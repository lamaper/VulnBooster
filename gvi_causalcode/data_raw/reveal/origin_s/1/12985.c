static inline int handle_cpu_signal ( uintptr_t pc , unsigned long address , int is_write , sigset_t * old_set , void * puc ) {
 int ret ;


 return 1 ;
 }
 ret = cpu_handle_mmu_fault ( cpu_single_env , address , is_write , MMU_USER_IDX ) ;
 if ( ret < 0 ) {
 return 0 ;
 }
 if ( ret == 0 ) {
 return 1 ;
 }
 cpu_restore_state ( cpu_single_env , pc ) ;
 sigprocmask ( SIG_SETMASK , old_set , NULL ) ;
 exception_action ( cpu_single_env ) ;
 return 1 ;
 }