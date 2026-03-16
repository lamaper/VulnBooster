size_t vpx_svc_get_frame_size ( const SvcContext * svc_ctx ) {
 const SvcInternal * const si = get_const_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || si == NULL || si -> frame_list == NULL ) return 0 ;
 return si -> frame_list -> size ;
 }