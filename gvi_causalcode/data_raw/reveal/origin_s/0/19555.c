static void fill_mode_info_sb ( VP9_COMMON * cm , MACROBLOCK * x , int mi_row , int mi_col , BLOCK_SIZE bsize , BLOCK_SIZE subsize , PC_TREE * pc_tree ) {
 MACROBLOCKD * xd = & x -> e_mbd ;
 int bsl = b_width_log2 ( bsize ) , hbs = ( 1 << bsl ) / 4 ;
 PARTITION_TYPE partition = pc_tree -> partitioning ;
 assert ( bsize >= BLOCK_8X8 ) ;
 if ( mi_row >= cm -> mi_rows || mi_col >= cm -> mi_cols ) return ;
 switch ( partition ) {
 case PARTITION_NONE : set_modeinfo_offsets ( cm , xd , mi_row , mi_col ) ;
 * ( xd -> mi [ 0 ] . src_mi ) = pc_tree -> none . mic ;
 duplicate_mode_info_in_sb ( cm , xd , mi_row , mi_col , bsize ) ;
 break ;
 case PARTITION_VERT : set_modeinfo_offsets ( cm , xd , mi_row , mi_col ) ;
 * ( xd -> mi [ 0 ] . src_mi ) = pc_tree -> vertical [ 0 ] . mic ;
 duplicate_mode_info_in_sb ( cm , xd , mi_row , mi_col , bsize ) ;
 if ( mi_col + hbs < cm -> mi_cols ) {
 set_modeinfo_offsets ( cm , xd , mi_row , mi_col + hbs ) ;
 * ( xd -> mi [ 0 ] . src_mi ) = pc_tree -> vertical [ 1 ] . mic ;
 duplicate_mode_info_in_sb ( cm , xd , mi_row , mi_col + hbs , bsize ) ;
 }
 break ;
 case PARTITION_HORZ : set_modeinfo_offsets ( cm , xd , mi_row , mi_col ) ;
 * ( xd -> mi [ 0 ] . src_mi ) = pc_tree -> horizontal [ 0 ] . mic ;
 duplicate_mode_info_in_sb ( cm , xd , mi_row , mi_col , bsize ) ;
 if ( mi_row + hbs < cm -> mi_rows ) {
 set_modeinfo_offsets ( cm , xd , mi_row + hbs , mi_col ) ;
 * ( xd -> mi [ 0 ] . src_mi ) = pc_tree -> horizontal [ 1 ] . mic ;
 duplicate_mode_info_in_sb ( cm , xd , mi_row + hbs , mi_col , bsize ) ;
 }
 break ;
 case PARTITION_SPLIT : {
 BLOCK_SIZE subsubsize = get_subsize ( subsize , PARTITION_SPLIT ) ;
 fill_mode_info_sb ( cm , x , mi_row , mi_col , subsize , subsubsize , pc_tree -> split [ 0 ] ) ;
 fill_mode_info_sb ( cm , x , mi_row , mi_col + hbs , subsize , subsubsize , pc_tree -> split [ 1 ] ) ;
 fill_mode_info_sb ( cm , x , mi_row + hbs , mi_col , subsize , subsubsize , pc_tree -> split [ 2 ] ) ;
 fill_mode_info_sb ( cm , x , mi_row + hbs , mi_col + hbs , subsize , subsubsize , pc_tree -> split [ 3 ] ) ;
 break ;
 }
 default : break ;
 }
 }