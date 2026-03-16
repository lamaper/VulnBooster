static inline void save_to_qmem_pingordata ( int userid , struct query * q ) {
 char cmc [ 8 ] ;
 int i ;
 if ( q -> name [ 0 ] == 'P' || q -> name [ 0 ] == 'p' ) {
 size_t cmcsize = sizeof ( cmc ) ;
 char * cp = strchr ( q -> name , '.' ) ;
 if ( cp == NULL ) return ;
 i = b32 -> decode ( cmc , & cmcsize , q -> name + 1 , ( cp - q -> name ) - 1 ) ;
 if ( i < 4 ) return ;
 save_to_qmem ( users [ userid ] . qmemping_cmc , users [ userid ] . qmemping_type , QMEMPING_LEN , & users [ userid ] . qmemping_lastfilled , ( void * ) cmc , q -> type ) ;
 }
 else {
 if ( strlen ( q -> name ) < 5 ) return ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) if ( q -> name [ i + 1 ] >= 'A' && q -> name [ i + 1 ] <= 'Z' ) cmc [ i ] = q -> name [ i + 1 ] + ( 'a' - 'A' ) ;
 else cmc [ i ] = q -> name [ i + 1 ] ;
 save_to_qmem ( users [ userid ] . qmemdata_cmc , users [ userid ] . qmemdata_type , QMEMDATA_LEN , & users [ userid ] . qmemdata_lastfilled , ( void * ) cmc , q -> type ) ;
 }
 }