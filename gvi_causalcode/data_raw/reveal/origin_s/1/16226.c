static int optimize_b ( MACROBLOCK * mb , int plane , int block , TX_SIZE tx_size , int ctx ) {
 MACROBLOCKD * const xd = & mb -> e_mbd ;
 struct macroblock_plane * const p = & mb -> plane [ plane ] ;
 struct macroblockd_plane * const pd = & xd -> plane [ plane ] ;
 const int ref = is_inter_block ( & xd -> mi [ 0 ] -> mbmi ) ;
 vp9_token_state tokens [ 1025 ] [ 2 ] ;
 unsigned best_index [ 1025 ] [ 2 ] ;
 uint8_t token_cache [ 1024 ] ;
 const int16_t * const coeff = BLOCK_OFFSET ( mb -> plane [ plane ] . coeff , block ) ;
 int16_t * const qcoeff = BLOCK_OFFSET ( p -> qcoeff , block ) ;
 int16_t * const dqcoeff = BLOCK_OFFSET ( pd -> dqcoeff , block ) ;
 const int eob = p -> eobs [ block ] ;
 const PLANE_TYPE type = pd -> plane_type ;
 const int default_eob = 16 << ( tx_size << 1 ) ;
 const int mul = 1 + ( tx_size == TX_32X32 ) ;
 const int16_t * dequant_ptr = pd -> dequant ;
 const uint8_t * const band_translate = get_band_translate ( tx_size ) ;
 const scan_order * const so = get_scan ( xd , tx_size , type , block ) ;
 const int16_t * const scan = so -> scan ;
 const int16_t * const nb = so -> neighbors ;
 int next = eob , sz = 0 ;
 int64_t rdmult = mb -> rdmult * plane_rd_mult [ type ] , rddiv = mb -> rddiv ;
 int64_t rd_cost0 , rd_cost1 ;
 int rate0 , rate1 , error0 , error1 , t0 , t1 ;
 int best , band , pt , i , final_eob ;
 assert ( ( ! type && ! plane ) || ( type && plane ) ) ;
 assert ( eob <= default_eob ) ;
 if ( ! ref ) rdmult = ( rdmult * 9 ) >> 4 ;
 tokens [ eob ] [ 0 ] . rate = 0 ;
 tokens [ eob ] [ 0 ] . error = 0 ;
 tokens [ eob ] [ 0 ] . next = default_eob ;
 tokens [ eob ] [ 0 ] . token = EOB_TOKEN ;
 tokens [ eob ] [ 0 ] . qc = 0 ;
 tokens [ eob ] [ 1 ] = tokens [ eob ] [ 0 ] ;
 for ( i = 0 ;
 i < eob ;
 i ++ ) token_cache [ scan [ i ] ] = vp9_pt_energy_class [ vp9_dct_value_tokens_ptr [ qcoeff [ scan [ i ] ] ] . token ] ;
 for ( i = eob ;
 i -- > 0 ;
 ) {
 int base_bits , d2 , dx ;
 const int rc = scan [ i ] ;
 int x = qcoeff [ rc ] ;
 if ( x ) {
 int shortcut = 0 ;
 error0 = tokens [ next ] [ 0 ] . error ;
 error1 = tokens [ next ] [ 1 ] . error ;
 rate0 = tokens [ next ] [ 0 ] . rate ;
 rate1 = tokens [ next ] [ 1 ] . rate ;
 t0 = ( vp9_dct_value_tokens_ptr + x ) -> token ;
 if ( next < default_eob ) {
 band = band_translate [ i + 1 ] ;
 pt = trellis_get_coeff_context ( scan , nb , i , t0 , token_cache ) ;
 rate0 += mb -> token_costs [ tx_size ] [ type ] [ ref ] [ band ] [ 0 ] [ pt ] [ tokens [ next ] [ 0 ] . token ] ;
 rate1 += mb -> token_costs [ tx_size ] [ type ] [ ref ] [ band ] [ 0 ] [ pt ] [ tokens [ next ] [ 1 ] . token ] ;
 }
 UPDATE_RD_COST ( ) ;
 best = rd_cost1 < rd_cost0 ;
 base_bits = vp9_dct_value_cost_ptr [ x ] ;
 dx = mul * ( dqcoeff [ rc ] - coeff [ rc ] ) ;
 d2 = dx * dx ;
 tokens [ i ] [ 0 ] . rate = base_bits + ( best ? rate1 : rate0 ) ;
 tokens [ i ] [ 0 ] . error = d2 + ( best ? error1 : error0 ) ;
 tokens [ i ] [ 0 ] . next = next ;
 tokens [ i ] [ 0 ] . token = t0 ;
 tokens [ i ] [ 0 ] . qc = x ;
 best_index [ i ] [ 0 ] = best ;
 rate0 = tokens [ next ] [ 0 ] . rate ;
 rate1 = tokens [ next ] [ 1 ] . rate ;
 if ( ( abs ( x ) * dequant_ptr [ rc != 0 ] > abs ( coeff [ rc ] ) * mul ) && ( abs ( x ) * dequant_ptr [ rc != 0 ] < abs ( coeff [ rc ] ) * mul + dequant_ptr [ rc != 0 ] ) ) shortcut = 1 ;
 else shortcut = 0 ;
 if ( shortcut ) {
 sz = - ( x < 0 ) ;
 x -= 2 * sz + 1 ;
 }
 if ( ! x ) {
 t0 = tokens [ next ] [ 0 ] . token == EOB_TOKEN ? EOB_TOKEN : ZERO_TOKEN ;
 t1 = tokens [ next ] [ 1 ] . token == EOB_TOKEN ? EOB_TOKEN : ZERO_TOKEN ;
 }
 else {
 t0 = t1 = ( vp9_dct_value_tokens_ptr + x ) -> token ;
 }
 if ( next < default_eob ) {
 band = band_translate [ i + 1 ] ;
 if ( t0 != EOB_TOKEN ) {
 pt = trellis_get_coeff_context ( scan , nb , i , t0 , token_cache ) ;
 rate0 += mb -> token_costs [ tx_size ] [ type ] [ ref ] [ band ] [ ! x ] [ pt ] [ tokens [ next ] [ 0 ] . token ] ;
 }
 if ( t1 != EOB_TOKEN ) {
 pt = trellis_get_coeff_context ( scan , nb , i , t1 , token_cache ) ;
 rate1 += mb -> token_costs [ tx_size ] [ type ] [ ref ] [ band ] [ ! x ] [ pt ] [ tokens [ next ] [ 1 ] . token ] ;
 }
 }
 UPDATE_RD_COST ( ) ;
 best = rd_cost1 < rd_cost0 ;
 base_bits = vp9_dct_value_cost_ptr [ x ] ;
 if ( shortcut ) {
 dx -= ( dequant_ptr [ rc != 0 ] + sz ) ^ sz ;
 d2 = dx * dx ;
 }
 tokens [ i ] [ 1 ] . rate = base_bits + ( best ? rate1 : rate0 ) ;
 tokens [ i ] [ 1 ] . error = d2 + ( best ? error1 : error0 ) ;
 tokens [ i ] [ 1 ] . next = next ;
 tokens [ i ] [ 1 ] . token = best ? t1 : t0 ;
 tokens [ i ] [ 1 ] . qc = x ;
 best_index [ i ] [ 1 ] = best ;
 next = i ;
 }
 else {
 band = band_translate [ i + 1 ] ;
 t0 = tokens [ next ] [ 0 ] . token ;
 t1 = tokens [ next ] [ 1 ] . token ;
 if ( t0 != EOB_TOKEN ) {
 tokens [ next ] [ 0 ] . rate += mb -> token_costs [ tx_size ] [ type ] [ ref ] [ band ] [ 1 ] [ 0 ] [ t0 ] ;
 tokens [ next ] [ 0 ] . token = ZERO_TOKEN ;
 }
 if ( t1 != EOB_TOKEN ) {
 tokens [ next ] [ 1 ] . rate += mb -> token_costs [ tx_size ] [ type ] [ ref ] [ band ] [ 1 ] [ 0 ] [ t1 ] ;
 tokens [ next ] [ 1 ] . token = ZERO_TOKEN ;
 }
 best_index [ i ] [ 0 ] = best_index [ i ] [ 1 ] = 0 ;
 }
 }
 band = band_translate [ i + 1 ] ;
 rate0 = tokens [ next ] [ 0 ] . rate ;
 rate1 = tokens [ next ] [ 1 ] . rate ;
 error0 = tokens [ next ] [ 0 ] . error ;
 error1 = tokens [ next ] [ 1 ] . error ;
 t0 = tokens [ next ] [ 0 ] . token ;
 t1 = tokens [ next ] [ 1 ] . token ;
 rate0 += mb -> token_costs [ tx_size ] [ type ] [ ref ] [ band ] [ 0 ] [ ctx ] [ t0 ] ;
 rate1 += mb -> token_costs [ tx_size ] [ type ] [ ref ] [ band ] [ 0 ] [ ctx ] [ t1 ] ;
 UPDATE_RD_COST ( ) ;
 best = rd_cost1 < rd_cost0 ;
 final_eob = - 1 ;
 vpx_memset ( qcoeff , 0 , sizeof ( * qcoeff ) * ( 16 << ( tx_size * 2 ) ) ) ;
 vpx_memset ( dqcoeff , 0 , sizeof ( * dqcoeff ) * ( 16 << ( tx_size * 2 ) ) ) ;
 for ( i = next ;
 i < eob ;
 i = next ) {
 const int x = tokens [ i ] [ best ] . qc ;
 const int rc = scan [ i ] ;
 if ( x ) {
 final_eob = i ;
 }
 qcoeff [ rc ] = x ;
 dqcoeff [ rc ] = ( x * dequant_ptr [ rc != 0 ] ) / mul ;
 next = tokens [ i ] [ best ] . next ;
 best = best_index [ i ] [ best ] ;
 }
 final_eob ++ ;
 mb -> plane [ plane ] . eobs [ block ] = final_eob ;
 return final_eob ;
 }