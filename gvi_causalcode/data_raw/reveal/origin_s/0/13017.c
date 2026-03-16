hidden_proto ( _nss_dns_gethostbyname3_r ) enum nss_status _nss_dns_gethostbyname3_r ( const char * name , int af , struct hostent * result , char * buffer , size_t buflen , int * errnop , int * h_errnop , int32_t * ttlp , char * * canonp ) {
 union {
 querybuf * buf ;
 u_char * ptr ;
 }
 host_buffer ;
 querybuf * orig_host_buffer ;
 char tmp [ NS_MAXDNAME ] ;
 int size , type , n ;
 const char * cp ;
 int map = 0 ;
 int olderr = errno ;
 enum nss_status status ;
 if ( __res_maybe_init ( & _res , 0 ) == - 1 ) return NSS_STATUS_UNAVAIL ;
 switch ( af ) {
 case AF_INET : size = INADDRSZ ;
 type = T_A ;
 break ;
 case AF_INET6 : size = IN6ADDRSZ ;
 type = T_AAAA ;
 break ;
 default : * h_errnop = NO_DATA ;
 * errnop = EAFNOSUPPORT ;
 return NSS_STATUS_UNAVAIL ;
 }
 result -> h_addrtype = af ;
 result -> h_length = size ;
 if ( strchr ( name , '.' ) == NULL && ( cp = res_hostalias ( & _res , name , tmp , sizeof ( tmp ) ) ) != NULL ) name = cp ;
 host_buffer . buf = orig_host_buffer = ( querybuf * ) alloca ( 1024 ) ;
 n = __libc_res_nsearch ( & _res , name , C_IN , type , host_buffer . buf -> buf , 1024 , & host_buffer . ptr , NULL , NULL , NULL , NULL ) ;
 if ( n < 0 ) {
 switch ( errno ) {
 case ESRCH : status = NSS_STATUS_TRYAGAIN ;
 h_errno = TRY_AGAIN ;
 break ;
 case EMFILE : case ENFILE : h_errno = NETDB_INTERNAL ;
 case ECONNREFUSED : case ETIMEDOUT : status = NSS_STATUS_UNAVAIL ;
 break ;
 default : status = NSS_STATUS_NOTFOUND ;
 break ;
 }
 * h_errnop = h_errno ;
 if ( h_errno == TRY_AGAIN ) * errnop = EAGAIN ;
 else __set_errno ( olderr ) ;
 if ( af == AF_INET6 && ( _res . options & RES_USE_INET6 ) ) n = __libc_res_nsearch ( & _res , name , C_IN , T_A , host_buffer . buf -> buf , host_buffer . buf != orig_host_buffer ? MAXPACKET : 1024 , & host_buffer . ptr , NULL , NULL , NULL , NULL ) ;
 if ( n < 0 ) {
 if ( host_buffer . buf != orig_host_buffer ) free ( host_buffer . buf ) ;
 return status ;
 }
 map = 1 ;
 result -> h_addrtype = AF_INET ;
 result -> h_length = INADDRSZ ;
 }
 status = getanswer_r ( host_buffer . buf , n , name , type , result , buffer , buflen , errnop , h_errnop , map , ttlp , canonp ) ;
 if ( host_buffer . buf != orig_host_buffer ) free ( host_buffer . buf ) ;
 return status ;
 }