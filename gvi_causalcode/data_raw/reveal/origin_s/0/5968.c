static const char * server_version_string ( MYSQL * con ) {
 if ( server_version == NULL ) {
 MYSQL_RES * result ;
 if ( ! mysql_query ( con , "select @@version_comment limit 1" ) && ( result = mysql_use_result ( con ) ) ) {
 MYSQL_ROW cur = mysql_fetch_row ( result ) ;
 if ( cur && cur [ 0 ] ) {
 size_t len = strlen ( mysql_get_server_info ( con ) ) + strlen ( cur [ 0 ] ) + 2 ;
 if ( ( server_version = ( char * ) my_malloc ( len , MYF ( MY_WME ) ) ) ) {
 char * bufp ;
 bufp = strmov ( server_version , mysql_get_server_info ( con ) ) ;
 bufp = strmov ( bufp , " " ) ;
 ( void ) strmov ( bufp , cur [ 0 ] ) ;
 }
 }
 mysql_free_result ( result ) ;
 }
 if ( server_version == NULL ) server_version = my_strdup ( mysql_get_server_info ( con ) , MYF ( MY_WME ) ) ;
 }
 return server_version ? server_version : "" ;
 }