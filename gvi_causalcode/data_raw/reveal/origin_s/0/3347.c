static vpx_codec_frame_flags_t get_frame_pkt_flags ( const VP9_COMP * cpi , unsigned int lib_flags ) {
 vpx_codec_frame_flags_t flags = lib_flags << 16 ;
 if ( lib_flags & FRAMEFLAGS_KEY # if CONFIG_SPATIAL_SVC || ( is_two_pass_svc ( cpi ) && cpi -> svc . layer_context [ 0 ] . is_key_frame ) # endif ) flags |= VPX_FRAME_IS_KEY ;
 if ( cpi -> droppable ) flags |= VPX_FRAME_IS_DROPPABLE ;
 return flags ;
 }