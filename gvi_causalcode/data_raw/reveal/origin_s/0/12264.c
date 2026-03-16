static int selinux_msg_queue_msgsnd ( struct msg_queue * msq , struct msg_msg * msg , int msqflg ) {
 struct ipc_security_struct * isec ;
 struct msg_security_struct * msec ;
 struct common_audit_data ad ;
 u32 sid = current_sid ( ) ;
 int rc ;
 isec = msq -> q_perm . security ;
 msec = msg -> security ;
 if ( msec -> sid == SECINITSID_UNLABELED ) {
 rc = security_transition_sid ( sid , isec -> sid , SECCLASS_MSG , NULL , & msec -> sid ) ;
 if ( rc ) return rc ;
 }
 ad . type = LSM_AUDIT_DATA_IPC ;
 ad . u . ipc_id = msq -> q_perm . key ;
 rc = avc_has_perm ( sid , isec -> sid , SECCLASS_MSGQ , MSGQ__WRITE , & ad ) ;
 if ( ! rc ) rc = avc_has_perm ( sid , msec -> sid , SECCLASS_MSG , MSG__SEND , & ad ) ;
 if ( ! rc ) rc = avc_has_perm ( msec -> sid , isec -> sid , SECCLASS_MSGQ , MSGQ__ENQUEUE , & ad ) ;
 return rc ;
 }