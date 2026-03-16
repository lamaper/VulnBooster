static int replace_column_table ( GRANT_TABLE * g_t , TABLE * table , const LEX_USER & combo , List < LEX_COLUMN > & columns , const char * db , const char * table_name , ulong rights , bool revoke_grant ) {
 int error = 0 , result = 0 ;
 uchar key [ MAX_KEY_LENGTH ] ;
 uint key_prefix_length ;
 KEY_PART_INFO * key_part = table -> key_info -> key_part ;
 DBUG_ENTER ( "replace_column_table" ) ;
 table -> use_all_columns ( ) ;
 table -> field [ 0 ] -> store ( combo . host . str , combo . host . length , system_charset_info ) ;
 table -> field [ 1 ] -> store ( db , ( uint ) strlen ( db ) , system_charset_info ) ;
 table -> field [ 2 ] -> store ( combo . user . str , combo . user . length , system_charset_info ) ;
 table -> field [ 3 ] -> store ( table_name , ( uint ) strlen ( table_name ) , system_charset_info ) ;
 key_prefix_length = ( key_part [ 0 ] . store_length + key_part [ 1 ] . store_length + key_part [ 2 ] . store_length + key_part [ 3 ] . store_length ) ;
 key_copy ( key , table -> record [ 0 ] , table -> key_info , key_prefix_length ) ;
 rights &= COL_ACLS ;
 List_iterator < LEX_COLUMN > iter ( columns ) ;
 class LEX_COLUMN * column ;
 table -> file -> ha_index_init ( 0 , 1 ) ;
 while ( ( column = iter ++ ) ) {
 ulong privileges = column -> rights ;
 bool old_row_exists = 0 ;
 uchar user_key [ MAX_KEY_LENGTH ] ;
 key_restore ( table -> record [ 0 ] , key , table -> key_info , key_prefix_length ) ;
 table -> field [ 4 ] -> store ( column -> column . ptr ( ) , column -> column . length ( ) , system_charset_info ) ;
 key_copy ( user_key , table -> record [ 0 ] , table -> key_info , table -> key_info -> key_length ) ;
 if ( table -> file -> index_read_map ( table -> record [ 0 ] , user_key , HA_WHOLE_KEY , HA_READ_KEY_EXACT ) ) {
 if ( revoke_grant ) {
 my_error ( ER_NONEXISTING_TABLE_GRANT , MYF ( 0 ) , combo . user . str , combo . host . str , table_name ) ;
 result = - 1 ;
 continue ;
 }
 old_row_exists = 0 ;
 restore_record ( table , s -> default_values ) ;
 key_restore ( table -> record [ 0 ] , key , table -> key_info , key_prefix_length ) ;
 table -> field [ 4 ] -> store ( column -> column . ptr ( ) , column -> column . length ( ) , system_charset_info ) ;
 }
 else {
 ulong tmp = ( ulong ) table -> field [ 6 ] -> val_int ( ) ;
 tmp = fix_rights_for_column ( tmp ) ;
 if ( revoke_grant ) privileges = tmp & ~ ( privileges | rights ) ;
 else privileges |= tmp ;
 old_row_exists = 1 ;
 store_record ( table , record [ 1 ] ) ;
 }
 table -> field [ 6 ] -> store ( ( longlong ) get_rights_for_column ( privileges ) , TRUE ) ;
 if ( old_row_exists ) {
 GRANT_COLUMN * grant_column ;
 if ( privileges ) error = table -> file -> ha_update_row ( table -> record [ 1 ] , table -> record [ 0 ] ) ;
 else error = table -> file -> ha_delete_row ( table -> record [ 1 ] ) ;
 if ( error && error != HA_ERR_RECORD_IS_THE_SAME ) {
 table -> file -> print_error ( error , MYF ( 0 ) ) ;
 result = - 1 ;
 goto end ;
 }
 else error = 0 ;
 grant_column = column_hash_search ( g_t , column -> column . ptr ( ) , column -> column . length ( ) ) ;
 if ( grant_column ) grant_column -> rights = privileges ;
 }
 else {
 GRANT_COLUMN * grant_column ;
 if ( ( error = table -> file -> ha_write_row ( table -> record [ 0 ] ) ) ) {
 table -> file -> print_error ( error , MYF ( 0 ) ) ;
 result = - 1 ;
 goto end ;
 }
 grant_column = new GRANT_COLUMN ( column -> column , privileges ) ;
 if ( my_hash_insert ( & g_t -> hash_columns , ( uchar * ) grant_column ) ) {
 result = - 1 ;
 goto end ;
 }
 }
 }
 if ( revoke_grant ) {
 uchar user_key [ MAX_KEY_LENGTH ] ;
 key_copy ( user_key , table -> record [ 0 ] , table -> key_info , key_prefix_length ) ;
 if ( table -> file -> index_read_map ( table -> record [ 0 ] , user_key , ( key_part_map ) 15 , HA_READ_KEY_EXACT ) ) goto end ;
 do {
 ulong privileges = ( ulong ) table -> field [ 6 ] -> val_int ( ) ;
 privileges = fix_rights_for_column ( privileges ) ;
 store_record ( table , record [ 1 ] ) ;
 if ( privileges & rights ) {
 GRANT_COLUMN * grant_column = NULL ;
 char colum_name_buf [ HOSTNAME_LENGTH + 1 ] ;
 String column_name ( colum_name_buf , sizeof ( colum_name_buf ) , system_charset_info ) ;
 privileges &= ~ rights ;
 table -> field [ 6 ] -> store ( ( longlong ) get_rights_for_column ( privileges ) , TRUE ) ;
 table -> field [ 4 ] -> val_str ( & column_name ) ;
 grant_column = column_hash_search ( g_t , column_name . ptr ( ) , column_name . length ( ) ) ;
 if ( privileges ) {
 int tmp_error ;
 if ( ( tmp_error = table -> file -> ha_update_row ( table -> record [ 1 ] , table -> record [ 0 ] ) ) && tmp_error != HA_ERR_RECORD_IS_THE_SAME ) {
 table -> file -> print_error ( tmp_error , MYF ( 0 ) ) ;
 result = - 1 ;
 goto end ;
 }
 if ( grant_column ) grant_column -> rights = privileges ;
 }
 else {
 int tmp_error ;
 if ( ( tmp_error = table -> file -> ha_delete_row ( table -> record [ 1 ] ) ) ) {
 table -> file -> print_error ( tmp_error , MYF ( 0 ) ) ;
 result = - 1 ;
 goto end ;
 }
 if ( grant_column ) hash_delete ( & g_t -> hash_columns , ( uchar * ) grant_column ) ;
 }
 }
 }
 while ( ! table -> file -> index_next ( table -> record [ 0 ] ) && ! key_cmp_if_same ( table , key , 0 , key_prefix_length ) ) ;
 }
 end : table -> file -> ha_index_end ( ) ;
 DBUG_RETURN ( result ) ;
 }