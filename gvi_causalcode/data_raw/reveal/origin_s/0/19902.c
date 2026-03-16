PREDICTION_MODE vp9_left_block_mode ( const MODE_INFO * cur_mi , const MODE_INFO * left_mi , int b ) {
 if ( b == 0 || b == 2 ) {
 if ( ! left_mi || is_inter_block ( & left_mi -> mbmi ) ) return DC_PRED ;
 return get_y_mode ( left_mi , b + 1 ) ;
 }
 else {
 assert ( b == 1 || b == 3 ) ;
 return cur_mi -> bmi [ b - 1 ] . as_mode ;
 }
 }