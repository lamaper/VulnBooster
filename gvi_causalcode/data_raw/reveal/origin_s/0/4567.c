static void pick_quickcompress_mode ( vpx_codec_alg_priv_t * ctx , unsigned long duration , unsigned long deadline ) {
 MODE new_mode = BEST ;
 switch ( ctx -> cfg . g_pass ) {
 case VPX_RC_ONE_PASS : if ( deadline > 0 ) {
 const vpx_codec_enc_cfg_t * const cfg = & ctx -> cfg ;
 const uint64_t duration_us = ( uint64_t ) duration * 1000000 * ( uint64_t ) cfg -> g_timebase . num / ( uint64_t ) cfg -> g_timebase . den ;
 new_mode = ( deadline > duration_us ) ? GOOD : REALTIME ;
 }
 else {
 new_mode = BEST ;
 }
 break ;
 case VPX_RC_FIRST_PASS : break ;
 case VPX_RC_LAST_PASS : new_mode = deadline > 0 ? GOOD : BEST ;
 break ;
 }
 if ( ctx -> oxcf . mode != new_mode ) {
 ctx -> oxcf . mode = new_mode ;
 vp9_change_config ( ctx -> cpi , & ctx -> oxcf ) ;
 }
 }