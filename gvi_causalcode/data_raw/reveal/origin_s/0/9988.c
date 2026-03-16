static int parse_paged_cookie ( Operation * op , SlapReply * rs ) {
 int rc = LDAP_SUCCESS ;
 PagedResultsState * ps = op -> o_pagedresults_state ;
 assert ( get_pagedresults ( op ) > SLAP_CONTROL_IGNORED ) ;
 if ( ps -> ps_cookieval . bv_len ) {
 PagedResultsCookie reqcookie ;
 if ( ps -> ps_cookieval . bv_len != sizeof ( reqcookie ) ) {
 rs -> sr_text = "paged results cookie is invalid" ;
 rc = LDAP_PROTOCOL_ERROR ;
 goto done ;
 }
 AC_MEMCPY ( & reqcookie , ps -> ps_cookieval . bv_val , sizeof ( reqcookie ) ) ;
 if ( reqcookie > ps -> ps_cookie ) {
 rs -> sr_text = "paged results cookie is invalid" ;
 rc = LDAP_PROTOCOL_ERROR ;
 goto done ;
 }
 else if ( reqcookie < ps -> ps_cookie ) {
 rs -> sr_text = "paged results cookie is invalid or old" ;
 rc = LDAP_UNWILLING_TO_PERFORM ;
 goto done ;
 }
 }
 else {
 op -> o_conn -> c_pagedresults_state . ps_cookie = 0 ;
 }
 done : ;
 return rc ;
 }