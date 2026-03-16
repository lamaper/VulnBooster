BN_ULONG bn_mul_add_words ( BN_ULONG * rp , const BN_ULONG * ap , int num , BN_ULONG w ) {
 BN_ULONG c = 0 ;
 BN_ULONG bl , bh ;
 assert ( num >= 0 ) ;
 if ( num <= 0 ) return ( ( BN_ULONG ) 0 ) ;
 bl = LBITS ( w ) ;
 bh = HBITS ( w ) ;

 mul_add ( rp [ 0 ] , ap [ 0 ] , bl , bh , c ) ;
 mul_add ( rp [ 1 ] , ap [ 1 ] , bl , bh , c ) ;
 mul_add ( rp [ 2 ] , ap [ 2 ] , bl , bh , c ) ;
 mul_add ( rp [ 3 ] , ap [ 3 ] , bl , bh , c ) ;
 ap += 4 ;
 rp += 4 ;
 num -= 4 ;
 }

 mul_add ( rp [ 0 ] , ap [ 0 ] , bl , bh , c ) ;
 ap ++ ;
 rp ++ ;
 num -- ;
 }
 return ( c ) ;
 }