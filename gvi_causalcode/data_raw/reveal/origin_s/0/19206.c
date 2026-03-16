static int replace_db_table ( TABLE * table , const char * db , const LEX_USER & combo , ulong rights , bool revoke_grant ) {
 uint i ;
 ulong priv , store_rights ;
 bool old_row_exists = 0 ;
 int error ;
 char what = ( revoke_grant ) ? 'N' : 'Y' ;
 uchar user_key [ MAX_KEY_LENGTH ] ;
 DBUG_ENTER ( "replace_db_table" ) ;
 if ( ! initialized ) {
 my_error ( ER_OPTION_PREVENTS_STATEMENT , MYF ( 0 ) , "--skip-grant-tables" ) ;
 DBUG_RETURN ( - 1 ) ;
 }
 if ( ! find_acl_user ( combo . host . str , combo . user . str , FALSE ) ) {
 my_message ( ER_PASSWORD_NO_MATCH , ER ( ER_PASSWORD_NO_MATCH ) , MYF ( 0 ) ) ;
 DBUG_RETURN ( - 1 ) ;
 }
 table -> use_all_columns ( ) ;
 table -> field [ 0 ] -> store ( combo . host . str , combo . host . length , system_charset_info ) ;
 table -> field [ 1 ] -> store ( db , ( uint ) strlen ( db ) , system_charset_info ) ;
 table -> field [ 2 ] -> store ( combo . user . str , combo . user . length , system_charset_info ) ;
 key_copy ( user_key , table -> record [ 0 ] , table -> key_info , table -> key_info -> key_length ) ;
 if ( table -> file -> index_read_idx_map ( table -> record [ 0 ] , 0 , user_key , HA_WHOLE_KEY , HA_READ_KEY_EXACT ) ) {
 if ( what == 'N' ) {
 my_error ( ER_NONEXISTING_GRANT , MYF ( 0 ) , combo . user . str , combo . host . str ) ;
 goto abort ;
 }
 old_row_exists = 0 ;
 restore_record ( table , s -> default_values ) ;
 table -> field [ 0 ] -> store ( combo . host . str , combo . host . length , system_charset_info ) ;
 table -> field [ 1 ] -> store ( db , ( uint ) strlen ( db ) , system_charset_info ) ;
 table -> field [ 2 ] -> store ( combo . user . str , combo . user . length , system_charset_info ) ;
 }
 else {
 old_row_exists = 1 ;
 store_record ( table , record [ 1 ] ) ;
 }
 store_rights = get_rights_for_db ( rights ) ;
 for ( i = 3 , priv = 1 ;
 i < table -> s -> fields ;
 i ++ , priv <<= 1 ) {
 if ( priv & store_rights ) table -> field [ i ] -> store ( & what , 1 , & my_charset_latin1 ) ;
 }
 rights = get_access ( table , 3 ) ;
 rights = fix_rights_for_db ( rights ) ;
 if ( old_row_exists ) {
 if ( rights ) {
 if ( ( error = table -> file -> ha_update_row ( table -> record [ 1 ] , table -> record [ 0 ] ) ) && error != HA_ERR_RECORD_IS_THE_SAME ) goto table_error ;
 }
 else {
 if ( ( error = table -> file -> ha_delete_row ( table -> record [ 1 ] ) ) ) goto table_error ;
 }
 }
 else if ( rights && ( error = table -> file -> ha_write_row ( table -> record [ 0 ] ) ) ) {
 if ( table -> file -> is_fatal_error ( error , HA_CHECK_DUP_KEY ) ) goto table_error ;
 }
 acl_cache -> clear ( 1 ) ;
 if ( old_row_exists ) acl_update_db ( combo . user . str , combo . host . str , db , rights ) ;
 else if ( rights ) acl_insert_db ( combo . user . str , combo . host . str , db , rights ) ;
 DBUG_RETURN ( 0 ) ;
 table_error : table -> file -> print_error ( error , MYF ( 0 ) ) ;
 abort : DBUG_RETURN ( - 1 ) ;
 }