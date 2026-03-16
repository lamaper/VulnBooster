static int selinux_bprm_secureexec ( struct linux_binprm * bprm ) {
 const struct task_security_struct * tsec = current_security ( ) ;
 u32 sid , osid ;
 int atsecure = 0 ;
 sid = tsec -> sid ;
 osid = tsec -> osid ;
 if ( osid != sid ) {
 atsecure = avc_has_perm ( osid , sid , SECCLASS_PROCESS , PROCESS__NOATSECURE , NULL ) ;
 }
 return ! ! atsecure ;
 }