static int http_server_session_sharing_cb ( const char * name , RecDataT dtype , RecData data , void * cookie ) {
 bool valid_p = true ;
 HttpConfigParams * c = static_cast < HttpConfigParams * > ( cookie ) ;
 if ( 0 == strcasecmp ( "proxy.config.http.server_session_sharing.match" , name ) ) {
 MgmtByte & match = c -> oride . server_session_sharing_match ;
 if ( RECD_INT == dtype ) {
 match = static_cast < TSServerSessionSharingMatchType > ( data . rec_int ) ;
 }
 else if ( RECD_STRING == dtype && http_config_enum_search ( data . rec_string , SessionSharingMatchStrings , match ) ) {
 }
 else {
 valid_p = false ;
 }
 }
 else {
 valid_p = false ;
 }
 if ( valid_p ) {
 http_config_cb ( name , dtype , data , cookie ) ;
 }
 return REC_ERR_OKAY ;
 }