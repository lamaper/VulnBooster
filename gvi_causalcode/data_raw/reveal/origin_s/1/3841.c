int vpx_svc_is_keyframe ( const SvcContext * svc_ctx ) {
 const SvcInternal * const si = get_const_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || si == NULL || si -> frame_list == NULL ) return 0 ;
 return ( si -> frame_list -> flags & VPX_FRAME_IS_KEY ) != 0 ;
 }