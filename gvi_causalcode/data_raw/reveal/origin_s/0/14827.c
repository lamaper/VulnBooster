static int kadmin_parse_policy_args ( int argc , char * argv [ ] , kadm5_policy_ent_t policy , long * mask , char * caller ) {
 krb5_error_code retval ;
 int i ;
 time_t now , date ;
 time ( & now ) ;
 * mask = 0 ;
 for ( i = 1 ;
 i < argc - 1 ;
 i ++ ) {
 if ( ! strcmp ( argv [ i ] , "-maxlife" ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 date = get_date ( argv [ i ] ) ;
 if ( date == ( time_t ) - 1 ) {
 fprintf ( stderr , _ ( "Invalid date specification \"%s\".\n" ) , argv [ i ] ) ;
 return - 1 ;
 }
 policy -> pw_max_life = date - now ;
 * mask |= KADM5_PW_MAX_LIFE ;
 continue ;
 }
 else if ( ! strcmp ( argv [ i ] , "-minlife" ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 date = get_date ( argv [ i ] ) ;
 if ( date == ( time_t ) - 1 ) {
 fprintf ( stderr , _ ( "Invalid date specification \"%s\".\n" ) , argv [ i ] ) ;
 return - 1 ;
 }
 policy -> pw_min_life = date - now ;
 * mask |= KADM5_PW_MIN_LIFE ;
 continue ;
 }
 else if ( ! strcmp ( argv [ i ] , "-minlength" ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 policy -> pw_min_length = atoi ( argv [ i ] ) ;
 * mask |= KADM5_PW_MIN_LENGTH ;
 continue ;
 }
 else if ( ! strcmp ( argv [ i ] , "-minclasses" ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 policy -> pw_min_classes = atoi ( argv [ i ] ) ;
 * mask |= KADM5_PW_MIN_CLASSES ;
 continue ;
 }
 else if ( ! strcmp ( argv [ i ] , "-history" ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 policy -> pw_history_num = atoi ( argv [ i ] ) ;
 * mask |= KADM5_PW_HISTORY_NUM ;
 continue ;
 }
 else if ( strlen ( argv [ i ] ) == 11 && ! strcmp ( argv [ i ] , "-maxfailure" ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 policy -> pw_max_fail = atoi ( argv [ i ] ) ;
 * mask |= KADM5_PW_MAX_FAILURE ;
 continue ;
 }
 else if ( strlen ( argv [ i ] ) == 21 && ! strcmp ( argv [ i ] , "-failurecountinterval" ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 date = get_date ( argv [ i ] ) ;
 if ( date != ( time_t ) - 1 ) policy -> pw_failcnt_interval = date - now ;
 else if ( isdigit ( * argv [ i ] ) ) policy -> pw_failcnt_interval = atoi ( argv [ i ] ) ;
 else {
 fprintf ( stderr , _ ( "Invalid date specification \"%s\".\n" ) , argv [ i ] ) ;
 return - 1 ;
 }
 * mask |= KADM5_PW_FAILURE_COUNT_INTERVAL ;
 continue ;
 }
 else if ( strlen ( argv [ i ] ) == 16 && ! strcmp ( argv [ i ] , "-lockoutduration" ) ) {
 if ( ++ i > argc - 2 ) return - 1 ;
 date = get_date ( argv [ i ] ) ;
 if ( date != ( time_t ) - 1 ) policy -> pw_lockout_duration = date - now ;
 else if ( isdigit ( * argv [ i ] ) ) policy -> pw_lockout_duration = atoi ( argv [ i ] ) ;
 else {
 fprintf ( stderr , _ ( "Invalid date specification \"%s\".\n" ) , argv [ i ] ) ;
 return - 1 ;
 }
 * mask |= KADM5_PW_LOCKOUT_DURATION ;
 continue ;
 }
 else if ( ! strcmp ( argv [ i ] , "-allowedkeysalts" ) ) {
 krb5_key_salt_tuple * ks_tuple = NULL ;
 int n_ks_tuple = 0 ;
 if ( ++ i > argc - 2 ) return - 1 ;
 if ( strcmp ( argv [ i ] , "-" ) ) {
 retval = krb5_string_to_keysalts ( argv [ i ] , "," , ":.-" , 0 , & ks_tuple , & n_ks_tuple ) ;
 if ( retval ) {
 com_err ( caller , retval , _ ( "while parsing keysalts %s" ) , argv [ i ] ) ;
 return - 1 ;
 }
 free ( ks_tuple ) ;
 policy -> allowed_keysalts = argv [ i ] ;
 }
 * mask |= KADM5_POLICY_ALLOWED_KEYSALTS ;
 continue ;
 }
 else return - 1 ;
 }
 if ( i != argc - 1 ) {
 fprintf ( stderr , _ ( "%s: parser lost count!\n" ) , caller ) ;
 return - 1 ;
 }
 else return 0 ;
 }