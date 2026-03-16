unsigned long # endif # undef mul # undef mul_add # define mul_add ( r , a , word , carry ) do {
 \ register BN_ULONG high , low ;
 \ asm ( "mulq %3" \ : "=a" ( low ) , "=d" ( high ) \ : "a" ( word ) , "m" ( a ) \ : "cc" ) ;
 \ asm ( "addq %2,%0;
 adcq %3,%1" \ : "+r" ( carry ) , "+d" ( high ) \ : "a" ( low ) , "g" ( 0 ) \ : "cc" ) ;
 \ asm ( "addq %2,%0;
 adcq %3,%1" \ : "+m" ( r ) , "+d" ( high ) \ : "r" ( carry ) , "g" ( 0 ) \ : "cc" ) ;
 \ carry = high ;
 \ }
 while ( 0 ) # define mul ( r , a , word , carry ) do {
 \ register BN_ULONG high , low ;
 \ asm ( "mulq %3" \ : "=a" ( low ) , "=d" ( high ) \ : "a" ( word ) , "g" ( a ) \ : "cc" ) ;
 \ asm ( "addq %2,%0;
 adcq %3,%1" \ : "+r" ( carry ) , "+d" ( high ) \ : "a" ( low ) , "g" ( 0 ) \ : "cc" ) ;
 \ ( r ) = carry , carry = high ;
 \ }
 while ( 0 ) # undef sqr # define sqr ( r0 , r1 , a ) \ asm ( "mulq %2" \ : "=a" ( r0 ) , "=d" ( r1 ) \ : "a" ( a ) \ : "cc" ) ;
 BN_ULONG bn_mul_add_words ( BN_ULONG * rp , const BN_ULONG * ap , int num , BN_ULONG w ) {
 BN_ULONG c1 = 0 ;
 if ( num <= 0 ) return ( c1 ) ;
 while ( num & ~ 3 ) {
 mul_add ( rp [ 0 ] , ap [ 0 ] , w , c1 ) ;
 mul_add ( rp [ 1 ] , ap [ 1 ] , w , c1 ) ;
 mul_add ( rp [ 2 ] , ap [ 2 ] , w , c1 ) ;
 mul_add ( rp [ 3 ] , ap [ 3 ] , w , c1 ) ;
 ap += 4 ;
 rp += 4 ;
 num -= 4 ;
 }
 if ( num ) {
 mul_add ( rp [ 0 ] , ap [ 0 ] , w , c1 ) ;
 if ( -- num == 0 ) return c1 ;
 mul_add ( rp [ 1 ] , ap [ 1 ] , w , c1 ) ;
 if ( -- num == 0 ) return c1 ;
 mul_add ( rp [ 2 ] , ap [ 2 ] , w , c1 ) ;
 return c1 ;
 }
 return ( c1 ) ;
 }