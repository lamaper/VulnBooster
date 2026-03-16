static int check_nnp_nosuid ( const struct linux_binprm * bprm , const struct task_security_struct * old_tsec , const struct task_security_struct * new_tsec ) {
 int nnp = ( bprm -> unsafe & LSM_UNSAFE_NO_NEW_PRIVS ) ;
 int nosuid = ! mnt_may_suid ( bprm -> file -> f_path . mnt ) ;
 int rc ;
 if ( ! nnp && ! nosuid ) return 0 ;
 if ( new_tsec -> sid == old_tsec -> sid ) return 0 ;
 rc = security_bounded_transition ( old_tsec -> sid , new_tsec -> sid ) ;
 if ( rc ) {
 if ( nnp ) return - EPERM ;
 else return - EACCES ;
 }
 return 0 ;
 }