hidden_proto ( _nss_dns_gethostbyaddr2_r ) enum nss_status _nss_dns_gethostbyaddr2_r ( const void * addr , socklen_t len , int af , struct hostent * result , char * buffer , size_t buflen , int * errnop , int * h_errnop , int32_t * ttlp ) {
 static const u_char mapped [ ] = {
 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0xff , 0xff }
 ;
 static const u_char tunnelled [ ] = {
 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }
 ;
 static const u_char v6local [ ] = {
 0 , 0 , 0 , 1 }
 ;
 const u_char * uaddr = ( const u_char * ) addr ;
 struct host_data {
 char * aliases [ MAX_NR_ALIASES ] ;
 unsigned char host_addr [ 16 ] ;
 char * h_addr_ptrs [ MAX_NR_ADDRS + 1 ] ;
 char linebuffer [ 0 ] ;
 }
 * host_data = ( struct host_data * ) buffer ;
 union {
 querybuf * buf ;
 u_char * ptr ;
 }
 host_buffer ;
 querybuf * orig_host_buffer ;
 char qbuf [ MAXDNAME + 1 ] , * qp = NULL ;
 size_t size ;
 int n , status ;
 int olderr = errno ;
 uintptr_t pad = - ( uintptr_t ) buffer % __alignof__ ( struct host_data ) ;
 buffer += pad ;
 buflen = buflen > pad ? buflen - pad : 0 ;
 if ( __glibc_unlikely ( buflen < sizeof ( struct host_data ) ) ) {
 * errnop = ERANGE ;
 * h_errnop = NETDB_INTERNAL ;
 return NSS_STATUS_TRYAGAIN ;
 }
 host_data = ( struct host_data * ) buffer ;
 if ( __res_maybe_init ( & _res , 0 ) == - 1 ) return NSS_STATUS_UNAVAIL ;
 if ( af == AF_INET6 && len == IN6ADDRSZ && ( memcmp ( uaddr , mapped , sizeof mapped ) == 0 || ( memcmp ( uaddr , tunnelled , sizeof tunnelled ) == 0 && memcmp ( & uaddr [ sizeof tunnelled ] , v6local , sizeof v6local ) ) ) ) {
 addr += sizeof mapped ;
 uaddr += sizeof mapped ;
 af = AF_INET ;
 len = INADDRSZ ;
 }
 switch ( af ) {
 case AF_INET : size = INADDRSZ ;
 break ;
 case AF_INET6 : size = IN6ADDRSZ ;
 break ;
 default : * errnop = EAFNOSUPPORT ;
 * h_errnop = NETDB_INTERNAL ;
 return NSS_STATUS_UNAVAIL ;
 }
 if ( size > len ) {
 * errnop = EAFNOSUPPORT ;
 * h_errnop = NETDB_INTERNAL ;
 return NSS_STATUS_UNAVAIL ;
 }
 host_buffer . buf = orig_host_buffer = ( querybuf * ) alloca ( 1024 ) ;
 switch ( af ) {
 case AF_INET : sprintf ( qbuf , "%u.%u.%u.%u.in-addr.arpa" , ( uaddr [ 3 ] & 0xff ) , ( uaddr [ 2 ] & 0xff ) , ( uaddr [ 1 ] & 0xff ) , ( uaddr [ 0 ] & 0xff ) ) ;
 break ;
 case AF_INET6 : if ( __glibc_unlikely ( _res . options & RES_USEBSTRING ) ) {
 qp = stpcpy ( qbuf , "\\[x" ) ;
 for ( n = 0 ;
 n < IN6ADDRSZ ;
 ++ n ) qp += sprintf ( qp , "%02hhx" , uaddr [ n ] ) ;
 strcpy ( qp , "].ip6.arpa" ) ;
 n = __libc_res_nquery ( & _res , qbuf , C_IN , T_PTR , host_buffer . buf -> buf , 1024 , & host_buffer . ptr , NULL , NULL , NULL , NULL ) ;
 if ( n >= 0 ) goto got_it_already ;
 }
 qp = qbuf ;
 for ( n = IN6ADDRSZ - 1 ;
 n >= 0 ;
 n -- ) {
 static const char nibblechar [ 16 ] = "0123456789abcdef" ;
 * qp ++ = nibblechar [ uaddr [ n ] & 0xf ] ;
 * qp ++ = '.' ;
 * qp ++ = nibblechar [ ( uaddr [ n ] >> 4 ) & 0xf ] ;
 * qp ++ = '.' ;
 }
 strcpy ( qp , "ip6.arpa" ) ;
 break ;
 default : break ;
 }
 n = __libc_res_nquery ( & _res , qbuf , C_IN , T_PTR , host_buffer . buf -> buf , 1024 , & host_buffer . ptr , NULL , NULL , NULL , NULL ) ;
 if ( n < 0 && af == AF_INET6 && ( _res . options & RES_NOIP6DOTINT ) == 0 ) {
 strcpy ( qp , "ip6.int" ) ;
 n = __libc_res_nquery ( & _res , qbuf , C_IN , T_PTR , host_buffer . buf -> buf , host_buffer . buf != orig_host_buffer ? MAXPACKET : 1024 , & host_buffer . ptr , NULL , NULL , NULL , NULL ) ;
 }
 if ( n < 0 ) {
 * h_errnop = h_errno ;
 __set_errno ( olderr ) ;
 if ( host_buffer . buf != orig_host_buffer ) free ( host_buffer . buf ) ;
 return errno == ECONNREFUSED ? NSS_STATUS_UNAVAIL : NSS_STATUS_NOTFOUND ;
 }
 got_it_already : status = getanswer_r ( host_buffer . buf , n , qbuf , T_PTR , result , buffer , buflen , errnop , h_errnop , 0 , ttlp , NULL ) ;
 if ( host_buffer . buf != orig_host_buffer ) free ( host_buffer . buf ) ;
 if ( status != NSS_STATUS_SUCCESS ) return status ;

 result -> h_length = len ;
 memcpy ( host_data -> host_addr , addr , len ) ;
 host_data -> h_addr_ptrs [ 0 ] = ( char * ) host_data -> host_addr ;
 host_data -> h_addr_ptrs [ 1 ] = NULL ;

 map_v4v6_address ( ( char * ) host_data -> host_addr , ( char * ) host_data -> host_addr ) ;
 result -> h_addrtype = AF_INET6 ;
 result -> h_length = IN6ADDRSZ ;
 }

 return NSS_STATUS_SUCCESS ;
 }