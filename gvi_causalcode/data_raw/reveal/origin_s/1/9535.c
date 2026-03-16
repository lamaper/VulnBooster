vpx_codec_err_t vpx_svc_get_layer_resolution ( const SvcContext * svc_ctx , int layer , unsigned int * width , unsigned int * height ) {
 int w , h , index , num , den ;
 const SvcInternal * const si = get_const_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || si == NULL || width == NULL || height == NULL ) {
 return VPX_CODEC_INVALID_PARAM ;
 }
 if ( layer < 0 || layer >= si -> layers ) return VPX_CODEC_INVALID_PARAM ;
 index = layer + VPX_SS_MAX_LAYERS - si -> layers ;
 num = si -> scaling_factor_num [ index ] ;
 den = si -> scaling_factor_den [ index ] ;
 if ( num == 0 || den == 0 ) return VPX_CODEC_INVALID_PARAM ;
 w = si -> width * num / den ;
 h = si -> height * num / den ;
 w += w % 2 ;
 h += h % 2 ;
 * width = w ;
 * height = h ;
 return VPX_CODEC_OK ;
 }