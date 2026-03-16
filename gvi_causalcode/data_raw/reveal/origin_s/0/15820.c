void vp9_encode_frame ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 RD_OPT * const rd_opt = & cpi -> rd ;
 if ( ! frame_is_intra_only ( cm ) ) {
 if ( ( cm -> ref_frame_sign_bias [ ALTREF_FRAME ] == cm -> ref_frame_sign_bias [ GOLDEN_FRAME ] ) || ( cm -> ref_frame_sign_bias [ ALTREF_FRAME ] == cm -> ref_frame_sign_bias [ LAST_FRAME ] ) ) {
 cm -> allow_comp_inter_inter = 0 ;
 }
 else {
 cm -> allow_comp_inter_inter = 1 ;
 cm -> comp_fixed_ref = ALTREF_FRAME ;
 cm -> comp_var_ref [ 0 ] = LAST_FRAME ;
 cm -> comp_var_ref [ 1 ] = GOLDEN_FRAME ;
 }
 }
 if ( cpi -> sf . frame_parameter_update ) {
 int i ;
 const MV_REFERENCE_FRAME frame_type = get_frame_type ( cpi ) ;
 int64_t * const mode_thrs = rd_opt -> prediction_type_threshes [ frame_type ] ;
 int64_t * const filter_thrs = rd_opt -> filter_threshes [ frame_type ] ;
 int * const tx_thrs = rd_opt -> tx_select_threshes [ frame_type ] ;
 const int is_alt_ref = frame_type == ALTREF_FRAME ;
 if ( is_alt_ref || ! cm -> allow_comp_inter_inter ) cm -> reference_mode = SINGLE_REFERENCE ;
 else if ( mode_thrs [ COMPOUND_REFERENCE ] > mode_thrs [ SINGLE_REFERENCE ] && mode_thrs [ COMPOUND_REFERENCE ] > mode_thrs [ REFERENCE_MODE_SELECT ] && check_dual_ref_flags ( cpi ) && cpi -> static_mb_pct == 100 ) cm -> reference_mode = COMPOUND_REFERENCE ;
 else if ( mode_thrs [ SINGLE_REFERENCE ] > mode_thrs [ REFERENCE_MODE_SELECT ] ) cm -> reference_mode = SINGLE_REFERENCE ;
 else cm -> reference_mode = REFERENCE_MODE_SELECT ;
 if ( cm -> interp_filter == SWITCHABLE ) cm -> interp_filter = get_interp_filter ( filter_thrs , is_alt_ref ) ;
 encode_frame_internal ( cpi ) ;
 for ( i = 0 ;
 i < REFERENCE_MODES ;
 ++ i ) mode_thrs [ i ] = ( mode_thrs [ i ] + rd_opt -> comp_pred_diff [ i ] / cm -> MBs ) / 2 ;
 for ( i = 0 ;
 i < SWITCHABLE_FILTER_CONTEXTS ;
 ++ i ) filter_thrs [ i ] = ( filter_thrs [ i ] + rd_opt -> filter_diff [ i ] / cm -> MBs ) / 2 ;
 for ( i = 0 ;
 i < TX_MODES ;
 ++ i ) {
 int64_t pd = rd_opt -> tx_select_diff [ i ] ;
 if ( i == TX_MODE_SELECT ) pd -= RDCOST ( cpi -> mb . rdmult , cpi -> mb . rddiv , 2048 * ( TX_SIZES - 1 ) , 0 ) ;
 tx_thrs [ i ] = ( tx_thrs [ i ] + ( int ) ( pd / cm -> MBs ) ) / 2 ;
 }
 if ( cm -> reference_mode == REFERENCE_MODE_SELECT ) {
 int single_count_zero = 0 ;
 int comp_count_zero = 0 ;
 for ( i = 0 ;
 i < COMP_INTER_CONTEXTS ;
 i ++ ) {
 single_count_zero += cm -> counts . comp_inter [ i ] [ 0 ] ;
 comp_count_zero += cm -> counts . comp_inter [ i ] [ 1 ] ;
 }
 if ( comp_count_zero == 0 ) {
 cm -> reference_mode = SINGLE_REFERENCE ;
 vp9_zero ( cm -> counts . comp_inter ) ;
 }
 else if ( single_count_zero == 0 ) {
 cm -> reference_mode = COMPOUND_REFERENCE ;
 vp9_zero ( cm -> counts . comp_inter ) ;
 }
 }
 if ( cm -> tx_mode == TX_MODE_SELECT ) {
 int count4x4 = 0 ;
 int count8x8_lp = 0 , count8x8_8x8p = 0 ;
 int count16x16_16x16p = 0 , count16x16_lp = 0 ;
 int count32x32 = 0 ;
 for ( i = 0 ;
 i < TX_SIZE_CONTEXTS ;
 ++ i ) {
 count4x4 += cm -> counts . tx . p32x32 [ i ] [ TX_4X4 ] ;
 count4x4 += cm -> counts . tx . p16x16 [ i ] [ TX_4X4 ] ;
 count4x4 += cm -> counts . tx . p8x8 [ i ] [ TX_4X4 ] ;
 count8x8_lp += cm -> counts . tx . p32x32 [ i ] [ TX_8X8 ] ;
 count8x8_lp += cm -> counts . tx . p16x16 [ i ] [ TX_8X8 ] ;
 count8x8_8x8p += cm -> counts . tx . p8x8 [ i ] [ TX_8X8 ] ;
 count16x16_16x16p += cm -> counts . tx . p16x16 [ i ] [ TX_16X16 ] ;
 count16x16_lp += cm -> counts . tx . p32x32 [ i ] [ TX_16X16 ] ;
 count32x32 += cm -> counts . tx . p32x32 [ i ] [ TX_32X32 ] ;
 }
 if ( count4x4 == 0 && count16x16_lp == 0 && count16x16_16x16p == 0 && count32x32 == 0 ) {
 cm -> tx_mode = ALLOW_8X8 ;
 reset_skip_tx_size ( cm , TX_8X8 ) ;
 }
 else if ( count8x8_8x8p == 0 && count16x16_16x16p == 0 && count8x8_lp == 0 && count16x16_lp == 0 && count32x32 == 0 ) {
 cm -> tx_mode = ONLY_4X4 ;
 reset_skip_tx_size ( cm , TX_4X4 ) ;
 }
 else if ( count8x8_lp == 0 && count16x16_lp == 0 && count4x4 == 0 ) {
 cm -> tx_mode = ALLOW_32X32 ;
 }
 else if ( count32x32 == 0 && count8x8_lp == 0 && count4x4 == 0 ) {
 cm -> tx_mode = ALLOW_16X16 ;
 reset_skip_tx_size ( cm , TX_16X16 ) ;
 }
 }
 }
 else {
 cm -> reference_mode = SINGLE_REFERENCE ;
 encode_frame_internal ( cpi ) ;
 }
 }