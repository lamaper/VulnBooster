static void find_mismatch ( const vpx_image_t * const img1 , const vpx_image_t * const img2 , int yloc [ 4 ] , int uloc [ 4 ] , int vloc [ 4 ] ) {
 const uint32_t bsize = 64 ;
 const uint32_t bsizey = bsize >> img1 -> y_chroma_shift ;
 const uint32_t bsizex = bsize >> img1 -> x_chroma_shift ;
 const uint32_t c_w = ( img1 -> d_w + img1 -> x_chroma_shift ) >> img1 -> x_chroma_shift ;
 const uint32_t c_h = ( img1 -> d_h + img1 -> y_chroma_shift ) >> img1 -> y_chroma_shift ;
 int match = 1 ;
 uint32_t i , j ;
 yloc [ 0 ] = yloc [ 1 ] = yloc [ 2 ] = yloc [ 3 ] = - 1 ;
 for ( i = 0 , match = 1 ;
 match && i < img1 -> d_h ;
 i += bsize ) {
 for ( j = 0 ;
 match && j < img1 -> d_w ;
 j += bsize ) {
 int k , l ;
 const int si = mmin ( i + bsize , img1 -> d_h ) - i ;
 const int sj = mmin ( j + bsize , img1 -> d_w ) - j ;
 for ( k = 0 ;
 match && k < si ;
 ++ k ) {
 for ( l = 0 ;
 match && l < sj ;
 ++ l ) {
 if ( * ( img1 -> planes [ VPX_PLANE_Y ] + ( i + k ) * img1 -> stride [ VPX_PLANE_Y ] + j + l ) != * ( img2 -> planes [ VPX_PLANE_Y ] + ( i + k ) * img2 -> stride [ VPX_PLANE_Y ] + j + l ) ) {
 yloc [ 0 ] = i + k ;
 yloc [ 1 ] = j + l ;
 yloc [ 2 ] = * ( img1 -> planes [ VPX_PLANE_Y ] + ( i + k ) * img1 -> stride [ VPX_PLANE_Y ] + j + l ) ;
 yloc [ 3 ] = * ( img2 -> planes [ VPX_PLANE_Y ] + ( i + k ) * img2 -> stride [ VPX_PLANE_Y ] + j + l ) ;
 match = 0 ;
 break ;
 }
 }
 }
 }
 }
 uloc [ 0 ] = uloc [ 1 ] = uloc [ 2 ] = uloc [ 3 ] = - 1 ;
 for ( i = 0 , match = 1 ;
 match && i < c_h ;
 i += bsizey ) {
 for ( j = 0 ;
 match && j < c_w ;
 j += bsizex ) {
 int k , l ;
 const int si = mmin ( i + bsizey , c_h - i ) ;
 const int sj = mmin ( j + bsizex , c_w - j ) ;
 for ( k = 0 ;
 match && k < si ;
 ++ k ) {
 for ( l = 0 ;
 match && l < sj ;
 ++ l ) {
 if ( * ( img1 -> planes [ VPX_PLANE_U ] + ( i + k ) * img1 -> stride [ VPX_PLANE_U ] + j + l ) != * ( img2 -> planes [ VPX_PLANE_U ] + ( i + k ) * img2 -> stride [ VPX_PLANE_U ] + j + l ) ) {
 uloc [ 0 ] = i + k ;
 uloc [ 1 ] = j + l ;
 uloc [ 2 ] = * ( img1 -> planes [ VPX_PLANE_U ] + ( i + k ) * img1 -> stride [ VPX_PLANE_U ] + j + l ) ;
 uloc [ 3 ] = * ( img2 -> planes [ VPX_PLANE_U ] + ( i + k ) * img2 -> stride [ VPX_PLANE_U ] + j + l ) ;
 match = 0 ;
 break ;
 }
 }
 }
 }
 }
 vloc [ 0 ] = vloc [ 1 ] = vloc [ 2 ] = vloc [ 3 ] = - 1 ;
 for ( i = 0 , match = 1 ;
 match && i < c_h ;
 i += bsizey ) {
 for ( j = 0 ;
 match && j < c_w ;
 j += bsizex ) {
 int k , l ;
 const int si = mmin ( i + bsizey , c_h - i ) ;
 const int sj = mmin ( j + bsizex , c_w - j ) ;
 for ( k = 0 ;
 match && k < si ;
 ++ k ) {
 for ( l = 0 ;
 match && l < sj ;
 ++ l ) {
 if ( * ( img1 -> planes [ VPX_PLANE_V ] + ( i + k ) * img1 -> stride [ VPX_PLANE_V ] + j + l ) != * ( img2 -> planes [ VPX_PLANE_V ] + ( i + k ) * img2 -> stride [ VPX_PLANE_V ] + j + l ) ) {
 vloc [ 0 ] = i + k ;
 vloc [ 1 ] = j + l ;
 vloc [ 2 ] = * ( img1 -> planes [ VPX_PLANE_V ] + ( i + k ) * img1 -> stride [ VPX_PLANE_V ] + j + l ) ;
 vloc [ 3 ] = * ( img2 -> planes [ VPX_PLANE_V ] + ( i + k ) * img2 -> stride [ VPX_PLANE_V ] + j + l ) ;
 match = 0 ;
 break ;
 }
 }
 }
 }
 }
 }