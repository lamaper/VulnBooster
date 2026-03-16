static void send_paged_response ( Operation * op , SlapReply * rs , ID * lastid , int tentries ) {
 LDAPControl * ctrls [ 2 ] ;
 BerElementBuffer berbuf ;
 BerElement * ber = ( BerElement * ) & berbuf ;
 PagedResultsCookie respcookie ;
 struct berval cookie ;
 Debug ( LDAP_DEBUG_ARGS , "send_paged_response: lastid=0x%08lx nentries=%d\n" , lastid ? * lastid : 0 , rs -> sr_nentries , NULL ) ;
 ctrls [ 1 ] = NULL ;
 ber_init2 ( ber , NULL , LBER_USE_DER ) ;
 if ( lastid ) {
 respcookie = ( PagedResultsCookie ) ( * lastid ) ;
 cookie . bv_len = sizeof ( respcookie ) ;
 cookie . bv_val = ( char * ) & respcookie ;
 }
 else {
 respcookie = ( PagedResultsCookie ) 0 ;
 BER_BVSTR ( & cookie , "" ) ;
 }
 op -> o_conn -> c_pagedresults_state . ps_cookie = respcookie ;
 op -> o_conn -> c_pagedresults_state . ps_count = ( ( PagedResultsState * ) op -> o_pagedresults_state ) -> ps_count + rs -> sr_nentries ;
 ber_printf ( ber , "{
iO}
" , 0 , & cookie ) ;
 ctrls [ 0 ] = op -> o_tmpalloc ( sizeof ( LDAPControl ) , op -> o_tmpmemctx ) ;
 if ( ber_flatten2 ( ber , & ctrls [ 0 ] -> ldctl_value , 0 ) == - 1 ) {
 goto done ;
 }
 ctrls [ 0 ] -> ldctl_oid = LDAP_CONTROL_PAGEDRESULTS ;
 ctrls [ 0 ] -> ldctl_iscritical = 0 ;
 slap_add_ctrls ( op , rs , ctrls ) ;
 rs -> sr_err = LDAP_SUCCESS ;
 send_ldap_result ( op , rs ) ;
 done : ( void ) ber_free_buf ( ber ) ;
 }