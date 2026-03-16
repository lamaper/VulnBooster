static int show_routine_grants ( THD * thd , LEX_USER * lex_user , HASH * hash , const char * type , int typelen , char * buff , int buffsize ) {
 uint counter , index ;
 int error = 0 ;
 Protocol * protocol = thd -> protocol ;
 for ( index = 0 ;
 index < hash -> records ;
 index ++ ) {
 const char * user , * host ;
 GRANT_NAME * grant_proc = ( GRANT_NAME * ) hash_element ( hash , index ) ;
 if ( ! ( user = grant_proc -> user ) ) user = "" ;
 if ( ! ( host = grant_proc -> host . hostname ) ) host = "" ;
 if ( ! strcmp ( lex_user -> user . str , user ) && ! my_strcasecmp ( system_charset_info , lex_user -> host . str , host ) ) {
 ulong proc_access = grant_proc -> privs ;
 if ( proc_access != 0 ) {
 String global ( buff , buffsize , system_charset_info ) ;
 ulong test_access = proc_access & ~ GRANT_ACL ;
 global . length ( 0 ) ;
 global . append ( STRING_WITH_LEN ( "GRANT " ) ) ;
 if ( ! test_access ) global . append ( STRING_WITH_LEN ( "USAGE" ) ) ;
 else {
 int found = 0 ;
 ulong j ;
 for ( counter = 0 , j = SELECT_ACL ;
 j <= PROC_ACLS ;
 counter ++ , j <<= 1 ) {
 if ( test_access & j ) {
 if ( found ) global . append ( STRING_WITH_LEN ( ", " ) ) ;
 found = 1 ;
 global . append ( command_array [ counter ] , command_lengths [ counter ] ) ;
 }
 }
 }
 global . append ( STRING_WITH_LEN ( " ON " ) ) ;
 global . append ( type , typelen ) ;
 global . append ( ' ' ) ;
 append_identifier ( thd , & global , grant_proc -> db , strlen ( grant_proc -> db ) ) ;
 global . append ( '.' ) ;
 append_identifier ( thd , & global , grant_proc -> tname , strlen ( grant_proc -> tname ) ) ;
 global . append ( STRING_WITH_LEN ( " TO '" ) ) ;
 global . append ( lex_user -> user . str , lex_user -> user . length , system_charset_info ) ;
 global . append ( STRING_WITH_LEN ( "'@'" ) ) ;
 global . append ( host , strlen ( host ) , system_charset_info ) ;
 global . append ( '\'' ) ;
 if ( proc_access & GRANT_ACL ) global . append ( STRING_WITH_LEN ( " WITH GRANT OPTION" ) ) ;
 protocol -> prepare_for_resend ( ) ;
 protocol -> store ( global . ptr ( ) , global . length ( ) , global . charset ( ) ) ;
 if ( protocol -> write ( ) ) {
 error = - 1 ;
 break ;
 }
 }
 }
 }
 return error ;
 }