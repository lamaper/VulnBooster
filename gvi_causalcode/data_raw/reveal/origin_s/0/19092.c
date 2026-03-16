static int compare_img ( const vpx_image_t * const img1 , const vpx_image_t * const img2 ) {
 uint32_t l_w = img1 -> d_w ;
 uint32_t c_w = ( img1 -> d_w + img1 -> x_chroma_shift ) >> img1 -> x_chroma_shift ;
 const uint32_t c_h = ( img1 -> d_h + img1 -> y_chroma_shift ) >> img1 -> y_chroma_shift ;
 uint32_t i ;
 int match = 1 ;
 match &= ( img1 -> fmt == img2 -> fmt ) ;
 match &= ( img1 -> d_w == img2 -> d_w ) ;
 match &= ( img1 -> d_h == img2 -> d_h ) ;

 l_w *= 2 ;
 c_w *= 2 ;
 }

 i < img1 -> d_h ;
 ++ i ) match &= ( memcmp ( img1 -> planes [ VPX_PLANE_Y ] + i * img1 -> stride [ VPX_PLANE_Y ] , img2 -> planes [ VPX_PLANE_Y ] + i * img2 -> stride [ VPX_PLANE_Y ] , l_w ) == 0 ) ;
 for ( i = 0 ;
 i < c_h ;
 ++ i ) match &= ( memcmp ( img1 -> planes [ VPX_PLANE_U ] + i * img1 -> stride [ VPX_PLANE_U ] , img2 -> planes [ VPX_PLANE_U ] + i * img2 -> stride [ VPX_PLANE_U ] , c_w ) == 0 ) ;
 for ( i = 0 ;
 i < c_h ;
 ++ i ) match &= ( memcmp ( img1 -> planes [ VPX_PLANE_V ] + i * img1 -> stride [ VPX_PLANE_V ] , img2 -> planes [ VPX_PLANE_V ] + i * img2 -> stride [ VPX_PLANE_V ] , c_w ) == 0 ) ;
 return match ;
 }