static void write_partition ( const VP9_COMMON * const cm , const MACROBLOCKD * const xd , int hbs , int mi_row , int mi_col , PARTITION_TYPE p , BLOCK_SIZE bsize , vp9_writer * w ) {
 const int ctx = partition_plane_context ( xd , mi_row , mi_col , bsize ) ;
 const vp9_prob * const probs = get_partition_probs ( cm , ctx ) ;
 const int has_rows = ( mi_row + hbs ) < cm -> mi_rows ;
 const int has_cols = ( mi_col + hbs ) < cm -> mi_cols ;
 if ( has_rows && has_cols ) {
 vp9_write_token ( w , vp9_partition_tree , probs , & partition_encodings [ p ] ) ;
 }
 else if ( ! has_rows && has_cols ) {
 assert ( p == PARTITION_SPLIT || p == PARTITION_HORZ ) ;
 vp9_write ( w , p == PARTITION_SPLIT , probs [ 1 ] ) ;
 }
 else if ( has_rows && ! has_cols ) {
 assert ( p == PARTITION_SPLIT || p == PARTITION_VERT ) ;
 vp9_write ( w , p == PARTITION_SPLIT , probs [ 2 ] ) ;
 }
 else {
 assert ( p == PARTITION_SPLIT ) ;
 }
 }