static void kadmin_modprinc_usage ( ) {
 fprintf ( stderr , _ ( "usage: modify_principal [options] principal\n" ) ) ;
 fprintf ( stderr , _ ( "\toptions are:\n" ) ) ;
 fprintf ( stderr , _ ( "\t\t[-x db_princ_args]* [-expire expdate] " "[-pwexpire pwexpdate] [-maxlife maxtixlife]\n" "\t\t[-kvno kvno] [-policy policy] [-clearpolicy]\n" "\t\t[-maxrenewlife maxrenewlife] [-unlock] " "[{
+|-}
attribute]\n" ) ) ;
 fprintf ( stderr , "\tattributes are:\n" ) ;
 fprintf ( stderr , _ ( "\t\tallow_postdated allow_forwardable allow_tgs_req " "allow_renewable\n" "\t\tallow_proxiable allow_dup_skey allow_tix " "requires_preauth\n" "\t\trequires_hwauth needchange allow_svr " "password_changing_service\n" "\t\tok_as_delegate ok_to_auth_as_delegate " "no_auth_data_required\n" "\nwhere,\n\t[-x db_princ_args]* - any number of database " "specific arguments.\n" "\t\t\tLook at each database documentation for supported " "arguments\n" ) ) ;
 }