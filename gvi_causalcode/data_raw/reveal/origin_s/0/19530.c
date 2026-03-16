static const char * image_format_to_string ( vpx_img_fmt_t f ) {
 switch ( f ) {
 case VPX_IMG_FMT_I420 : return "I420" ;
 case VPX_IMG_FMT_I422 : return "I422" ;
 case VPX_IMG_FMT_I444 : return "I444" ;
 case VPX_IMG_FMT_YV12 : return "YV12" ;
 default : return "Other" ;
 }
 }