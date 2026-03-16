static int start_transaction ( MYSQL * mysql_con ) {
 verbose_msg ( "-- Starting transaction...\n" ) ;
 if ( ( mysql_get_server_version ( mysql_con ) < 40100 ) && opt_master_data ) {
 fprintf ( stderr , "-- %s: the combination of --single-transaction and " "--master-data requires a MySQL server version of at least 4.1 " "(current server's version is %s). %s\n" , ignore_errors ? "Warning" : "Error" , mysql_con -> server_version ? mysql_con -> server_version : "unknown" , ignore_errors ? "Continuing due to --force, backup may not be consistent across all tables!" : "Aborting." ) ;
 if ( ! ignore_errors ) exit ( EX_MYSQLERR ) ;
 }
 return ( mysql_query_with_error_report ( mysql_con , 0 , "SET SESSION TRANSACTION ISOLATION " "LEVEL REPEATABLE READ" ) || mysql_query_with_error_report ( mysql_con , 0 , "START TRANSACTION " "/*!40100 WITH CONSISTENT SNAPSHOT */" ) ) ;
 }