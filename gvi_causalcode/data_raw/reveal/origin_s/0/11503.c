static struct stream_state * new_stream ( struct VpxEncoderConfig * global , struct stream_state * prev ) {
 struct stream_state * stream ;
 stream = calloc ( 1 , sizeof ( * stream ) ) ;
 if ( stream == NULL ) {
 fatal ( "Failed to allocate new stream." ) ;
 }
 if ( prev ) {
 memcpy ( stream , prev , sizeof ( * stream ) ) ;
 stream -> index ++ ;
 prev -> next = stream ;
 }
 else {
 vpx_codec_err_t res ;
 res = vpx_codec_enc_config_default ( global -> codec -> codec_interface ( ) , & stream -> config . cfg , global -> usage ) ;
 if ( res ) fatal ( "Failed to get config: %s\n" , vpx_codec_err_to_string ( res ) ) ;
 stream -> config . cfg . g_timebase . den = 1000 ;
 stream -> config . cfg . g_w = 0 ;
 stream -> config . cfg . g_h = 0 ;
 stream -> config . write_webm = 1 ;

 stream -> ebml . last_pts_ns = - 1 ;
 stream -> ebml . writer = NULL ;
 stream -> ebml . segment = NULL ;

 if ( global -> deadline == VPX_DL_REALTIME ) stream -> config . cfg . g_lag_in_frames = 0 ;
 }
 stream -> config . out_fn = NULL ;
 stream -> next = NULL ;
 return stream ;
 }