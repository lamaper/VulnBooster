static bool config_filter_match_service ( const struct config_filter * mask , const struct config_filter * filter ) {
 if ( mask -> service != NULL ) {
 if ( filter -> service == NULL ) return FALSE ;
 if ( mask -> service [ 0 ] == '!' ) {
 if ( strcmp ( filter -> service , mask -> service + 1 ) == 0 ) return FALSE ;
 }
 else {
 if ( strcmp ( filter -> service , mask -> service ) != 0 ) return FALSE ;
 }
 }
 return TRUE ;
 }