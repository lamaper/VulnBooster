static int update_mv ( vp9_writer * w , const unsigned int ct [ 2 ] , vp9_prob * cur_p , vp9_prob upd_p ) {
 const vp9_prob new_p = get_binary_prob ( ct [ 0 ] , ct [ 1 ] ) | 1 ;
 const int update = cost_branch256 ( ct , * cur_p ) + vp9_cost_zero ( upd_p ) > cost_branch256 ( ct , new_p ) + vp9_cost_one ( upd_p ) + 7 * 256 ;
 vp9_write ( w , update , upd_p ) ;
 if ( update ) {
 * cur_p = new_p ;
 vp9_write_literal ( w , new_p >> 1 , 7 ) ;
 }
 return update ;
 }