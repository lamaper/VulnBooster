PREDICTION_MODE vp9_above_block_mode ( const MODE_INFO * cur_mi , const MODE_INFO * above_mi , int b ) {
 if ( b == 0 || b == 1 ) {
 if ( ! above_mi || is_inter_block ( & above_mi -> mbmi ) ) return DC_PRED ;
 return get_y_mode ( above_mi , b + 2 ) ;
 }
 else {
 assert ( b == 2 || b == 3 ) ;
 return cur_mi -> bmi [ b - 2 ] . as_mode ;
 }
 }