void kadmin_lock ( int argc , char * argv [ ] ) {
 kadm5_ret_t retval ;
 if ( locked ) return ;
 retval = kadm5_lock ( handle ) ;
 if ( retval ) {
 com_err ( "lock" , retval , "" ) ;
 return ;
 }
 locked = 1 ;
 }