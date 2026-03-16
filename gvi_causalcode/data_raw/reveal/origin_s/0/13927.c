static inline u32 signal_to_av ( int sig ) {
 u32 perm = 0 ;
 switch ( sig ) {
 case SIGCHLD : perm = PROCESS__SIGCHLD ;
 break ;
 case SIGKILL : perm = PROCESS__SIGKILL ;
 break ;
 case SIGSTOP : perm = PROCESS__SIGSTOP ;
 break ;
 default : perm = PROCESS__SIGNAL ;
 break ;
 }
 return perm ;
 }