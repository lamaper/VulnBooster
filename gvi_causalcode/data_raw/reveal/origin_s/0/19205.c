static void encode_sb ( VP9_COMP * cpi , const TileInfo * const tile , TOKENEXTRA * * tp , int mi_row , int mi_col , int output_enabled , BLOCK_SIZE bsize , PC_TREE * pc_tree ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 const int bsl = b_width_log2 ( bsize ) , hbs = ( 1 << bsl ) / 4 ;
 int ctx ;
 PARTITION_TYPE partition ;
 BLOCK_SIZE subsize = bsize ;
 if ( mi_row >= cm -> mi_rows || mi_col >= cm -> mi_cols ) return ;
 if ( bsize >= BLOCK_8X8 ) {
 ctx = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 subsize = get_subsize ( bsize , pc_tree -> partitioning ) ;
 }
 else {
 ctx = 0 ;
 subsize = BLOCK_4X4 ;
 }
 partition = partition_lookup [ bsl ] [ subsize ] ;
 if ( output_enabled && bsize != BLOCK_4X4 ) cm -> counts . partition [ ctx ] [ partition ] ++ ;
 switch ( partition ) {
 case PARTITION_NONE : encode_b ( cpi , tile , tp , mi_row , mi_col , output_enabled , subsize , & pc_tree -> none ) ;
 break ;
 case PARTITION_VERT : encode_b ( cpi , tile , tp , mi_row , mi_col , output_enabled , subsize , & pc_tree -> vertical [ 0 ] ) ;
 if ( mi_col + hbs < cm -> mi_cols && bsize > BLOCK_8X8 ) {
 encode_b ( cpi , tile , tp , mi_row , mi_col + hbs , output_enabled , subsize , & pc_tree -> vertical [ 1 ] ) ;
 }
 break ;
 case PARTITION_HORZ : encode_b ( cpi , tile , tp , mi_row , mi_col , output_enabled , subsize , & pc_tree -> horizontal [ 0 ] ) ;
 if ( mi_row + hbs < cm -> mi_rows && bsize > BLOCK_8X8 ) {
 encode_b ( cpi , tile , tp , mi_row + hbs , mi_col , output_enabled , subsize , & pc_tree -> horizontal [ 1 ] ) ;
 }
 break ;
 case PARTITION_SPLIT : if ( bsize == BLOCK_8X8 ) {
 encode_b ( cpi , tile , tp , mi_row , mi_col , output_enabled , subsize , pc_tree -> leaf_split [ 0 ] ) ;
 }
 else {
 encode_sb ( cpi , tile , tp , mi_row , mi_col , output_enabled , subsize , pc_tree -> split [ 0 ] ) ;
 encode_sb ( cpi , tile , tp , mi_row , mi_col + hbs , output_enabled , subsize , pc_tree -> split [ 1 ] ) ;
 encode_sb ( cpi , tile , tp , mi_row + hbs , mi_col , output_enabled , subsize , pc_tree -> split [ 2 ] ) ;
 encode_sb ( cpi , tile , tp , mi_row + hbs , mi_col + hbs , output_enabled , subsize , pc_tree -> split [ 3 ] ) ;
 }
 break ;
 default : assert ( "Invalid partition type." ) ;
 break ;
 }
 if ( partition != PARTITION_SPLIT || bsize == BLOCK_8X8 ) update_partition_context ( xd , mi_row , mi_col , subsize , bsize ) ;
 }