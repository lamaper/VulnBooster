static int calc_slice_sizes ( VC2EncContext * s ) {
 int i , j , slice_x , slice_y , bytes_left = 0 ;
 int bytes_top [ SLICE_REDIST_TOTAL ] = {
 0 }
 ;
 int64_t total_bytes_needed = 0 ;
 int slice_redist_range = FFMIN ( SLICE_REDIST_TOTAL , s -> num_x * s -> num_y ) ;
 SliceArgs * enc_args = s -> slice_args ;
 SliceArgs * top_loc [ SLICE_REDIST_TOTAL ] = {
 NULL }
 ;
 init_quant_matrix ( s ) ;
 for ( slice_y = 0 ;
 slice_y < s -> num_y ;
 slice_y ++ ) {
 for ( slice_x = 0 ;
 slice_x < s -> num_x ;
 slice_x ++ ) {
 SliceArgs * args = & enc_args [ s -> num_x * slice_y + slice_x ] ;
 args -> ctx = s ;
 args -> x = slice_x ;
 args -> y = slice_y ;
 args -> bits_ceil = s -> slice_max_bytes << 3 ;
 args -> bits_floor = s -> slice_min_bytes << 3 ;
 memset ( args -> cache , 0 , s -> q_ceil * sizeof ( * args -> cache ) ) ;
 }
 }
 s -> avctx -> execute ( s -> avctx , rate_control , enc_args , NULL , s -> num_x * s -> num_y , sizeof ( SliceArgs ) ) ;
 for ( i = 0 ;
 i < s -> num_x * s -> num_y ;
 i ++ ) {
 SliceArgs * args = & enc_args [ i ] ;
 bytes_left += s -> slice_max_bytes - args -> bytes ;
 for ( j = 0 ;
 j < slice_redist_range ;
 j ++ ) {
 if ( args -> bytes > bytes_top [ j ] ) {
 bytes_top [ j ] = args -> bytes ;
 top_loc [ j ] = args ;
 break ;
 }
 }
 }
 while ( 1 ) {
 int distributed = 0 ;
 for ( i = 0 ;
 i < slice_redist_range ;
 i ++ ) {
 SliceArgs * args ;
 int bits , bytes , diff , prev_bytes , new_idx ;
 if ( bytes_left <= 0 ) break ;
 if ( ! top_loc [ i ] || ! top_loc [ i ] -> quant_idx ) break ;
 args = top_loc [ i ] ;
 prev_bytes = args -> bytes ;
 new_idx = FFMAX ( args -> quant_idx - 1 , 0 ) ;
 bits = count_hq_slice ( args , new_idx ) ;
 bytes = SSIZE_ROUND ( bits >> 3 ) ;
 diff = bytes - prev_bytes ;
 if ( ( bytes_left - diff ) > 0 ) {
 args -> quant_idx = new_idx ;
 args -> bytes = bytes ;
 bytes_left -= diff ;
 distributed ++ ;
 }
 }
 if ( ! distributed ) break ;
 }
 for ( i = 0 ;
 i < s -> num_x * s -> num_y ;
 i ++ ) {
 SliceArgs * args = & enc_args [ i ] ;
 total_bytes_needed += args -> bytes ;
 s -> q_avg = ( s -> q_avg + args -> quant_idx ) / 2 ;
 }
 return total_bytes_needed ;
 }