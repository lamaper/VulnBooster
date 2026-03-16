static picture_t * DecodeBlock ( decoder_t * p_dec , block_t * * pp_block ) {
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 if ( ! pp_block ) return NULL ;
 if ( * pp_block ) {
 block_t * p_block = * pp_block ;
 if ( p_block -> i_flags & BLOCK_FLAG_DISCONTINUITY ) {
 schro_decoder_reset ( p_sys -> p_schro ) ;
 p_sys -> i_lastpts = VLC_TS_INVALID ;
 block_Release ( p_block ) ;
 * pp_block = NULL ;
 return NULL ;
 }
 SchroBuffer * p_schrobuffer ;
 p_schrobuffer = schro_buffer_new_with_data ( p_block -> p_buffer , p_block -> i_buffer ) ;
 p_schrobuffer -> free = SchroBufferFree ;
 p_schrobuffer -> priv = p_block ;
 if ( p_block -> i_pts > VLC_TS_INVALID ) {
 mtime_t * p_pts = malloc ( sizeof ( * p_pts ) ) ;
 if ( p_pts ) {
 * p_pts = p_block -> i_pts ;
 p_schrobuffer -> tag = schro_tag_new ( p_pts , free ) ;
 }
 }
 * pp_block = NULL ;
 schro_decoder_autoparse_push ( p_sys -> p_schro , p_schrobuffer ) ;
 }
 while ( 1 ) {
 SchroFrame * p_schroframe ;
 picture_t * p_pic ;
 int state = schro_decoder_autoparse_wait ( p_sys -> p_schro ) ;
 switch ( state ) {
 case SCHRO_DECODER_FIRST_ACCESS_UNIT : SetVideoFormat ( p_dec ) ;
 break ;
 case SCHRO_DECODER_NEED_BITS : return NULL ;
 case SCHRO_DECODER_NEED_FRAME : p_schroframe = CreateSchroFrameFromPic ( p_dec ) ;
 if ( ! p_schroframe ) {
 msg_Err ( p_dec , "Could not allocate picture for decoder" ) ;
 return NULL ;
 }
 schro_decoder_add_output_picture ( p_sys -> p_schro , p_schroframe ) ;
 break ;
 case SCHRO_DECODER_OK : {
 SchroTag * p_tag = schro_decoder_get_picture_tag ( p_sys -> p_schro ) ;
 p_schroframe = schro_decoder_pull ( p_sys -> p_schro ) ;
 if ( ! p_schroframe || ! p_schroframe -> priv ) {
 if ( p_tag ) schro_tag_free ( p_tag ) ;
 if ( p_schroframe ) schro_frame_unref ( p_schroframe ) ;
 break ;
 }
 p_pic = ( ( struct picture_free_t * ) p_schroframe -> priv ) -> p_pic ;
 p_schroframe -> priv = NULL ;
 if ( p_tag ) {
 p_pic -> date = * ( mtime_t * ) p_tag -> value ;
 schro_tag_free ( p_tag ) ;
 }
 else if ( p_sys -> i_lastpts > VLC_TS_INVALID ) {
 p_pic -> date = p_sys -> i_lastpts + p_sys -> i_frame_pts_delta ;
 }
 p_sys -> i_lastpts = p_pic -> date ;
 schro_frame_unref ( p_schroframe ) ;
 return p_pic ;
 }
 case SCHRO_DECODER_EOS : break ;
 case SCHRO_DECODER_ERROR : msg_Err ( p_dec , "SCHRO_DECODER_ERROR" ) ;
 return NULL ;
 }
 }
 }