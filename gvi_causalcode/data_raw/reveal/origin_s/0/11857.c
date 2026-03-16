static void build_mc_border ( const uint8_t * src , int src_stride , uint8_t * dst , int dst_stride , int x , int y , int b_w , int b_h , int w , int h ) {
 const uint8_t * ref_row = src - x - y * src_stride ;
 if ( y >= h ) ref_row += ( h - 1 ) * src_stride ;
 else if ( y > 0 ) ref_row += y * src_stride ;
 do {
 int right = 0 , copy ;
 int left = x < 0 ? - x : 0 ;
 if ( left > b_w ) left = b_w ;
 if ( x + b_w > w ) right = x + b_w - w ;
 if ( right > b_w ) right = b_w ;
 copy = b_w - left - right ;
 if ( left ) memset ( dst , ref_row [ 0 ] , left ) ;
 if ( copy ) memcpy ( dst + left , ref_row + x + left , copy ) ;
 if ( right ) memset ( dst + left + copy , ref_row [ w - 1 ] , right ) ;
 dst += dst_stride ;
 ++ y ;
 if ( y > 0 && y < h ) ref_row += src_stride ;
 }
 while ( -- b_h ) ;
 }