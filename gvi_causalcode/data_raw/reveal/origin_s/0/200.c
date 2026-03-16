void kadmin_unlock ( int argc , char * argv [ ] ) {
 kadm5_ret_t retval ;
 if ( ! locked ) return ;
 retval = kadm5_unlock ( handle ) ;
 if ( retval ) {
 com_err ( "unlock" , retval , "" ) ;
 return ;
 }
 locked = 0 ;
 }