enum nss_status _nss_dns_gethostbyname_r ( const char * name , struct hostent * result , char * buffer , size_t buflen , int * errnop , int * h_errnop ) {
 enum nss_status status = NSS_STATUS_NOTFOUND ;
 if ( _res . options & RES_USE_INET6 ) status = _nss_dns_gethostbyname3_r ( name , AF_INET6 , result , buffer , buflen , errnop , h_errnop , NULL , NULL ) ;
 if ( status == NSS_STATUS_NOTFOUND ) status = _nss_dns_gethostbyname3_r ( name , AF_INET , result , buffer , buflen , errnop , h_errnop , NULL , NULL ) ;
 return status ;
 }