static int candidate_refresh_aq ( const CYCLIC_REFRESH * cr , const MB_MODE_INFO * mbmi , BLOCK_SIZE bsize , int use_rd ) {
 if ( use_rd ) {
 if ( cr -> projected_rate_sb < cr -> thresh_rate_sb ) return 1 ;
 else if ( bsize < cr -> min_block_size || ( mbmi -> mv [ 0 ] . as_int != 0 && cr -> projected_dist_sb > cr -> thresh_dist_sb ) || ! is_inter_block ( mbmi ) ) return 0 ;
 else return 1 ;
 }
 else {
 if ( bsize < cr -> min_block_size || mbmi -> mv [ 0 ] . as_int != 0 || ! is_inter_block ( mbmi ) ) return 0 ;
 else return 1 ;
 }
 }