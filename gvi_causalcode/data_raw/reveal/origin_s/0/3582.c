vpx_codec_err_t vpx_codec_encode ( vpx_codec_ctx_t * ctx , const vpx_image_t * img , vpx_codec_pts_t pts , unsigned long duration , vpx_enc_frame_flags_t flags , unsigned long deadline ) {
 vpx_codec_err_t res = VPX_CODEC_OK ;
 if ( ! ctx || ( img && ! duration ) ) res = VPX_CODEC_INVALID_PARAM ;
 else if ( ! ctx -> iface || ! ctx -> priv ) res = VPX_CODEC_ERROR ;
 else if ( ! ( ctx -> iface -> caps & VPX_CODEC_CAP_ENCODER ) ) res = VPX_CODEC_INCAPABLE ;
 else {
 unsigned int num_enc = ctx -> priv -> enc . total_encoders ;
 FLOATING_POINT_INIT ( ) ;
 if ( num_enc == 1 ) res = ctx -> iface -> enc . encode ( get_alg_priv ( ctx ) , img , pts , duration , flags , deadline ) ;
 else {
 int i ;
 ctx += num_enc - 1 ;
 if ( img ) img += num_enc - 1 ;
 for ( i = num_enc - 1 ;
 i >= 0 ;
 i -- ) {
 if ( ( res = ctx -> iface -> enc . encode ( get_alg_priv ( ctx ) , img , pts , duration , flags , deadline ) ) ) break ;
 ctx -- ;
 if ( img ) img -- ;
 }
 ctx ++ ;
 }
 FLOATING_POINT_RESTORE ( ) ;
 }
 return SAVE_STATUS ( ctx , res ) ;
 }