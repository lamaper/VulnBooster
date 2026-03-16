static void reply_handle ( struct request * const req , u16 flags , u32 ttl , struct reply * reply ) {
 int error ;
 static const int error_codes [ ] = {
 DNS_ERR_FORMAT , DNS_ERR_SERVERFAILED , DNS_ERR_NOTEXIST , DNS_ERR_NOTIMPL , DNS_ERR_REFUSED }
 ;
 if ( flags & 0x020f || ! reply || ! reply -> have_answer ) {
 if ( flags & 0x0200 ) {
 error = DNS_ERR_TRUNCATED ;
 }
 else {
 u16 error_code = ( flags & 0x000f ) - 1 ;
 if ( error_code > 4 ) {
 error = DNS_ERR_UNKNOWN ;
 }
 else {
 error = error_codes [ error_code ] ;
 }
 }
 switch ( error ) {
 case DNS_ERR_NOTIMPL : case DNS_ERR_REFUSED : if ( req -> reissue_count < global_max_reissues ) {
 char msg [ 64 ] ;
 evutil_snprintf ( msg , sizeof ( msg ) , "Bad response %d (%s)" , error , evdns_err_to_string ( error ) ) ;
 nameserver_failed ( req -> ns , msg ) ;
 if ( ! request_reissue ( req ) ) return ;
 }
 break ;
 case DNS_ERR_SERVERFAILED : log ( EVDNS_LOG_DEBUG , "Got a SERVERFAILED from nameserver %s;
 " "will allow the request to time out." , debug_ntoa ( req -> ns -> address ) ) ;
 break ;
 default : nameserver_up ( req -> ns ) ;
 }
 if ( req -> search_state && req -> request_type != TYPE_PTR ) {
 if ( ! search_try_next ( req ) ) {
 request_finished ( req , & req_head ) ;
 return ;
 }
 }
 reply_callback ( req , 0 , error , NULL ) ;
 request_finished ( req , & req_head ) ;
 }
 else {
 reply_callback ( req , ttl , 0 , reply ) ;
 nameserver_up ( req -> ns ) ;
 request_finished ( req , & req_head ) ;
 }
 }