static void selinux_bprm_committed_creds ( struct linux_binprm * bprm ) {
 const struct task_security_struct * tsec = current_security ( ) ;
 struct itimerval itimer ;
 u32 osid , sid ;
 int rc , i ;
 osid = tsec -> osid ;
 sid = tsec -> sid ;
 if ( sid == osid ) return ;
 rc = avc_has_perm ( osid , sid , SECCLASS_PROCESS , PROCESS__SIGINH , NULL ) ;
 if ( rc ) {
 if ( IS_ENABLED ( CONFIG_POSIX_TIMERS ) ) {
 memset ( & itimer , 0 , sizeof itimer ) ;
 for ( i = 0 ;
 i < 3 ;
 i ++ ) do_setitimer ( i , & itimer , NULL ) ;
 }
 spin_lock_irq ( & current -> sighand -> siglock ) ;
 if ( ! fatal_signal_pending ( current ) ) {
 flush_sigqueue ( & current -> pending ) ;
 flush_sigqueue ( & current -> signal -> shared_pending ) ;
 flush_signal_handlers ( current , 1 ) ;
 sigemptyset ( & current -> blocked ) ;
 recalc_sigpending ( ) ;
 }
 spin_unlock_irq ( & current -> sighand -> siglock ) ;
 }
 read_lock ( & tasklist_lock ) ;
 __wake_up_parent ( current , current -> real_parent ) ;
 read_unlock ( & tasklist_lock ) ;
 }