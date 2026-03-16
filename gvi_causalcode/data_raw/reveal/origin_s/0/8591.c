static int selinux_bprm_set_creds ( struct linux_binprm * bprm ) {
 const struct task_security_struct * old_tsec ;
 struct task_security_struct * new_tsec ;
 struct inode_security_struct * isec ;
 struct common_audit_data ad ;
 struct inode * inode = file_inode ( bprm -> file ) ;
 int rc ;
 if ( bprm -> cred_prepared ) return 0 ;
 old_tsec = current_security ( ) ;
 new_tsec = bprm -> cred -> security ;
 isec = inode_security ( inode ) ;
 new_tsec -> sid = old_tsec -> sid ;
 new_tsec -> osid = old_tsec -> sid ;
 new_tsec -> create_sid = 0 ;
 new_tsec -> keycreate_sid = 0 ;
 new_tsec -> sockcreate_sid = 0 ;
 if ( old_tsec -> exec_sid ) {
 new_tsec -> sid = old_tsec -> exec_sid ;
 new_tsec -> exec_sid = 0 ;
 rc = check_nnp_nosuid ( bprm , old_tsec , new_tsec ) ;
 if ( rc ) return rc ;
 }
 else {
 rc = security_transition_sid ( old_tsec -> sid , isec -> sid , SECCLASS_PROCESS , NULL , & new_tsec -> sid ) ;
 if ( rc ) return rc ;
 rc = check_nnp_nosuid ( bprm , old_tsec , new_tsec ) ;
 if ( rc ) new_tsec -> sid = old_tsec -> sid ;
 }
 ad . type = LSM_AUDIT_DATA_FILE ;
 ad . u . file = bprm -> file ;
 if ( new_tsec -> sid == old_tsec -> sid ) {
 rc = avc_has_perm ( old_tsec -> sid , isec -> sid , SECCLASS_FILE , FILE__EXECUTE_NO_TRANS , & ad ) ;
 if ( rc ) return rc ;
 }
 else {
 rc = avc_has_perm ( old_tsec -> sid , new_tsec -> sid , SECCLASS_PROCESS , PROCESS__TRANSITION , & ad ) ;
 if ( rc ) return rc ;
 rc = avc_has_perm ( new_tsec -> sid , isec -> sid , SECCLASS_FILE , FILE__ENTRYPOINT , & ad ) ;
 if ( rc ) return rc ;
 if ( bprm -> unsafe & LSM_UNSAFE_SHARE ) {
 rc = avc_has_perm ( old_tsec -> sid , new_tsec -> sid , SECCLASS_PROCESS , PROCESS__SHARE , NULL ) ;
 if ( rc ) return - EPERM ;
 }
 if ( bprm -> unsafe & ( LSM_UNSAFE_PTRACE | LSM_UNSAFE_PTRACE_CAP ) ) {
 u32 ptsid = ptrace_parent_sid ( current ) ;
 if ( ptsid != 0 ) {
 rc = avc_has_perm ( ptsid , new_tsec -> sid , SECCLASS_PROCESS , PROCESS__PTRACE , NULL ) ;
 if ( rc ) return - EPERM ;
 }
 }
 bprm -> per_clear |= PER_CLEAR_ON_SETID ;
 }
 return 0 ;
 }