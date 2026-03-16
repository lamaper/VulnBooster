static int selinux_file_send_sigiotask ( struct task_struct * tsk , struct fown_struct * fown , int signum ) {
 struct file * file ;
 u32 sid = task_sid ( tsk ) ;
 u32 perm ;
 struct file_security_struct * fsec ;
 file = container_of ( fown , struct file , f_owner ) ;
 fsec = file -> f_security ;
 if ( ! signum ) perm = signal_to_av ( SIGIO ) ;
 else perm = signal_to_av ( signum ) ;
 return avc_has_perm ( fsec -> fown_sid , sid , SECCLASS_PROCESS , perm , NULL ) ;
 }