char * kadmin_startup ( int argc , char * argv [ ] ) {
 extern char * optarg ;
 char * princstr = NULL , * keytab_name = NULL , * query = NULL ;
 char * password = NULL ;
 char * luser , * canon , * cp ;
 int optchar , freeprinc = 0 , use_keytab = 0 , use_anonymous = 0 ;
 struct passwd * pw ;
 kadm5_ret_t retval ;
 krb5_ccache cc ;
 krb5_principal princ ;
 kadm5_config_params params ;
 char * * db_args = NULL ;
 int db_args_size = 0 ;
 char * db_name = NULL ;
 char * svcname , * realm ;
 memset ( & params , 0 , sizeof ( params ) ) ;
 if ( strcmp ( whoami , "kadmin.local" ) == 0 ) set_com_err_hook ( extended_com_err_fn ) ;
 retval = kadm5_init_krb5_context ( & context ) ;
 if ( retval ) {
 com_err ( whoami , retval , _ ( "while initializing krb5 library" ) ) ;
 exit ( 1 ) ;
 }
 while ( ( optchar = getopt ( argc , argv , "x:r:p:knq:w:d:s:mc:t:e:ON" ) ) != EOF ) {
 switch ( optchar ) {
 case 'x' : db_args_size ++ ;
 db_args = realloc ( db_args , sizeof ( char * ) * ( db_args_size + 1 ) ) ;
 if ( db_args == NULL ) {
 fprintf ( stderr , _ ( "%s: Cannot initialize. Not enough memory\n" ) , argv [ 0 ] ) ;
 exit ( 1 ) ;
 }
 db_args [ db_args_size - 1 ] = optarg ;
 db_args [ db_args_size ] = NULL ;
 break ;
 case 'r' : def_realm = optarg ;
 break ;
 case 'p' : princstr = optarg ;
 break ;
 case 'c' : ccache_name = optarg ;
 break ;
 case 'k' : use_keytab ++ ;
 break ;
 case 'n' : use_anonymous ++ ;
 break ;
 case 't' : keytab_name = optarg ;
 break ;
 case 'w' : password = optarg ;
 break ;
 case 'q' : query = optarg ;
 break ;
 case 'd' : free ( db_name ) ;
 asprintf ( & db_name , "dbname=%s" , optarg ) ;
 db_args_size ++ ;
 db_args = realloc ( db_args , sizeof ( char * ) * ( db_args_size + 1 ) ) ;
 if ( db_args == NULL ) {
 fprintf ( stderr , _ ( "%s: Cannot initialize. Not enough memory\n" ) , argv [ 0 ] ) ;
 exit ( 1 ) ;
 }
 db_args [ db_args_size - 1 ] = db_name ;
 db_args [ db_args_size ] = NULL ;
 break ;
 case 's' : params . admin_server = optarg ;
 params . mask |= KADM5_CONFIG_ADMIN_SERVER ;
 break ;
 case 'm' : params . mkey_from_kbd = 1 ;
 params . mask |= KADM5_CONFIG_MKEY_FROM_KBD ;
 break ;
 case 'e' : retval = krb5_string_to_keysalts ( optarg , ", \t" , ":.-" , 0 , & params . keysalts , & params . num_keysalts ) ;
 if ( retval ) {
 com_err ( whoami , retval , _ ( "while parsing keysalts %s" ) , optarg ) ;
 exit ( 1 ) ;
 }
 params . mask |= KADM5_CONFIG_ENCTYPES ;
 break ;
 case 'O' : params . mask |= KADM5_CONFIG_OLD_AUTH_GSSAPI ;
 break ;
 case 'N' : params . mask |= KADM5_CONFIG_AUTH_NOFALLBACK ;
 break ;
 default : usage ( ) ;
 }
 }
 if ( ( ccache_name && use_keytab ) || ( keytab_name && ! use_keytab ) || ( ccache_name && use_anonymous ) || ( use_anonymous && use_keytab ) ) usage ( ) ;
 if ( def_realm == NULL && krb5_get_default_realm ( context , & def_realm ) ) {
 fprintf ( stderr , _ ( "%s: unable to get default realm\n" ) , whoami ) ;
 exit ( 1 ) ;
 }
 params . mask |= KADM5_CONFIG_REALM ;
 params . realm = def_realm ;
 if ( params . mask & KADM5_CONFIG_OLD_AUTH_GSSAPI ) svcname = KADM5_ADMIN_SERVICE ;
 else svcname = NULL ;
 if ( ccache_name == NULL ) {
 retval = krb5_cc_default ( context , & cc ) ;
 if ( retval ) {
 com_err ( whoami , retval , _ ( "while opening default credentials cache" ) ) ;
 exit ( 1 ) ;
 }
 }
 else {
 retval = krb5_cc_resolve ( context , ccache_name , & cc ) ;
 if ( retval ) {
 com_err ( whoami , retval , _ ( "while opening credentials cache %s" ) , ccache_name ) ;
 exit ( 1 ) ;
 }
 }
 if ( princstr == NULL ) {
 if ( ccache_name != NULL && ! krb5_cc_get_principal ( context , cc , & princ ) ) {
 retval = krb5_unparse_name ( context , princ , & princstr ) ;
 if ( retval ) {
 com_err ( whoami , retval , _ ( "while canonicalizing principal name" ) ) ;
 exit ( 1 ) ;
 }
 krb5_free_principal ( context , princ ) ;
 freeprinc ++ ;
 }
 else if ( use_keytab != 0 ) {
 retval = krb5_sname_to_principal ( context , NULL , "host" , KRB5_NT_SRV_HST , & princ ) ;
 if ( retval ) {
 com_err ( whoami , retval , _ ( "creating host service principal" ) ) ;
 exit ( 1 ) ;
 }
 retval = krb5_unparse_name ( context , princ , & princstr ) ;
 if ( retval ) {
 com_err ( whoami , retval , _ ( "while canonicalizing principal name" ) ) ;
 exit ( 1 ) ;
 }
 krb5_free_principal ( context , princ ) ;
 freeprinc ++ ;
 }
 else if ( ! krb5_cc_get_principal ( context , cc , & princ ) ) {
 if ( krb5_unparse_name ( context , princ , & canon ) ) {
 fprintf ( stderr , _ ( "%s: unable to canonicalize principal\n" ) , whoami ) ;
 exit ( 1 ) ;
 }
 realm = strchr ( canon , '@' ) ;
 while ( realm ) {
 if ( realm > canon && * ( realm - 1 ) != '\\' ) break ;
 realm = strchr ( realm + 1 , '@' ) ;
 }
 if ( realm ) * realm ++ = '\0' ;
 cp = strchr ( canon , '/' ) ;
 while ( cp ) {
 if ( cp > canon && * ( cp - 1 ) != '\\' ) break ;
 cp = strchr ( cp + 1 , '/' ) ;
 }
 if ( cp != NULL ) * cp = '\0' ;
 if ( asprintf ( & princstr , "%s/admin%s%s" , canon , ( realm ) ? "@" : "" , ( realm ) ? realm : "" ) < 0 ) {
 fprintf ( stderr , _ ( "%s: out of memory\n" ) , whoami ) ;
 exit ( 1 ) ;
 }
 free ( canon ) ;
 krb5_free_principal ( context , princ ) ;
 freeprinc ++ ;
 }
 else if ( ( luser = getenv ( "USER" ) ) ) {
 if ( asprintf ( & princstr , "%s/admin@%s" , luser , def_realm ) < 0 ) {
 fprintf ( stderr , _ ( "%s: out of memory\n" ) , whoami ) ;
 exit ( 1 ) ;
 }
 freeprinc ++ ;
 }
 else if ( ( pw = getpwuid ( getuid ( ) ) ) ) {
 if ( asprintf ( & princstr , "%s/admin@%s" , pw -> pw_name , def_realm ) < 0 ) {
 fprintf ( stderr , _ ( "%s: out of memory\n" ) , whoami ) ;
 exit ( 1 ) ;
 }
 freeprinc ++ ;
 }
 else {
 fprintf ( stderr , _ ( "%s: unable to figure out a principal name\n" ) , whoami ) ;
 exit ( 1 ) ;
 }
 }
 retval = krb5_klog_init ( context , "admin_server" , whoami , 0 ) ;
 if ( retval ) {
 com_err ( whoami , retval , _ ( "while setting up logging" ) ) ;
 exit ( 1 ) ;
 }
 if ( ccache_name ) {
 printf ( _ ( "Authenticating as principal %s with existing " "credentials.\n" ) , princstr ) ;
 retval = kadm5_init_with_creds ( context , princstr , cc , svcname , & params , KADM5_STRUCT_VERSION , KADM5_API_VERSION_4 , db_args , & handle ) ;
 }
 else if ( use_anonymous ) {
 printf ( _ ( "Authenticating as principal %s with password;
 " "anonymous requested.\n" ) , princstr ) ;
 retval = kadm5_init_anonymous ( context , princstr , svcname , & params , KADM5_STRUCT_VERSION , KADM5_API_VERSION_4 , db_args , & handle ) ;
 }
 else if ( use_keytab ) {
 if ( keytab_name ) printf ( _ ( "Authenticating as principal %s with keytab %s.\n" ) , princstr , keytab_name ) ;
 else printf ( _ ( "Authenticating as principal %s with default keytab.\n" ) , princstr ) ;
 retval = kadm5_init_with_skey ( context , princstr , keytab_name , svcname , & params , KADM5_STRUCT_VERSION , KADM5_API_VERSION_4 , db_args , & handle ) ;
 }
 else {
 printf ( _ ( "Authenticating as principal %s with password.\n" ) , princstr ) ;
 retval = kadm5_init_with_password ( context , princstr , password , svcname , & params , KADM5_STRUCT_VERSION , KADM5_API_VERSION_4 , db_args , & handle ) ;
 }
 if ( retval ) {
 com_err ( whoami , retval , _ ( "while initializing %s interface" ) , whoami ) ;
 if ( retval == KADM5_BAD_CLIENT_PARAMS || retval == KADM5_BAD_SERVER_PARAMS ) usage ( ) ;
 exit ( 1 ) ;
 }
 if ( freeprinc ) free ( princstr ) ;
 free ( db_name ) ;
 free ( db_args ) ;
 retval = krb5_cc_close ( context , cc ) ;
 if ( retval ) {
 com_err ( whoami , retval , _ ( "while closing ccache %s" ) , ccache_name ) ;
 exit ( 1 ) ;
 }
 retval = kadm5_init_iprop ( handle , 0 ) ;
 if ( retval ) {
 com_err ( whoami , retval , _ ( "while mapping update log" ) ) ;
 exit ( 1 ) ;
 }
 return query ;
 }