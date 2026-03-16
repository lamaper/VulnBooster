void * vpx_svc_get_buffer ( SvcContext * svc_ctx ) {
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || si == NULL || si -> frame_list == NULL ) return NULL ;
 if ( si -> frame_temp ) fd_free ( si -> frame_temp ) ;
 si -> frame_temp = si -> frame_list ;
 si -> frame_list = si -> frame_list -> next ;
 return si -> frame_temp -> buf ;
 }