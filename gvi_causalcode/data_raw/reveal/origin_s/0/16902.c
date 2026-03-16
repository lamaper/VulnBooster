void TSHttpTxnServerPush ( TSHttpTxn txnp , const char * url , int url_len ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 URL url_obj ;
 url_obj . create ( nullptr ) ;
 if ( url_obj . parse ( url , url_len ) == PARSE_RESULT_ERROR ) {
 url_obj . destroy ( ) ;
 return ;
 }
 HttpSM * sm = reinterpret_cast < HttpSM * > ( txnp ) ;
 Http2Stream * stream = dynamic_cast < Http2Stream * > ( sm -> ua_session ) ;
 if ( stream ) {
 Http2ClientSession * parent = static_cast < Http2ClientSession * > ( stream -> get_parent ( ) ) ;
 if ( ! parent -> is_url_pushed ( url , url_len ) ) {
 HTTPHdr * hptr = & ( sm -> t_state . hdr_info . client_request ) ;
 TSMLoc obj = reinterpret_cast < TSMLoc > ( hptr -> m_http ) ;
 MIMEHdrImpl * mh = _hdr_mloc_to_mime_hdr_impl ( obj ) ;
 MIMEField * f = mime_hdr_field_find ( mh , MIME_FIELD_ACCEPT_ENCODING , MIME_LEN_ACCEPT_ENCODING ) ;
 stream -> push_promise ( url_obj , f ) ;
 parent -> add_url_to_pushed_table ( url , url_len ) ;
 }
 }
 url_obj . destroy ( ) ;
 }