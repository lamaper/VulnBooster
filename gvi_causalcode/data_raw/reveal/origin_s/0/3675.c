static int pfkey_sockaddr_extract ( const struct sockaddr * sa , xfrm_address_t * xaddr ) {
 switch ( sa -> sa_family ) {
 case AF_INET : xaddr -> a4 = ( ( struct sockaddr_in * ) sa ) -> sin_addr . s_addr ;
 return AF_INET ;

 return AF_INET6 ;

 return 0 ;
 }