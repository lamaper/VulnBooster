static enum nss_status gaih_getanswer_slice ( const querybuf * answer , int anslen , const char * qname , struct gaih_addrtuple * * * patp , char * * bufferp , size_t * buflenp , int * errnop , int * h_errnop , int32_t * ttlp , int * firstp ) {
 char * buffer = * bufferp ;
 size_t buflen = * buflenp ;
 struct gaih_addrtuple * * pat = * patp ;
 const HEADER * hp = & answer -> hdr ;
 int ancount = ntohs ( hp -> ancount ) ;
 int qdcount = ntohs ( hp -> qdcount ) ;
 const u_char * cp = answer -> buf + HFIXEDSZ ;
 const u_char * end_of_message = answer -> buf + anslen ;
 if ( __glibc_unlikely ( qdcount != 1 ) ) {
 * h_errnop = NO_RECOVERY ;
 return NSS_STATUS_UNAVAIL ;
 }
 u_char packtmp [ NS_MAXCDNAME ] ;
 int n = __ns_name_unpack ( answer -> buf , end_of_message , cp , packtmp , sizeof packtmp ) ;
 if ( n != - 1 && __ns_name_ntop ( packtmp , buffer , buflen ) == - 1 ) {
 if ( __builtin_expect ( errno , 0 ) == EMSGSIZE ) {
 too_small : * errnop = ERANGE ;
 * h_errnop = NETDB_INTERNAL ;
 return NSS_STATUS_TRYAGAIN ;
 }
 n = - 1 ;
 }
 if ( __builtin_expect ( n < 0 || ( res_hnok ( buffer ) == 0 && ( errno = EBADMSG ) ) , 0 ) ) {
 * errnop = errno ;
 * h_errnop = NO_RECOVERY ;
 return NSS_STATUS_UNAVAIL ;
 }
 cp += n + QFIXEDSZ ;
 int haveanswer = 0 ;
 int had_error = 0 ;
 char * canon = NULL ;
 char * h_name = NULL ;
 int h_namelen = 0 ;
 if ( ancount == 0 ) return NSS_STATUS_NOTFOUND ;
 while ( ancount -- > 0 && cp < end_of_message && had_error == 0 ) {
 n = __ns_name_unpack ( answer -> buf , end_of_message , cp , packtmp , sizeof packtmp ) ;
 if ( n != - 1 && ( h_namelen = __ns_name_ntop ( packtmp , buffer , buflen ) ) == - 1 ) {
 if ( __builtin_expect ( errno , 0 ) == EMSGSIZE ) goto too_small ;
 n = - 1 ;
 }
 if ( __glibc_unlikely ( n < 0 || res_hnok ( buffer ) == 0 ) ) {
 ++ had_error ;
 continue ;
 }
 if ( * firstp && canon == NULL ) {
 h_name = buffer ;
 buffer += h_namelen ;
 buflen -= h_namelen ;
 }
 cp += n ;
 if ( __glibc_unlikely ( cp + 10 > end_of_message ) ) {
 ++ had_error ;
 continue ;
 }
 int type = __ns_get16 ( cp ) ;
 cp += INT16SZ ;
 int class = __ns_get16 ( cp ) ;
 cp += INT16SZ ;
 int32_t ttl = __ns_get32 ( cp ) ;
 cp += INT32SZ ;
 n = __ns_get16 ( cp ) ;
 cp += INT16SZ ;
 if ( class != C_IN ) {
 cp += n ;
 continue ;
 }
 if ( type == T_CNAME ) {
 char tbuf [ MAXDNAME ] ;
 if ( ttlp != NULL && ttl < * ttlp ) * ttlp = ttl ;
 n = dn_expand ( answer -> buf , end_of_message , cp , tbuf , sizeof tbuf ) ;
 if ( __glibc_unlikely ( n < 0 || res_hnok ( tbuf ) == 0 ) ) {
 ++ had_error ;
 continue ;
 }
 cp += n ;
 if ( * firstp ) {
 if ( h_name + h_namelen == buffer ) {
 buffer = h_name ;
 buflen += h_namelen ;
 }
 n = strlen ( tbuf ) + 1 ;
 if ( __glibc_unlikely ( n > buflen ) ) goto too_small ;
 if ( __glibc_unlikely ( n >= MAXHOSTNAMELEN ) ) {
 ++ had_error ;
 continue ;
 }
 canon = buffer ;
 buffer = __mempcpy ( buffer , tbuf , n ) ;
 buflen -= n ;
 h_namelen = 0 ;
 }
 continue ;
 }

 syslog ( LOG_DEBUG | LOG_AUTH , "getaddrinfo*.gaih_getanswer: got type \"%s\"" , p_type ( type ) ) ;
 cp += n ;
 continue ;
 }
 if ( type != T_A && type != T_AAAA ) abort ( ) ;
 if ( * pat == NULL ) {
 uintptr_t pad = ( - ( uintptr_t ) buffer % __alignof__ ( struct gaih_addrtuple ) ) ;
 buffer += pad ;
 buflen = buflen > pad ? buflen - pad : 0 ;
 if ( __builtin_expect ( buflen < sizeof ( struct gaih_addrtuple ) , 0 ) ) goto too_small ;
 * pat = ( struct gaih_addrtuple * ) buffer ;
 buffer += sizeof ( struct gaih_addrtuple ) ;
 buflen -= sizeof ( struct gaih_addrtuple ) ;
 }
 ( * pat ) -> name = NULL ;
 ( * pat ) -> next = NULL ;
 if ( * firstp ) {
 if ( ttlp != NULL && ttl < * ttlp ) * ttlp = ttl ;
 ( * pat ) -> name = canon ? : h_name ;
 * firstp = 0 ;
 }
 ( * pat ) -> family = type == T_A ? AF_INET : AF_INET6 ;
 if ( __builtin_expect ( ( type == T_A && n != INADDRSZ ) || ( type == T_AAAA && n != IN6ADDRSZ ) , 0 ) ) {
 ++ had_error ;
 continue ;
 }
 memcpy ( ( * pat ) -> addr , cp , n ) ;
 cp += n ;
 ( * pat ) -> scopeid = 0 ;
 pat = & ( ( * pat ) -> next ) ;
 haveanswer = 1 ;
 }
 if ( haveanswer ) {
 * patp = pat ;
 * bufferp = buffer ;
 * buflenp = buflen ;
 * h_errnop = NETDB_SUCCESS ;
 return NSS_STATUS_SUCCESS ;
 }
 return canon == NULL ? NSS_STATUS_TRYAGAIN : NSS_STATUS_NOTFOUND ;
 }