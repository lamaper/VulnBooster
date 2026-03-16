int64_t vp9_block_error_c ( const int16_t * coeff , const int16_t * dqcoeff , intptr_t block_size , int64_t * ssz ) {
 int i ;
 int64_t error = 0 , sqcoeff = 0 ;
 for ( i = 0 ;
 i < block_size ;
 i ++ ) {
 const int diff = coeff [ i ] - dqcoeff [ i ] ;
 error += diff * diff ;
 sqcoeff += coeff [ i ] * coeff [ i ] ;
 }
 * ssz = sqcoeff ;
 return error ;
 }