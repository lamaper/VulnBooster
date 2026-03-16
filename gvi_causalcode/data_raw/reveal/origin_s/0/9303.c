static vpx_codec_err_t validate_img ( vpx_codec_alg_priv_t * ctx , const vpx_image_t * img ) {
 switch ( img -> fmt ) {
 case VPX_IMG_FMT_YV12 : case VPX_IMG_FMT_I420 : case VPX_IMG_FMT_I422 : case VPX_IMG_FMT_I444 : break ;
 default : ERROR ( "Invalid image format. Only YV12, I420, I422, I444 images are " "supported." ) ;
 break ;
 }
 if ( img -> d_w != ctx -> cfg . g_w || img -> d_h != ctx -> cfg . g_h ) ERROR ( "Image size must match encoder init configuration size" ) ;
 return VPX_CODEC_OK ;
 }