static int verify_address_len ( const void * p ) {
 const struct sadb_address * sp = p ;
 const struct sockaddr * addr = ( const struct sockaddr * ) ( sp + 1 ) ;
 const struct sockaddr_in * sin ;


 switch ( addr -> sa_family ) {
 case AF_INET : len = DIV_ROUND_UP ( sizeof ( * sp ) + sizeof ( * sin ) , sizeof ( uint64_t ) ) ;
 if ( sp -> sadb_address_len != len || sp -> sadb_address_prefixlen > 32 ) return - EINVAL ;
 break ;

 if ( sp -> sadb_address_len != len || sp -> sadb_address_prefixlen > 128 ) return - EINVAL ;
 break ;

 break ;
 }
 return 0 ;
 }