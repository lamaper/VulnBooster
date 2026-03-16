hidden_def ( _nss_dns_gethostbyaddr2_r ) enum nss_status _nss_dns_gethostbyaddr_r ( const void * addr , socklen_t len , int af , struct hostent * result , char * buffer , size_t buflen , int * errnop , int * h_errnop ) {
 return _nss_dns_gethostbyaddr2_r ( addr , len , af , result , buffer , buflen , errnop , h_errnop , NULL ) ;
 }