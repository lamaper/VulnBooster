static int selinux_setprocattr ( struct task_struct * p , char * name , void * value , size_t size ) {
 struct task_security_struct * tsec ;
 struct cred * new ;
 u32 sid = 0 , ptsid ;
 int error ;
 char * str = value ;
 if ( current != p ) {
 return - EACCES ;
 }
 if ( ! strcmp ( name , "exec" ) ) error = current_has_perm ( p , PROCESS__SETEXEC ) ;
 else if ( ! strcmp ( name , "fscreate" ) ) error = current_has_perm ( p , PROCESS__SETFSCREATE ) ;
 else if ( ! strcmp ( name , "keycreate" ) ) error = current_has_perm ( p , PROCESS__SETKEYCREATE ) ;
 else if ( ! strcmp ( name , "sockcreate" ) ) error = current_has_perm ( p , PROCESS__SETSOCKCREATE ) ;
 else if ( ! strcmp ( name , "current" ) ) error = current_has_perm ( p , PROCESS__SETCURRENT ) ;
 else error = - EINVAL ;
 if ( error ) return error ;
 if ( size && str [ 1 ] && str [ 1 ] != '\n' ) {
 if ( str [ size - 1 ] == '\n' ) {
 str [ size - 1 ] = 0 ;
 size -- ;
 }
 error = security_context_to_sid ( value , size , & sid , GFP_KERNEL ) ;
 if ( error == - EINVAL && ! strcmp ( name , "fscreate" ) ) {
 if ( ! capable ( CAP_MAC_ADMIN ) ) {
 struct audit_buffer * ab ;
 size_t audit_size ;
 if ( str [ size - 1 ] == '\0' ) audit_size = size - 1 ;
 else audit_size = size ;
 ab = audit_log_start ( current -> audit_context , GFP_ATOMIC , AUDIT_SELINUX_ERR ) ;
 audit_log_format ( ab , "op=fscreate invalid_context=" ) ;
 audit_log_n_untrustedstring ( ab , value , audit_size ) ;
 audit_log_end ( ab ) ;
 return error ;
 }
 error = security_context_to_sid_force ( value , size , & sid ) ;
 }
 if ( error ) return error ;
 }
 new = prepare_creds ( ) ;
 if ( ! new ) return - ENOMEM ;
 tsec = new -> security ;
 if ( ! strcmp ( name , "exec" ) ) {
 tsec -> exec_sid = sid ;
 }
 else if ( ! strcmp ( name , "fscreate" ) ) {
 tsec -> create_sid = sid ;
 }
 else if ( ! strcmp ( name , "keycreate" ) ) {
 error = may_create_key ( sid , p ) ;
 if ( error ) goto abort_change ;
 tsec -> keycreate_sid = sid ;
 }
 else if ( ! strcmp ( name , "sockcreate" ) ) {
 tsec -> sockcreate_sid = sid ;
 }
 else if ( ! strcmp ( name , "current" ) ) {
 error = - EINVAL ;
 if ( sid == 0 ) goto abort_change ;
 error = - EPERM ;
 if ( ! current_is_single_threaded ( ) ) {
 error = security_bounded_transition ( tsec -> sid , sid ) ;
 if ( error ) goto abort_change ;
 }
 error = avc_has_perm ( tsec -> sid , sid , SECCLASS_PROCESS , PROCESS__DYNTRANSITION , NULL ) ;
 if ( error ) goto abort_change ;
 ptsid = ptrace_parent_sid ( p ) ;
 if ( ptsid != 0 ) {
 error = avc_has_perm ( ptsid , sid , SECCLASS_PROCESS , PROCESS__PTRACE , NULL ) ;
 if ( error ) goto abort_change ;
 }
 tsec -> sid = sid ;
 }
 else {
 error = - EINVAL ;
 goto abort_change ;
 }
 commit_creds ( new ) ;
 return size ;
 abort_change : abort_creds ( new ) ;
 return error ;
 }