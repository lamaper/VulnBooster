static int handle_grant_table ( TABLE_LIST * tables , uint table_no , bool drop , LEX_USER * user_from , LEX_USER * user_to ) {
 int result = 0 ;
 int error ;
 TABLE * table = tables [ table_no ] . table ;
 Field * host_field = table -> field [ 0 ] ;
 Field * user_field = table -> field [ table_no ? 2 : 1 ] ;
 char * host_str = user_from -> host . str ;
 char * user_str = user_from -> user . str ;
 const char * host ;
 const char * user ;
 uchar user_key [ MAX_KEY_LENGTH ] ;
 uint key_prefix_length ;
 DBUG_ENTER ( "handle_grant_table" ) ;
 THD * thd = current_thd ;
 table -> use_all_columns ( ) ;
 if ( ! table_no ) {
 DBUG_PRINT ( "info" , ( "read table: '%s' search: '%s'@'%s'" , table -> s -> table_name . str , user_str , host_str ) ) ;
 host_field -> store ( host_str , user_from -> host . length , system_charset_info ) ;
 user_field -> store ( user_str , user_from -> user . length , system_charset_info ) ;
 key_prefix_length = ( table -> key_info -> key_part [ 0 ] . store_length + table -> key_info -> key_part [ 1 ] . store_length ) ;
 key_copy ( user_key , table -> record [ 0 ] , table -> key_info , key_prefix_length ) ;
 if ( ( error = table -> file -> index_read_idx_map ( table -> record [ 0 ] , 0 , user_key , ( key_part_map ) 3 , HA_READ_KEY_EXACT ) ) ) {
 if ( error != HA_ERR_KEY_NOT_FOUND && error != HA_ERR_END_OF_FILE ) {
 table -> file -> print_error ( error , MYF ( 0 ) ) ;
 result = - 1 ;
 }
 }
 else {
 result = ( ( drop || user_to ) && modify_grant_table ( table , host_field , user_field , user_to ) ) ? - 1 : 1 ;
 }
 DBUG_PRINT ( "info" , ( "read result: %d" , result ) ) ;
 }
 else {
 if ( ( error = table -> file -> ha_rnd_init ( 1 ) ) ) {
 table -> file -> print_error ( error , MYF ( 0 ) ) ;
 result = - 1 ;
 }
 else {


 if ( error ) {
 DBUG_PRINT ( "info" , ( "scan error: %d" , error ) ) ;
 continue ;
 }
 if ( ! ( host = get_field ( thd -> mem_root , host_field ) ) ) host = "" ;
 if ( ! ( user = get_field ( thd -> mem_root , user_field ) ) ) user = "" ;


 result = ( ( drop || user_to ) && modify_grant_table ( table , host_field , user_field , user_to ) ) ? - 1 : result ? result : 1 ;
 if ( ! drop && ! user_to ) break ;
 }
 ( void ) table -> file -> ha_rnd_end ( ) ;
 DBUG_PRINT ( "info" , ( "scan result: %d" , result ) ) ;
 }
 }
 DBUG_RETURN ( result ) ;
 }