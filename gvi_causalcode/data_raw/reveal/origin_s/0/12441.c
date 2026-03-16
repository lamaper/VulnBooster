void vp9_initialize_rd_consts ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCK * const x = & cpi -> mb ;
 RD_OPT * const rd = & cpi -> rd ;
 int i ;
 vp9_clear_system_state ( ) ;
 rd -> RDDIV = RDDIV_BITS ;
 rd -> RDMULT = vp9_compute_rd_mult ( cpi , cm -> base_qindex + cm -> y_dc_delta_q ) ;
 x -> errorperbit = rd -> RDMULT / RD_MULT_EPB_RATIO ;
 x -> errorperbit += ( x -> errorperbit == 0 ) ;
 x -> select_tx_size = ( cpi -> sf . tx_size_search_method == USE_LARGESTALL && cm -> frame_type != KEY_FRAME ) ? 0 : 1 ;
 set_block_thresholds ( cm , rd ) ;
 if ( ! cpi -> sf . use_nonrd_pick_mode || cm -> frame_type == KEY_FRAME ) {
 fill_token_costs ( x -> token_costs , cm -> fc . coef_probs ) ;
 for ( i = 0 ;
 i < PARTITION_CONTEXTS ;
 ++ i ) vp9_cost_tokens ( cpi -> partition_cost [ i ] , get_partition_probs ( cm , i ) , vp9_partition_tree ) ;
 }
 if ( ! cpi -> sf . use_nonrd_pick_mode || ( cm -> current_video_frame & 0x07 ) == 1 || cm -> frame_type == KEY_FRAME ) {
 fill_mode_costs ( cpi ) ;
 if ( ! frame_is_intra_only ( cm ) ) {
 vp9_build_nmv_cost_table ( x -> nmvjointcost , cm -> allow_high_precision_mv ? x -> nmvcost_hp : x -> nmvcost , & cm -> fc . nmvc , cm -> allow_high_precision_mv ) ;
 for ( i = 0 ;
 i < INTER_MODE_CONTEXTS ;
 ++ i ) vp9_cost_tokens ( ( int * ) cpi -> inter_mode_cost [ i ] , cm -> fc . inter_mode_probs [ i ] , vp9_inter_mode_tree ) ;
 }
 }
 }