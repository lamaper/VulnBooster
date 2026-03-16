static inline int answer_from_qmem_data ( int dns_fd , int userid , struct query * q ) {
 char cmc [ 4 ] ;
 int i ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) if ( q -> name [ i + 1 ] >= 'A' && q -> name [ i + 1 ] <= 'Z' ) cmc [ i ] = q -> name [ i + 1 ] + ( 'a' - 'A' ) ;
 else cmc [ i ] = q -> name [ i + 1 ] ;
 return answer_from_qmem ( dns_fd , q , users [ userid ] . qmemdata_cmc , users [ userid ] . qmemdata_type , QMEMDATA_LEN , ( void * ) cmc ) ;
 }