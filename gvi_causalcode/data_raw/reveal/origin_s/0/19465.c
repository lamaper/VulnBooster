err_status_t srtp_remove_stream ( srtp_t session , uint32_t ssrc ) {
 srtp_stream_ctx_t * stream , * last_stream ;
 err_status_t status ;
 if ( session == NULL ) return err_status_bad_param ;
 last_stream = stream = session -> stream_list ;
 while ( ( stream != NULL ) && ( ssrc != stream -> ssrc ) ) {
 last_stream = stream ;
 stream = stream -> next ;
 }
 if ( stream == NULL ) return err_status_no_ctx ;
 if ( last_stream == stream ) session -> stream_list = stream -> next ;
 else last_stream -> next = stream -> next ;
 status = srtp_stream_dealloc ( session , stream ) ;
 if ( status ) return status ;
 return err_status_ok ;
 }