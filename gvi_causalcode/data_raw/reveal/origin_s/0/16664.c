static int kadmin_parse_princ_args ( int argc , char * argv [ ] , kadm5_principal_ent_t oprinc , long * mask , char * * pass , krb5_boolean * randkey , krb5_key_salt_tuple * * ks_tuple , int * n_ks_tuple , char * caller ) {
 int i , attrib_set ;
 size_t j ;
 time_t date ;
 time_t now ;
 krb5_error_code retval ;
 * mask = 0 ;
 * pass = NULL ;
 * n_ks_tuple = 0 ;
 * ks_tuple = NULL ;
 time ( & now ) ;
 * randkey = FALSE ;
 for ( i = 1 ;
 i < argc - 1 ;
 i ++ ) {
 attrib_set = 0 ;
 if ( ! strcmp ( "-x" , argv [ i ] ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 add_tl_data ( & oprinc -> n_tl_data , & oprinc -> tl_data , KRB5_TL_DB_ARGS , strlen ( argv [ i ] ) + 1 , ( krb5_octet * ) argv [ i ] ) ;
 * mask |= KADM5_TL_DATA ;
 continue ;
 }
 if ( ! strcmp ( "-expire" , argv [ i ] ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 date = get_date ( argv [ i ] ) ;
 if ( date == ( time_t ) - 1 ) {
 fprintf ( stderr , _ ( "Invalid date specification \"%s\".\n" ) , argv [ i ] ) ;
 return - 1 ;
 }
 oprinc -> princ_expire_time = date ;
 * mask |= KADM5_PRINC_EXPIRE_TIME ;
 continue ;
 }
 if ( ! strcmp ( "-pwexpire" , argv [ i ] ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 date = get_date ( argv [ i ] ) ;
 if ( date == ( time_t ) - 1 ) {
 fprintf ( stderr , _ ( "Invalid date specification \"%s\".\n" ) , argv [ i ] ) ;
 return - 1 ;
 }
 oprinc -> pw_expiration = date ;
 * mask |= KADM5_PW_EXPIRATION ;
 continue ;
 }
 if ( ! strcmp ( "-maxlife" , argv [ i ] ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 date = get_date ( argv [ i ] ) ;
 if ( date == ( time_t ) - 1 ) {
 fprintf ( stderr , _ ( "Invalid date specification \"%s\".\n" ) , argv [ i ] ) ;
 return - 1 ;
 }
 oprinc -> max_life = date - now ;
 * mask |= KADM5_MAX_LIFE ;
 continue ;
 }
 if ( ! strcmp ( "-maxrenewlife" , argv [ i ] ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 date = get_date ( argv [ i ] ) ;
 if ( date == ( time_t ) - 1 ) {
 fprintf ( stderr , _ ( "Invalid date specification \"%s\".\n" ) , argv [ i ] ) ;
 return - 1 ;
 }
 oprinc -> max_renewable_life = date - now ;
 * mask |= KADM5_MAX_RLIFE ;
 continue ;
 }
 if ( ! strcmp ( "-kvno" , argv [ i ] ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 oprinc -> kvno = atoi ( argv [ i ] ) ;
 * mask |= KADM5_KVNO ;
 continue ;
 }
 if ( ! strcmp ( "-policy" , argv [ i ] ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 oprinc -> policy = argv [ i ] ;
 * mask |= KADM5_POLICY ;
 continue ;
 }
 if ( ! strcmp ( "-clearpolicy" , argv [ i ] ) ) {
 oprinc -> policy = NULL ;
 * mask |= KADM5_POLICY_CLR ;
 continue ;
 }
 if ( ! strcmp ( "-pw" , argv [ i ] ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 * pass = argv [ i ] ;
 continue ;
 }
 if ( ! strcmp ( "-randkey" , argv [ i ] ) ) {
 * randkey = TRUE ;
 continue ;
 }
 if ( ! strcmp ( "-unlock" , argv [ i ] ) ) {
 unlock_princ ( oprinc , mask , caller ) ;
 continue ;
 }
 if ( ! strcmp ( "-e" , argv [ i ] ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 retval = krb5_string_to_keysalts ( argv [ i ] , ", \t" , ":.-" , 0 , ks_tuple , n_ks_tuple ) ;
 if ( retval ) {
 com_err ( caller , retval , _ ( "while parsing keysalts %s" ) , argv [ i ] ) ;
 return - 1 ;
 }
 continue ;
 }
 for ( j = 0 ;
 j < sizeof ( flags ) / sizeof ( struct pflag ) ;
 j ++ ) {
 if ( strlen ( argv [ i ] ) == flags [ j ] . flaglen + 1 && ! strcmp ( flags [ j ] . flagname , & argv [ i ] [ 1 ] ) ) {
 if ( ( flags [ j ] . set && argv [ i ] [ 0 ] == '-' ) || ( ! flags [ j ] . set && argv [ i ] [ 0 ] == '+' ) ) {
 oprinc -> attributes |= flags [ j ] . theflag ;
 * mask |= KADM5_ATTRIBUTES ;
 attrib_set ++ ;
 break ;
 }
 else if ( ( flags [ j ] . set && argv [ i ] [ 0 ] == '+' ) || ( ! flags [ j ] . set && argv [ i ] [ 0 ] == '-' ) ) {
 oprinc -> attributes &= ~ flags [ j ] . theflag ;
 * mask |= KADM5_ATTRIBUTES ;
 attrib_set ++ ;
 break ;
 }
 else {
 return - 1 ;
 }
 }
 }
 if ( ! attrib_set ) return - 1 ;
 }
 if ( i != argc - 1 ) return - 1 ;
 retval = kadmin_parse_name ( argv [ i ] , & oprinc -> principal ) ;
 if ( retval ) {
 com_err ( caller , retval , _ ( "while parsing principal" ) ) ;
 return - 1 ;
 }
 return 0 ;
 }