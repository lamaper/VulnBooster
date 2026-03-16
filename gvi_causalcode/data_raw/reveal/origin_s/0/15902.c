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
 BN_ULONG bn_mul_words ( BN_ULONG * rp , const BN_ULONG * ap , int num , BN_ULONG w ) {
 BN_ULONG c1 = 0 ;
 if ( num <= 0 ) return ( c1 ) ;
 while ( num & ~ 3 ) {
 mul ( rp [ 0 ] , ap [ 0 ] , w , c1 ) ;
 mul ( rp [ 1 ] , ap [ 1 ] , w , c1 ) ;
 mul ( rp [ 2 ] , ap [ 2 ] , w , c1 ) ;
 mul ( rp [ 3 ] , ap [ 3 ] , w , c1 ) ;
 ap += 4 ;
 rp += 4 ;
 num -= 4 ;
 }
 if ( num ) {
 mul ( rp [ 0 ] , ap [ 0 ] , w , c1 ) ;
 if ( -- num == 0 ) return c1 ;
 mul ( rp [ 1 ] , ap [ 1 ] , w , c1 ) ;
 if ( -- num == 0 ) return c1 ;
 mul ( rp [ 2 ] , ap [ 2 ] , w , c1 ) ;
 }
 return ( c1 ) ;
 }
 void bn_sqr_words ( BN_ULONG * r , const BN_ULONG * a , int n ) {
 if ( n <= 0 ) return ;
 while ( n & ~ 3 ) {
 sqr ( r [ 0 ] , r [ 1 ] , a [ 0 ] ) ;
 sqr ( r [ 2 ] , r [ 3 ] , a [ 1 ] ) ;
 sqr ( r [ 4 ] , r [ 5 ] , a [ 2 ] ) ;
 sqr ( r [ 6 ] , r [ 7 ] , a [ 3 ] ) ;
 a += 4 ;
 r += 8 ;
 n -= 4 ;
 }
 if ( n ) {
 sqr ( r [ 0 ] , r [ 1 ] , a [ 0 ] ) ;
 if ( -- n == 0 ) return ;
 sqr ( r [ 2 ] , r [ 3 ] , a [ 1 ] ) ;
 if ( -- n == 0 ) return ;
 sqr ( r [ 4 ] , r [ 5 ] , a [ 2 ] ) ;
 }
 }
 BN_ULONG bn_div_words ( BN_ULONG h , BN_ULONG l , BN_ULONG d ) {
 BN_ULONG ret , waste ;
 asm ( "divq %4" : "=a" ( ret ) , "=d" ( waste ) : "a" ( l ) , "d" ( h ) , "g" ( d ) : "cc" ) ;
 return ret ;
 }
 BN_ULONG bn_add_words ( BN_ULONG * rp , const BN_ULONG * ap , const BN_ULONG * bp , int n ) {
 BN_ULONG ret ;
 size_t i = 0 ;
 if ( n <= 0 ) return 0 ;
 asm volatile ( " subq %0,%0 \n" " jmp 1f \n" ".p2align 4 \n" "1: movq (%4,%2,8),%0 \n" " adcq (%5,%2,8),%0 \n" " movq %0,(%3,%2,8) \n" " lea 1(%2),%2 \n" " loop 1b \n" " sbbq %0,%0 \n" : "=&r" ( ret ) , "+c" ( n ) , "+r" ( i ) : "r" ( rp ) , "r" ( ap ) , "r" ( bp ) : "cc" , "memory" ) ;
 return ret & 1 ;
 }