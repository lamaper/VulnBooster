static int get_image_bps ( const vpx_image_t * img ) {
 switch ( img -> fmt ) {
 case VPX_IMG_FMT_YV12 : case VPX_IMG_FMT_I420 : return 12 ;
 case VPX_IMG_FMT_I422 : return 16 ;
 case VPX_IMG_FMT_I444 : return 24 ;
 case VPX_IMG_FMT_I42016 : return 24 ;
 case VPX_IMG_FMT_I42216 : return 32 ;
 case VPX_IMG_FMT_I44416 : return 48 ;
 default : assert ( 0 && "Invalid image format" ) ;
 break ;
 }
 return 0 ;
 }