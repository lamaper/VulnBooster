void kadmin_modpol ( int argc , char * argv [ ] ) {
 krb5_error_code retval ;
 long mask ;
 kadm5_policy_ent_rec policy ;
 memset ( & policy , 0 , sizeof ( policy ) ) ;
 if ( kadmin_parse_policy_args ( argc , argv , & policy , & mask , "modify_policy" ) ) {
 kadmin_addmodpol_usage ( "modify_policy" ) ;
 return ;
 }
 policy . policy = argv [ argc - 1 ] ;
 retval = kadm5_modify_policy ( handle , & policy , mask ) ;
 if ( retval ) {
 com_err ( "modify_policy" , retval , _ ( "while modifying policy \"%s\"." ) , policy . policy ) ;
 }
 }