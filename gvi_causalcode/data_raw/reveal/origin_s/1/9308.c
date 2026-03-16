int vpx_svc_get_encode_frame_count ( const SvcContext * svc_ctx ) {
 const SvcInternal * const si = get_const_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || si == NULL ) return 0 ;
 return si -> encode_frame_count ;
 }