static bool update_user_table ( THD * thd , TABLE * table , const char * host , const char * user , const char * new_password , uint new_password_len ) {
 char user_key [ MAX_KEY_LENGTH ] ;
 int error ;
 DBUG_ENTER ( "update_user_table" ) ;
 DBUG_PRINT ( "enter" , ( "user: %s host: %s" , user , host ) ) ;
 table -> use_all_columns ( ) ;
 table -> field [ 0 ] -> store ( host , ( uint ) strlen ( host ) , system_charset_info ) ;
 table -> field [ 1 ] -> store ( user , ( uint ) strlen ( user ) , system_charset_info ) ;
 key_copy ( ( uchar * ) user_key , table -> record [ 0 ] , table -> key_info , table -> key_info -> key_length ) ;
 if ( table -> file -> index_read_idx_map ( table -> record [ 0 ] , 0 , ( uchar * ) user_key , HA_WHOLE_KEY , HA_READ_KEY_EXACT ) ) {
 my_message ( ER_PASSWORD_NO_MATCH , ER ( ER_PASSWORD_NO_MATCH ) , MYF ( 0 ) ) ;
 DBUG_RETURN ( 1 ) ;
 }
 store_record ( table , record [ 1 ] ) ;
 table -> field [ 2 ] -> store ( new_password , new_password_len , system_charset_info ) ;
 if ( ( error = table -> file -> ha_update_row ( table -> record [ 1 ] , table -> record [ 0 ] ) ) && error != HA_ERR_RECORD_IS_THE_SAME ) {
 table -> file -> print_error ( error , MYF ( 0 ) ) ;
 DBUG_RETURN ( 1 ) ;
 }
 DBUG_RETURN ( 0 ) ;
 }