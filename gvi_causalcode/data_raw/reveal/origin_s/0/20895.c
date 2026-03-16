static int selinux_task_setrlimit ( struct task_struct * p , unsigned int resource , struct rlimit * new_rlim ) {
 struct rlimit * old_rlim = p -> signal -> rlim + resource ;
 if ( old_rlim -> rlim_max != new_rlim -> rlim_max ) return current_has_perm ( p , PROCESS__SETRLIMIT ) ;
 return 0 ;
 }