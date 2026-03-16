static int address_is_correct ( struct nameserver * ns , struct sockaddr * sa , socklen_t slen ) {
 struct sockaddr_in * sin = ( struct sockaddr_in * ) sa ;
 if ( sa -> sa_family != AF_INET || slen != sizeof ( struct sockaddr_in ) ) return 0 ;
 if ( sin -> sin_addr . s_addr != ns -> address ) return 0 ;
 return 1 ;
 }