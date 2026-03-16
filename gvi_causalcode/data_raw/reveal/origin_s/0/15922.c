static PARTITION_TYPE read_partition ( VP9_COMMON * cm , MACROBLOCKD * xd , int hbs , int mi_row , int mi_col , BLOCK_SIZE bsize , vp9_reader * r ) {
 const int ctx = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 const vp9_prob * const probs = get_partition_probs ( cm , ctx ) ;
 const int has_rows = ( mi_row + hbs ) < cm -> mi_rows ;
 const int has_cols = ( mi_col + hbs ) < cm -> mi_cols ;
 PARTITION_TYPE p ;
 if ( has_rows && has_cols ) p = ( PARTITION_TYPE ) vp9_read_tree ( r , vp9_partition_tree , probs ) ;
 else if ( ! has_rows && has_cols ) p = vp9_read ( r , probs [ 1 ] ) ? PARTITION_SPLIT : PARTITION_HORZ ;
 else if ( has_rows && ! has_cols ) p = vp9_read ( r , probs [ 2 ] ) ? PARTITION_SPLIT : PARTITION_VERT ;
 else p = PARTITION_SPLIT ;
 if ( ! cm -> frame_parallel_decoding_mode ) ++ cm -> counts . partition [ ctx ] [ p ] ;
 return p ;
 }