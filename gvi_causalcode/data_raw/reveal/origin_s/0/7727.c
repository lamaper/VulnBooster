static void dump_trigger_old ( FILE * sql_file , MYSQL_RES * show_triggers_rs , MYSQL_ROW * show_trigger_row , const char * table_name ) {
 char quoted_table_name_buf [ NAME_LEN * 2 + 3 ] ;
 char * quoted_table_name = quote_name ( table_name , quoted_table_name_buf , 1 ) ;
 char name_buff [ NAME_LEN * 4 + 3 ] ;
 const char * xml_msg = "\nWarning! mysqldump being run against old server " "that does not\nsupport 'SHOW CREATE TRIGGERS' " "statement. Skipping..\n" ;
 DBUG_ENTER ( "dump_trigger_old" ) ;
 if ( opt_xml ) {
 print_xml_comment ( sql_file , strlen ( xml_msg ) , xml_msg ) ;
 check_io ( sql_file ) ;
 DBUG_VOID_RETURN ;
 }
 fprintf ( sql_file , "--\n" "-- WARNING: old server version. " "The following dump may be incomplete.\n" "--\n" ) ;
 if ( opt_compact ) fprintf ( sql_file , "/*!50003 SET @OLD_SQL_MODE=@@SQL_MODE*/;
\n" ) ;
 fprintf ( sql_file , "DELIMITER ;
;
\n" "/*!50003 SET SESSION SQL_MODE=\"%s\" */;
;
\n" "/*!50003 CREATE */ " , ( * show_trigger_row ) [ 6 ] ) ;
 if ( mysql_num_fields ( show_triggers_rs ) > 7 ) {
 size_t user_name_len ;
 char user_name_str [ USERNAME_LENGTH + 1 ] ;
 char quoted_user_name_str [ USERNAME_LENGTH * 2 + 3 ] ;
 size_t host_name_len ;
 char host_name_str [ HOSTNAME_LENGTH + 1 ] ;
 char quoted_host_name_str [ HOSTNAME_LENGTH * 2 + 3 ] ;
 parse_user ( ( * show_trigger_row ) [ 7 ] , strlen ( ( * show_trigger_row ) [ 7 ] ) , user_name_str , & user_name_len , host_name_str , & host_name_len ) ;
 fprintf ( sql_file , "/*!50017 DEFINER=%s@%s */ " , quote_name ( user_name_str , quoted_user_name_str , FALSE ) , quote_name ( host_name_str , quoted_host_name_str , FALSE ) ) ;
 }
 fprintf ( sql_file , "/*!50003 TRIGGER %s %s %s ON %s FOR EACH ROW%s%s */;
;
\n" "DELIMITER ;
\n" , quote_name ( ( * show_trigger_row ) [ 0 ] , name_buff , 0 ) , ( * show_trigger_row ) [ 4 ] , ( * show_trigger_row ) [ 1 ] , quoted_table_name , ( strchr ( " \t\n\r" , * ( ( * show_trigger_row ) [ 3 ] ) ) ) ? "" : " " , ( * show_trigger_row ) [ 3 ] ) ;
 if ( opt_compact ) fprintf ( sql_file , "/*!50003 SET SESSION SQL_MODE=@OLD_SQL_MODE */;
\n" ) ;
 DBUG_VOID_RETURN ;
 }