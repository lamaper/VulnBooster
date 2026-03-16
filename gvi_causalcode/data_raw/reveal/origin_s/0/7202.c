static int trellis_get_coeff_context ( const int16_t * scan , const int16_t * nb , int idx , int token , uint8_t * token_cache ) {
 int bak = token_cache [ scan [ idx ] ] , pt ;
 token_cache [ scan [ idx ] ] = vp9_pt_energy_class [ token ] ;
 pt = get_coef_context ( nb , token_cache , idx + 1 ) ;
 token_cache [ scan [ idx ] ] = bak ;
 return pt ;
 }