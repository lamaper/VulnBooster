void kadmin_cpw ( int argc , char * argv [ ] ) {
 kadm5_ret_t retval ;
 static char newpw [ 1024 ] ;
 static char prompt1 [ 1024 ] , prompt2 [ 1024 ] ;
 char * canon = NULL , * pwarg = NULL ;
 int n_ks_tuple = 0 , randkey = 0 ;
 krb5_boolean keepold = FALSE ;
 krb5_key_salt_tuple * ks_tuple = NULL ;
 krb5_principal princ = NULL ;
 char * * db_args = NULL ;
 int db_args_size = 0 ;
 if ( argc < 2 ) {
 cpw_usage ( NULL ) ;
 return ;
 }
 for ( argv ++ , argc -- ;
 argc > 1 ;
 argc -- , argv ++ ) {
 if ( ! strcmp ( "-x" , * argv ) ) {
 argc -- ;
 if ( argc < 1 ) {
 cpw_usage ( _ ( "change_password: missing db argument" ) ) ;
 goto cleanup ;
 }
 db_args_size ++ ;
 db_args = realloc ( db_args , sizeof ( char * ) * ( db_args_size + 1 ) ) ;
 if ( db_args == NULL ) {
 fprintf ( stderr , _ ( "change_password: Not enough memory\n" ) ) ;
 exit ( 1 ) ;
 }
 db_args [ db_args_size - 1 ] = * ++ argv ;
 db_args [ db_args_size ] = NULL ;
 }
 else if ( ! strcmp ( "-pw" , * argv ) ) {
 argc -- ;
 if ( argc < 1 ) {
 cpw_usage ( _ ( "change_password: missing password arg" ) ) ;
 goto cleanup ;
 }
 pwarg = * ++ argv ;
 }
 else if ( ! strcmp ( "-randkey" , * argv ) ) {
 randkey ++ ;
 }
 else if ( ! strcmp ( "-keepold" , * argv ) ) {
 keepold = TRUE ;
 }
 else if ( ! strcmp ( "-e" , * argv ) ) {
 argc -- ;
 if ( argc < 1 ) {
 cpw_usage ( _ ( "change_password: missing keysaltlist arg" ) ) ;
 goto cleanup ;
 }
 retval = krb5_string_to_keysalts ( * ++ argv , ", \t" , ":.-" , 0 , & ks_tuple , & n_ks_tuple ) ;
 if ( retval ) {
 com_err ( "change_password" , retval , _ ( "while parsing keysalts %s" ) , * argv ) ;
 goto cleanup ;
 }
 }
 else {
 cpw_usage ( NULL ) ;
 goto cleanup ;
 }
 }
 if ( * argv == NULL ) {
 com_err ( "change_password" , 0 , _ ( "missing principal name" ) ) ;
 cpw_usage ( NULL ) ;
 goto cleanup ;
 }
 retval = kadmin_parse_name ( * argv , & princ ) ;
 if ( retval ) {
 com_err ( "change_password" , retval , _ ( "while parsing principal name" ) ) ;
 goto cleanup ;
 }
 retval = krb5_unparse_name ( context , princ , & canon ) ;
 if ( retval ) {
 com_err ( "change_password" , retval , _ ( "while canonicalizing principal" ) ) ;
 goto cleanup ;
 }
 if ( pwarg != NULL ) {
 if ( keepold || ks_tuple != NULL ) {
 retval = kadm5_chpass_principal_3 ( handle , princ , keepold , n_ks_tuple , ks_tuple , pwarg ) ;
 }
 else {
 retval = kadm5_chpass_principal ( handle , princ , pwarg ) ;
 }
 if ( retval ) {
 com_err ( "change_password" , retval , _ ( "while changing password for \"%s\"." ) , canon ) ;
 goto cleanup ;
 }
 printf ( _ ( "Password for \"%s\" changed.\n" ) , canon ) ;
 }
 else if ( randkey ) {
 retval = randkey_princ ( princ , keepold , n_ks_tuple , ks_tuple ) ;
 if ( retval ) {
 com_err ( "change_password" , retval , _ ( "while randomizing key for \"%s\"." ) , canon ) ;
 goto cleanup ;
 }
 printf ( _ ( "Key for \"%s\" randomized.\n" ) , canon ) ;
 }
 else {
 unsigned int i = sizeof ( newpw ) - 1 ;
 snprintf ( prompt1 , sizeof ( prompt1 ) , _ ( "Enter password for principal \"%s\"" ) , canon ) ;
 snprintf ( prompt2 , sizeof ( prompt2 ) , _ ( "Re-enter password for principal \"%s\"" ) , canon ) ;
 retval = krb5_read_password ( context , prompt1 , prompt2 , newpw , & i ) ;
 if ( retval ) {
 com_err ( "change_password" , retval , _ ( "while reading password for \"%s\"." ) , canon ) ;
 goto cleanup ;
 }
 if ( keepold || ks_tuple != NULL ) {
 retval = kadm5_chpass_principal_3 ( handle , princ , keepold , n_ks_tuple , ks_tuple , newpw ) ;
 }
 else {
 retval = kadm5_chpass_principal ( handle , princ , newpw ) ;
 }
 memset ( newpw , 0 , sizeof ( newpw ) ) ;
 if ( retval ) {
 com_err ( "change_password" , retval , _ ( "while changing password for \"%s\"." ) , canon ) ;
 goto cleanup ;
 }
 printf ( _ ( "Password for \"%s\" changed.\n" ) , canon ) ;
 }
 cleanup : free ( canon ) ;
 free ( db_args ) ;
 krb5_free_principal ( context , princ ) ;
 free ( ks_tuple ) ;
 }