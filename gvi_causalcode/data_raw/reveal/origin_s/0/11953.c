static void decode_partition ( VP9_COMMON * const cm , MACROBLOCKD * const xd , const TileInfo * const tile , int mi_row , int mi_col , vp9_reader * r , BLOCK_SIZE bsize ) {
 const int hbs = num_8x8_blocks_wide_lookup [ bsize ] / 2 ;
 PARTITION_TYPE partition ;
 BLOCK_SIZE subsize , uv_subsize ;
 if ( mi_row >= cm -> mi_rows || mi_col >= cm -> mi_cols ) return ;
 partition = read_partition ( cm , xd , hbs , mi_row , mi_col , bsize , r ) ;
 subsize = get_subsize ( bsize , partition ) ;
 uv_subsize = ss_size_lookup [ subsize ] [ cm -> subsampling_x ] [ cm -> subsampling_y ] ;
 if ( subsize >= BLOCK_8X8 && uv_subsize == BLOCK_INVALID ) vpx_internal_error ( & cm -> error , VPX_CODEC_CORRUPT_FRAME , "Invalid block size." ) ;
 if ( subsize < BLOCK_8X8 ) {
 decode_block ( cm , xd , tile , mi_row , mi_col , r , subsize ) ;
 }
 else {
 switch ( partition ) {
 case PARTITION_NONE : decode_block ( cm , xd , tile , mi_row , mi_col , r , subsize ) ;
 break ;
 case PARTITION_HORZ : decode_block ( cm , xd , tile , mi_row , mi_col , r , subsize ) ;
 if ( mi_row + hbs < cm -> mi_rows ) decode_block ( cm , xd , tile , mi_row + hbs , mi_col , r , subsize ) ;
 break ;
 case PARTITION_VERT : decode_block ( cm , xd , tile , mi_row , mi_col , r , subsize ) ;
 if ( mi_col + hbs < cm -> mi_cols ) decode_block ( cm , xd , tile , mi_row , mi_col + hbs , r , subsize ) ;
 break ;
 case PARTITION_SPLIT : decode_partition ( cm , xd , tile , mi_row , mi_col , r , subsize ) ;
 decode_partition ( cm , xd , tile , mi_row , mi_col + hbs , r , subsize ) ;
 decode_partition ( cm , xd , tile , mi_row + hbs , mi_col , r , subsize ) ;
 decode_partition ( cm , xd , tile , mi_row + hbs , mi_col + hbs , r , subsize ) ;
 break ;
 default : assert ( 0 && "Invalid partition type" ) ;
 }
 }
 if ( bsize >= BLOCK_8X8 && ( bsize == BLOCK_8X8 || partition != PARTITION_SPLIT ) ) update_partition_context ( xd , mi_row , mi_col , subsize , bsize ) ;
 }