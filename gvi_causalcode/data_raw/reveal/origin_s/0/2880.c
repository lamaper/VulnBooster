static void selinux_bprm_committing_creds ( struct linux_binprm * bprm ) {
 struct task_security_struct * new_tsec ;
 struct rlimit * rlim , * initrlim ;
 int rc , i ;
 new_tsec = bprm -> cred -> security ;
 if ( new_tsec -> sid == new_tsec -> osid ) return ;
 flush_unauthorized_files ( bprm -> cred , current -> files ) ;
 current -> pdeath_signal = 0 ;
 rc = avc_has_perm ( new_tsec -> osid , new_tsec -> sid , SECCLASS_PROCESS , PROCESS__RLIMITINH , NULL ) ;
 if ( rc ) {
 task_lock ( current ) ;
 for ( i = 0 ;
 i < RLIM_NLIMITS ;
 i ++ ) {
 rlim = current -> signal -> rlim + i ;
 initrlim = init_task . signal -> rlim + i ;
 rlim -> rlim_cur = min ( rlim -> rlim_max , initrlim -> rlim_cur ) ;
 }
 task_unlock ( current ) ;
 if ( IS_ENABLED ( CONFIG_POSIX_TIMERS ) ) update_rlimit_cpu ( current , rlimit ( RLIMIT_CPU ) ) ;
 }
 }