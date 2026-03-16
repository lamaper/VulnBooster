int UnblendedCompare ( real u1 [ MmMax ] , real u2 [ MmMax ] , int cnt ) {
 int i ;
 for ( i = 0 ;
 i < cnt ;
 ++ i ) {
 if ( u1 [ i ] != u2 [ i ] ) return ( u1 [ i ] > u2 [ i ] ? 1 : - 1 ) ;
 }
 return ( 0 ) ;
 }