static void nonrd_use_partition ( VP9_COMP * cpi , const TileInfo * const tile , MODE_INFO * * mi , TOKENEXTRA * * tp , int mi_row , int mi_col , BLOCK_SIZE bsize , int output_enabled , int * totrate , int64_t * totdist , PC_TREE * pc_tree ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 const int bsl = b_width_log2 ( bsize ) , hbs = ( 1 << bsl ) / 4 ;
 const int mis = cm -> mi_stride ;
 PARTITION_TYPE partition ;
 BLOCK_SIZE subsize ;
 int rate = INT_MAX ;
 int64_t dist = INT64_MAX ;
 if ( mi_row >= cm -> mi_rows || mi_col >= cm -> mi_cols ) return ;
 subsize = ( bsize >= BLOCK_8X8 ) ? mi [ 0 ] -> mbmi . sb_type : BLOCK_4X4 ;
 partition = partition_lookup [ bsl ] [ subsize ] ;
 switch ( partition ) {
 case PARTITION_NONE : nonrd_pick_sb_modes ( cpi , tile , mi_row , mi_col , totrate , totdist , subsize , & pc_tree -> none ) ;
 pc_tree -> none . mic . mbmi = xd -> mi [ 0 ] -> mbmi ;
 pc_tree -> none . skip_txfm [ 0 ] = x -> skip_txfm [ 0 ] ;
 pc_tree -> none . skip = x -> skip ;
 break ;
 case PARTITION_VERT : nonrd_pick_sb_modes ( cpi , tile , mi_row , mi_col , totrate , totdist , subsize , & pc_tree -> vertical [ 0 ] ) ;
 pc_tree -> vertical [ 0 ] . mic . mbmi = xd -> mi [ 0 ] -> mbmi ;
 pc_tree -> vertical [ 0 ] . skip_txfm [ 0 ] = x -> skip_txfm [ 0 ] ;
 pc_tree -> vertical [ 0 ] . skip = x -> skip ;
 if ( mi_col + hbs < cm -> mi_cols ) {
 nonrd_pick_sb_modes ( cpi , tile , mi_row , mi_col + hbs , & rate , & dist , subsize , & pc_tree -> vertical [ 1 ] ) ;
 pc_tree -> vertical [ 1 ] . mic . mbmi = xd -> mi [ 0 ] -> mbmi ;
 pc_tree -> vertical [ 1 ] . skip_txfm [ 0 ] = x -> skip_txfm [ 0 ] ;
 pc_tree -> vertical [ 1 ] . skip = x -> skip ;
 if ( rate != INT_MAX && dist != INT64_MAX && * totrate != INT_MAX && * totdist != INT64_MAX ) {
 * totrate += rate ;
 * totdist += dist ;
 }
 }
 break ;
 case PARTITION_HORZ : nonrd_pick_sb_modes ( cpi , tile , mi_row , mi_col , totrate , totdist , subsize , & pc_tree -> horizontal [ 0 ] ) ;
 pc_tree -> horizontal [ 0 ] . mic . mbmi = xd -> mi [ 0 ] -> mbmi ;
 pc_tree -> horizontal [ 0 ] . skip_txfm [ 0 ] = x -> skip_txfm [ 0 ] ;
 pc_tree -> horizontal [ 0 ] . skip = x -> skip ;
 if ( mi_row + hbs < cm -> mi_rows ) {
 nonrd_pick_sb_modes ( cpi , tile , mi_row + hbs , mi_col , & rate , & dist , subsize , & pc_tree -> horizontal [ 0 ] ) ;
 pc_tree -> horizontal [ 1 ] . mic . mbmi = xd -> mi [ 0 ] -> mbmi ;
 pc_tree -> horizontal [ 1 ] . skip_txfm [ 0 ] = x -> skip_txfm [ 0 ] ;
 pc_tree -> horizontal [ 1 ] . skip = x -> skip ;
 if ( rate != INT_MAX && dist != INT64_MAX && * totrate != INT_MAX && * totdist != INT64_MAX ) {
 * totrate += rate ;
 * totdist += dist ;
 }
 }
 break ;
 case PARTITION_SPLIT : subsize = get_subsize ( bsize , PARTITION_SPLIT ) ;
 nonrd_use_partition ( cpi , tile , mi , tp , mi_row , mi_col , subsize , output_enabled , totrate , totdist , pc_tree -> split [ 0 ] ) ;
 nonrd_use_partition ( cpi , tile , mi + hbs , tp , mi_row , mi_col + hbs , subsize , output_enabled , & rate , & dist , pc_tree -> split [ 1 ] ) ;
 if ( rate != INT_MAX && dist != INT64_MAX && * totrate != INT_MAX && * totdist != INT64_MAX ) {
 * totrate += rate ;
 * totdist += dist ;
 }
 nonrd_use_partition ( cpi , tile , mi + hbs * mis , tp , mi_row + hbs , mi_col , subsize , output_enabled , & rate , & dist , pc_tree -> split [ 2 ] ) ;
 if ( rate != INT_MAX && dist != INT64_MAX && * totrate != INT_MAX && * totdist != INT64_MAX ) {
 * totrate += rate ;
 * totdist += dist ;
 }
 nonrd_use_partition ( cpi , tile , mi + hbs * mis + hbs , tp , mi_row + hbs , mi_col + hbs , subsize , output_enabled , & rate , & dist , pc_tree -> split [ 3 ] ) ;
 if ( rate != INT_MAX && dist != INT64_MAX && * totrate != INT_MAX && * totdist != INT64_MAX ) {
 * totrate += rate ;
 * totdist += dist ;
 }
 break ;
 default : assert ( "Invalid partition type." ) ;
 break ;
 }
 if ( bsize == BLOCK_64X64 && output_enabled ) {
 if ( cpi -> oxcf . aq_mode == CYCLIC_REFRESH_AQ ) vp9_cyclic_refresh_set_rate_and_dist_sb ( cpi -> cyclic_refresh , * totrate , * totdist ) ;
 encode_sb_rt ( cpi , tile , tp , mi_row , mi_col , 1 , bsize , pc_tree ) ;
 }
 }