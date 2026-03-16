static void lag_pred_line_yuy2 ( LagarithContext * l , uint8_t * buf , int width , int stride , int line , int is_luma ) {
 int L , TL ;
 if ( ! line ) {
 if ( is_luma ) {
 buf ++ ;
 width -- ;
 }
 l -> dsp . add_hfyu_left_prediction ( buf + 1 , buf + 1 , width - 1 , buf [ 0 ] ) ;
 return ;
 }
 if ( line == 1 ) {
 const int HEAD = is_luma ? 4 : 2 ;
 int i ;
 L = buf [ width - stride - 1 ] ;
 TL = buf [ HEAD - stride - 1 ] ;
 for ( i = 0 ;
 i < HEAD ;
 i ++ ) {
 L += buf [ i ] ;
 buf [ i ] = L ;
 }
 buf += HEAD ;
 width -= HEAD ;
 }
 else {
 TL = buf [ width - ( 2 * stride ) - 1 ] ;
 L = buf [ width - stride - 1 ] ;
 }
 l -> dsp . add_hfyu_median_prediction ( buf , buf - stride , buf , width , & L , & TL ) ;
 }