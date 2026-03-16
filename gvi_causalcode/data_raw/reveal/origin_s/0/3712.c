static inline int pfkey_sockaddr_len ( sa_family_t family ) {
 switch ( family ) {
 case AF_INET : return sizeof ( struct sockaddr_in ) ;


 return 0 ;
 }