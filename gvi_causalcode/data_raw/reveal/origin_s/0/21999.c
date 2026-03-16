void vp8_post_proc_down_and_across_mb_row_c ( unsigned char * src_ptr , unsigned char * dst_ptr , int src_pixels_per_line , int dst_pixels_per_line , int cols , unsigned char * f , int size ) {
 unsigned char * p_src , * p_dst ;
 int row ;
 int col ;
 unsigned char v ;
 unsigned char d [ 4 ] ;
 for ( row = 0 ;
 row < size ;
 row ++ ) {
 p_src = src_ptr ;
 p_dst = dst_ptr ;
 for ( col = 0 ;
 col < cols ;
 col ++ ) {
 unsigned char p_above2 = p_src [ col - 2 * src_pixels_per_line ] ;
 unsigned char p_above1 = p_src [ col - src_pixels_per_line ] ;
 unsigned char p_below1 = p_src [ col + src_pixels_per_line ] ;
 unsigned char p_below2 = p_src [ col + 2 * src_pixels_per_line ] ;
 v = p_src [ col ] ;
 if ( ( abs ( v - p_above2 ) < f [ col ] ) && ( abs ( v - p_above1 ) < f [ col ] ) && ( abs ( v - p_below1 ) < f [ col ] ) && ( abs ( v - p_below2 ) < f [ col ] ) ) {
 unsigned char k1 , k2 , k3 ;
 k1 = ( p_above2 + p_above1 + 1 ) >> 1 ;
 k2 = ( p_below2 + p_below1 + 1 ) >> 1 ;
 k3 = ( k1 + k2 + 1 ) >> 1 ;
 v = ( k3 + v + 1 ) >> 1 ;
 }
 p_dst [ col ] = v ;
 }
 p_src = dst_ptr ;
 p_dst = dst_ptr ;
 p_src [ - 2 ] = p_src [ - 1 ] = p_src [ 0 ] ;
 p_src [ cols ] = p_src [ cols + 1 ] = p_src [ cols - 1 ] ;
 for ( col = 0 ;
 col < cols ;
 col ++ ) {
 v = p_src [ col ] ;
 if ( ( abs ( v - p_src [ col - 2 ] ) < f [ col ] ) && ( abs ( v - p_src [ col - 1 ] ) < f [ col ] ) && ( abs ( v - p_src [ col + 1 ] ) < f [ col ] ) && ( abs ( v - p_src [ col + 2 ] ) < f [ col ] ) ) {
 unsigned char k1 , k2 , k3 ;
 k1 = ( p_src [ col - 2 ] + p_src [ col - 1 ] + 1 ) >> 1 ;
 k2 = ( p_src [ col + 2 ] + p_src [ col + 1 ] + 1 ) >> 1 ;
 k3 = ( k1 + k2 + 1 ) >> 1 ;
 v = ( k3 + v + 1 ) >> 1 ;
 }
 d [ col & 3 ] = v ;
 if ( col >= 2 ) p_dst [ col - 2 ] = d [ ( col - 2 ) & 3 ] ;
 }
 p_dst [ col - 2 ] = d [ ( col - 2 ) & 3 ] ;
 p_dst [ col - 1 ] = d [ ( col - 1 ) & 3 ] ;
 src_ptr += src_pixels_per_line ;
 dst_ptr += dst_pixels_per_line ;
 }
 }