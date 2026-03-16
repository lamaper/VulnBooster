static int set_var_thresh_from_histogram ( VP9_COMP * cpi ) {
 const SPEED_FEATURES * const sf = & cpi -> sf ;
 const VP9_COMMON * const cm = & cpi -> common ;
 const uint8_t * src = cpi -> Source -> y_buffer ;
 const uint8_t * last_src = cpi -> Last_Source -> y_buffer ;
 const int src_stride = cpi -> Source -> y_stride ;
 const int last_stride = cpi -> Last_Source -> y_stride ;
 const int cutoff = ( MIN ( cm -> width , cm -> height ) >= 720 ) ? ( cm -> MBs * VAR_HIST_LARGE_CUT_OFF / 100 ) : ( cm -> MBs * VAR_HIST_SMALL_CUT_OFF / 100 ) ;
 DECLARE_ALIGNED_ARRAY ( 16 , int , hist , VAR_HIST_BINS ) ;
 diff * var16 = cpi -> source_diff_var ;
 int sum = 0 ;
 int i , j ;
 vpx_memset ( hist , 0 , VAR_HIST_BINS * sizeof ( hist [ 0 ] ) ) ;
 for ( i = 0 ;
 i < cm -> mb_rows ;
 i ++ ) {
 for ( j = 0 ;
 j < cm -> mb_cols ;
 j ++ ) {
 vp9_get16x16var ( src , src_stride , last_src , last_stride , & var16 -> sse , & var16 -> sum ) ;
 var16 -> var = var16 -> sse - ( ( ( uint32_t ) var16 -> sum * var16 -> sum ) >> 8 ) ;
 if ( var16 -> var >= VAR_HIST_MAX_BG_VAR ) hist [ VAR_HIST_BINS - 1 ] ++ ;
 else hist [ var16 -> var / VAR_HIST_FACTOR ] ++ ;
 src += 16 ;
 last_src += 16 ;
 var16 ++ ;
 }
 src = src - cm -> mb_cols * 16 + 16 * src_stride ;
 last_src = last_src - cm -> mb_cols * 16 + 16 * last_stride ;
 }
 cpi -> source_var_thresh = 0 ;
 if ( hist [ VAR_HIST_BINS - 1 ] < cutoff ) {
 for ( i = 0 ;
 i < VAR_HIST_BINS - 1 ;
 i ++ ) {
 sum += hist [ i ] ;
 if ( sum > cutoff ) {
 cpi -> source_var_thresh = ( i + 1 ) * VAR_HIST_FACTOR ;
 return 0 ;
 }
 }
 }
 return sf -> search_type_check_frequency ;
 }