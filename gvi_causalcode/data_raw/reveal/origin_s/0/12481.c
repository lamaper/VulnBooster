static real Blend ( real u [ MmMax ] , struct pscontext * context ) {
 real sum = u [ 0 ] ;
 int i ;
 for ( i = 1 ;
 i < context -> instance_count ;
 ++ i ) sum += context -> blend_values [ i ] * u [ i ] ;
 return ( sum ) ;
 }