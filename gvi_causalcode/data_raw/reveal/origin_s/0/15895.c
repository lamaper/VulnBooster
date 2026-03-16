static int dump_all_databases ( ) {
 MYSQL_ROW row ;
 MYSQL_RES * tableres ;
 int result = 0 ;
 if ( mysql_query_with_error_report ( mysql , & tableres , "SHOW DATABASES" ) ) return 1 ;
 while ( ( row = mysql_fetch_row ( tableres ) ) ) {
 if ( mysql_get_server_version ( mysql ) >= FIRST_INFORMATION_SCHEMA_VERSION && ! my_strcasecmp ( & my_charset_latin1 , row [ 0 ] , INFORMATION_SCHEMA_DB_NAME ) ) continue ;
 if ( mysql_get_server_version ( mysql ) >= FIRST_PERFORMANCE_SCHEMA_VERSION && ! my_strcasecmp ( & my_charset_latin1 , row [ 0 ] , PERFORMANCE_SCHEMA_DB_NAME ) ) continue ;
 if ( dump_all_tables_in_db ( row [ 0 ] ) ) result = 1 ;
 }
 mysql_free_result ( tableres ) ;
 if ( seen_views ) {
 if ( mysql_query ( mysql , "SHOW DATABASES" ) || ! ( tableres = mysql_store_result ( mysql ) ) ) {
 fprintf ( stderr , "%s: Error: Couldn't execute 'SHOW DATABASES': %s\n" , my_progname_short , mysql_error ( mysql ) ) ;
 return 1 ;
 }
 while ( ( row = mysql_fetch_row ( tableres ) ) ) {
 if ( mysql_get_server_version ( mysql ) >= FIRST_INFORMATION_SCHEMA_VERSION && ! my_strcasecmp ( & my_charset_latin1 , row [ 0 ] , INFORMATION_SCHEMA_DB_NAME ) ) continue ;
 if ( mysql_get_server_version ( mysql ) >= FIRST_PERFORMANCE_SCHEMA_VERSION && ! my_strcasecmp ( & my_charset_latin1 , row [ 0 ] , PERFORMANCE_SCHEMA_DB_NAME ) ) continue ;
 if ( dump_all_views_in_db ( row [ 0 ] ) ) result = 1 ;
 }
 mysql_free_result ( tableres ) ;
 }
 return result ;
 }