static int answer_from_qmem ( int dns_fd , struct query * q , unsigned char * qmem_cmc , unsigned short * qmem_type , int qmem_len , unsigned char * cmc_to_check ) {
 int i ;
 for ( i = 0 ;
 i < qmem_len ;
 i ++ ) {
 if ( qmem_type [ i ] == T_UNSET ) continue ;
 if ( qmem_type [ i ] != q -> type ) continue ;
 if ( memcmp ( qmem_cmc + i * 4 , cmc_to_check , 4 ) ) continue ;
 if ( debug >= 1 ) fprintf ( stderr , "OUT from qmem for %s == duplicate, sending illegal reply\n" , q -> name ) ;
 write_dns ( dns_fd , q , "x" , 1 , 'T' ) ;
 q -> id = 0 ;
 return 1 ;
 }
 return 0 ;
 }