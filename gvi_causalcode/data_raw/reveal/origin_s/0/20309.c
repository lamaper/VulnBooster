static struct passwd * check_user ( const char * user ) {

 uid_t user_id = geteuid ( ) ;
 if ( user_id ) {
 if ( user ) {
 tmp_user_info = getpwnam ( user ) ;
 if ( ( ! tmp_user_info || user_id != tmp_user_info -> pw_uid ) && global_system_variables . log_warnings ) sql_print_warning ( "One can only use the --user switch if running as root\n" ) ;
 }
 return NULL ;
 }
 if ( ! user ) {
 if ( ! opt_bootstrap && ! opt_help ) {
 sql_print_error ( "Fatal error: Please consult the Knowledge Base " "to find out how to run mysqld as root!\n" ) ;
 unireg_abort ( 1 ) ;
 }
 return NULL ;
 }
 if ( ! strcmp ( user , "root" ) ) return NULL ;
 if ( ! ( tmp_user_info = getpwnam ( user ) ) ) {
 const char * pos ;
 for ( pos = user ;
 my_isdigit ( mysqld_charset , * pos ) ;
 pos ++ ) ;
 if ( * pos ) goto err ;
 if ( ! ( tmp_user_info = getpwuid ( atoi ( user ) ) ) ) goto err ;
 }
 return tmp_user_info ;
 err : sql_print_error ( "Fatal error: Can't change to run as user '%s' ;
 Please check that the user exists!\n" , user ) ;
 unireg_abort ( 1 ) ;

 }