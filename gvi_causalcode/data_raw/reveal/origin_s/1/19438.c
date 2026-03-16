void vpx_svc_set_keyframe ( SvcContext * svc_ctx ) {
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || si == NULL ) return ;
 si -> frame_within_gop = 0 ;
 }