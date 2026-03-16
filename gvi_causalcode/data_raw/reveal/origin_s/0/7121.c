srtp_stream_ctx_t * srtp_get_stream ( srtp_t srtp , uint32_t ssrc ) {
 srtp_stream_ctx_t * stream ;
 stream = srtp -> stream_list ;
 while ( stream != NULL ) {
 if ( stream -> ssrc == ssrc ) return stream ;
 stream = stream -> next ;
 }
 return NULL ;
 }