void kadmin_addpol ( int argc , char * argv [ ] ) {
 krb5_error_code retval ;
 long mask ;
 kadm5_policy_ent_rec policy ;
 memset ( & policy , 0 , sizeof ( policy ) ) ;
 if ( kadmin_parse_policy_args ( argc , argv , & policy , & mask , "add_policy" ) ) {
 kadmin_addmodpol_usage ( "add_policy" ) ;
 return ;
 }
 policy . policy = argv [ argc - 1 ] ;
 mask |= KADM5_POLICY ;
 retval = kadm5_create_policy ( handle , & policy , mask ) ;
 if ( retval ) {
 com_err ( "add_policy" , retval , _ ( "while creating policy \"%s\"." ) , policy . policy ) ;
 }
 }