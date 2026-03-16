static struct curl_slist * get_dav_token_headers ( struct remote_lock * lock , enum dav_header_flag options ) {
 struct strbuf buf = STRBUF_INIT ;
 struct curl_slist * dav_headers = NULL ;
 if ( options & DAV_HEADER_IF ) {
 strbuf_addf ( & buf , "If: (<%s>)" , lock -> token ) ;
 dav_headers = curl_slist_append ( dav_headers , buf . buf ) ;
 strbuf_reset ( & buf ) ;
 }
 if ( options & DAV_HEADER_LOCK ) {
 strbuf_addf ( & buf , "Lock-Token: <%s>" , lock -> token ) ;
 dav_headers = curl_slist_append ( dav_headers , buf . buf ) ;
 strbuf_reset ( & buf ) ;
 }
 if ( options & DAV_HEADER_TIMEOUT ) {
 strbuf_addf ( & buf , "Timeout: Second-%ld" , lock -> timeout ) ;
 dav_headers = curl_slist_append ( dav_headers , buf . buf ) ;
 strbuf_reset ( & buf ) ;
 }
 strbuf_release ( & buf ) ;
 return dav_headers ;
 }