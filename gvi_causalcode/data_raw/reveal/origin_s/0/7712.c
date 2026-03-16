static int dct_quantize_trellis_c ( MpegEncContext * s , int16_t * block , int n , int qscale , int * overflow ) {
 const int * qmat ;
 const uint8_t * scantable = s -> intra_scantable . scantable ;
 const uint8_t * perm_scantable = s -> intra_scantable . permutated ;
 int max = 0 ;
 unsigned int threshold1 , threshold2 ;
 int bias = 0 ;
 int run_tab [ 65 ] ;
 int level_tab [ 65 ] ;
 int score_tab [ 65 ] ;
 int survivor [ 65 ] ;
 int survivor_count ;
 int last_run = 0 ;
 int last_level = 0 ;
 int last_score = 0 ;
 int last_i ;
 int coeff [ 2 ] [ 64 ] ;
 int coeff_count [ 64 ] ;
 int qmul , qadd , start_i , last_non_zero , i , dc ;
 const int esc_length = s -> ac_esc_length ;
 uint8_t * length ;
 uint8_t * last_length ;
 const int lambda = s -> lambda2 >> ( FF_LAMBDA_SHIFT - 6 ) ;
 s -> dsp . fdct ( block ) ;
 if ( s -> dct_error_sum ) s -> denoise_dct ( s , block ) ;
 qmul = qscale * 16 ;
 qadd = ( ( qscale - 1 ) | 1 ) * 8 ;
 if ( s -> mb_intra ) {
 int q ;
 if ( ! s -> h263_aic ) {
 if ( n < 4 ) q = s -> y_dc_scale ;
 else q = s -> c_dc_scale ;
 q = q << 3 ;
 }
 else {
 q = 1 << 3 ;
 qadd = 0 ;
 }
 block [ 0 ] = ( block [ 0 ] + ( q >> 1 ) ) / q ;
 start_i = 1 ;
 last_non_zero = 0 ;
 qmat = s -> q_intra_matrix [ qscale ] ;
 if ( s -> mpeg_quant || s -> out_format == FMT_MPEG1 ) bias = 1 << ( QMAT_SHIFT - 1 ) ;
 length = s -> intra_ac_vlc_length ;
 last_length = s -> intra_ac_vlc_last_length ;
 }
 else {
 start_i = 0 ;
 last_non_zero = - 1 ;
 qmat = s -> q_inter_matrix [ qscale ] ;
 length = s -> inter_ac_vlc_length ;
 last_length = s -> inter_ac_vlc_last_length ;
 }
 last_i = start_i ;
 threshold1 = ( 1 << QMAT_SHIFT ) - bias - 1 ;
 threshold2 = ( threshold1 << 1 ) ;
 for ( i = 63 ;
 i >= start_i ;
 i -- ) {
 const int j = scantable [ i ] ;
 int level = block [ j ] * qmat [ j ] ;
 if ( ( ( unsigned ) ( level + threshold1 ) ) > threshold2 ) {
 last_non_zero = i ;
 break ;
 }
 }
 for ( i = start_i ;
 i <= last_non_zero ;
 i ++ ) {
 const int j = scantable [ i ] ;
 int level = block [ j ] * qmat [ j ] ;
 if ( ( ( unsigned ) ( level + threshold1 ) ) > threshold2 ) {
 if ( level > 0 ) {
 level = ( bias + level ) >> QMAT_SHIFT ;
 coeff [ 0 ] [ i ] = level ;
 coeff [ 1 ] [ i ] = level - 1 ;
 }
 else {
 level = ( bias - level ) >> QMAT_SHIFT ;
 coeff [ 0 ] [ i ] = - level ;
 coeff [ 1 ] [ i ] = - level + 1 ;
 }
 coeff_count [ i ] = FFMIN ( level , 2 ) ;
 assert ( coeff_count [ i ] ) ;
 max |= level ;
 }
 else {
 coeff [ 0 ] [ i ] = ( level >> 31 ) | 1 ;
 coeff_count [ i ] = 1 ;
 }
 }
 * overflow = s -> max_qcoeff < max ;
 if ( last_non_zero < start_i ) {
 memset ( block + start_i , 0 , ( 64 - start_i ) * sizeof ( int16_t ) ) ;
 return last_non_zero ;
 }
 score_tab [ start_i ] = 0 ;
 survivor [ 0 ] = start_i ;
 survivor_count = 1 ;
 for ( i = start_i ;
 i <= last_non_zero ;
 i ++ ) {
 int level_index , j , zero_distortion ;
 int dct_coeff = FFABS ( block [ scantable [ i ] ] ) ;
 int best_score = 256 * 256 * 256 * 120 ;
 if ( s -> dsp . fdct == ff_fdct_ifast ) dct_coeff = ( dct_coeff * ff_inv_aanscales [ scantable [ i ] ] ) >> 12 ;
 zero_distortion = dct_coeff * dct_coeff ;
 for ( level_index = 0 ;
 level_index < coeff_count [ i ] ;
 level_index ++ ) {
 int distortion ;
 int level = coeff [ level_index ] [ i ] ;
 const int alevel = FFABS ( level ) ;
 int unquant_coeff ;
 assert ( level ) ;
 if ( s -> out_format == FMT_H263 ) {
 unquant_coeff = alevel * qmul + qadd ;
 }
 else {
 j = s -> dsp . idct_permutation [ scantable [ i ] ] ;
 if ( s -> mb_intra ) {
 unquant_coeff = ( int ) ( alevel * qscale * s -> intra_matrix [ j ] ) >> 3 ;
 unquant_coeff = ( unquant_coeff - 1 ) | 1 ;
 }
 else {
 unquant_coeff = ( ( ( alevel << 1 ) + 1 ) * qscale * ( ( int ) s -> inter_matrix [ j ] ) ) >> 4 ;
 unquant_coeff = ( unquant_coeff - 1 ) | 1 ;
 }
 unquant_coeff <<= 3 ;
 }
 distortion = ( unquant_coeff - dct_coeff ) * ( unquant_coeff - dct_coeff ) - zero_distortion ;
 level += 64 ;
 if ( ( level & ( ~ 127 ) ) == 0 ) {
 for ( j = survivor_count - 1 ;
 j >= 0 ;
 j -- ) {
 int run = i - survivor [ j ] ;
 int score = distortion + length [ UNI_AC_ENC_INDEX ( run , level ) ] * lambda ;
 score += score_tab [ i - run ] ;
 if ( score < best_score ) {
 best_score = score ;
 run_tab [ i + 1 ] = run ;
 level_tab [ i + 1 ] = level - 64 ;
 }
 }
 if ( s -> out_format == FMT_H263 ) {
 for ( j = survivor_count - 1 ;
 j >= 0 ;
 j -- ) {
 int run = i - survivor [ j ] ;
 int score = distortion + last_length [ UNI_AC_ENC_INDEX ( run , level ) ] * lambda ;
 score += score_tab [ i - run ] ;
 if ( score < last_score ) {
 last_score = score ;
 last_run = run ;
 last_level = level - 64 ;
 last_i = i + 1 ;
 }
 }
 }
 }
 else {
 distortion += esc_length * lambda ;
 for ( j = survivor_count - 1 ;
 j >= 0 ;
 j -- ) {
 int run = i - survivor [ j ] ;
 int score = distortion + score_tab [ i - run ] ;
 if ( score < best_score ) {
 best_score = score ;
 run_tab [ i + 1 ] = run ;
 level_tab [ i + 1 ] = level - 64 ;
 }
 }
 if ( s -> out_format == FMT_H263 ) {
 for ( j = survivor_count - 1 ;
 j >= 0 ;
 j -- ) {
 int run = i - survivor [ j ] ;
 int score = distortion + score_tab [ i - run ] ;
 if ( score < last_score ) {
 last_score = score ;
 last_run = run ;
 last_level = level - 64 ;
 last_i = i + 1 ;
 }
 }
 }
 }
 }
 score_tab [ i + 1 ] = best_score ;
 if ( last_non_zero <= 27 ) {
 for ( ;
 survivor_count ;
 survivor_count -- ) {
 if ( score_tab [ survivor [ survivor_count - 1 ] ] <= best_score ) break ;
 }
 }
 else {
 for ( ;
 survivor_count ;
 survivor_count -- ) {
 if ( score_tab [ survivor [ survivor_count - 1 ] ] <= best_score + lambda ) break ;
 }
 }
 survivor [ survivor_count ++ ] = i + 1 ;
 }
 if ( s -> out_format != FMT_H263 ) {
 last_score = 256 * 256 * 256 * 120 ;
 for ( i = survivor [ 0 ] ;
 i <= last_non_zero + 1 ;
 i ++ ) {
 int score = score_tab [ i ] ;
 if ( i ) score += lambda * 2 ;
 if ( score < last_score ) {
 last_score = score ;
 last_i = i ;
 last_level = level_tab [ i ] ;
 last_run = run_tab [ i ] ;
 }
 }
 }
 s -> coded_score [ n ] = last_score ;
 dc = FFABS ( block [ 0 ] ) ;
 last_non_zero = last_i - 1 ;
 memset ( block + start_i , 0 , ( 64 - start_i ) * sizeof ( int16_t ) ) ;
 if ( last_non_zero < start_i ) return last_non_zero ;
 if ( last_non_zero == 0 && start_i == 0 ) {
 int best_level = 0 ;
 int best_score = dc * dc ;
 for ( i = 0 ;
 i < coeff_count [ 0 ] ;
 i ++ ) {
 int level = coeff [ i ] [ 0 ] ;
 int alevel = FFABS ( level ) ;
 int unquant_coeff , score , distortion ;
 if ( s -> out_format == FMT_H263 ) {
 unquant_coeff = ( alevel * qmul + qadd ) >> 3 ;
 }
 else {
 unquant_coeff = ( ( ( alevel << 1 ) + 1 ) * qscale * ( ( int ) s -> inter_matrix [ 0 ] ) ) >> 4 ;
 unquant_coeff = ( unquant_coeff - 1 ) | 1 ;
 }
 unquant_coeff = ( unquant_coeff + 4 ) >> 3 ;
 unquant_coeff <<= 3 + 3 ;
 distortion = ( unquant_coeff - dc ) * ( unquant_coeff - dc ) ;
 level += 64 ;
 if ( ( level & ( ~ 127 ) ) == 0 ) score = distortion + last_length [ UNI_AC_ENC_INDEX ( 0 , level ) ] * lambda ;
 else score = distortion + esc_length * lambda ;
 if ( score < best_score ) {
 best_score = score ;
 best_level = level - 64 ;
 }
 }
 block [ 0 ] = best_level ;
 s -> coded_score [ n ] = best_score - dc * dc ;
 if ( best_level == 0 ) return - 1 ;
 else return last_non_zero ;
 }
 i = last_i ;
 assert ( last_level ) ;
 block [ perm_scantable [ last_non_zero ] ] = last_level ;
 i -= last_run + 1 ;
 for ( ;
 i > start_i ;
 i -= run_tab [ i ] + 1 ) {
 block [ perm_scantable [ i - 1 ] ] = level_tab [ i ] ;
 }
 return last_non_zero ;
 }