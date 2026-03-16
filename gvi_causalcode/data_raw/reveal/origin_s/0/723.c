static int modify_grant_table ( TABLE * table , Field * host_field , Field * user_field , LEX_USER * user_to ) {
 int error ;
 DBUG_ENTER ( "modify_grant_table" ) ;
 if ( user_to ) {
 store_record ( table , record [ 1 ] ) ;
 host_field -> store ( user_to -> host . str , user_to -> host . length , system_charset_info ) ;
 user_field -> store ( user_to -> user . str , user_to -> user . length , system_charset_info ) ;
 if ( ( error = table -> file -> ha_update_row ( table -> record [ 1 ] , table -> record [ 0 ] ) ) && error != HA_ERR_RECORD_IS_THE_SAME ) table -> file -> print_error ( error , MYF ( 0 ) ) ;
 else error = 0 ;
 }
 else {
 if ( ( error = table -> file -> ha_delete_row ( table -> record [ 0 ] ) ) ) table -> file -> print_error ( error , MYF ( 0 ) ) ;
 }
 DBUG_RETURN ( error ) ;
 }