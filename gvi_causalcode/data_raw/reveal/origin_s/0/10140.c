static void DumpDblArray ( real * arr , int n , FILE * cfff , int oper ) {
 int mi , i ;
 for ( mi = n - 1 ;
 mi >= 0 && arr [ mi ] == 0 ;
 -- mi ) ;
 if ( mi < 0 ) return ;
 dumpdbl ( cfff , arr [ 0 ] ) ;
 for ( i = 1 ;
 i <= mi ;
 ++ i ) dumpdbl ( cfff , arr [ i ] - arr [ i - 1 ] ) ;
 dumpoper ( cfff , oper ) ;
 }