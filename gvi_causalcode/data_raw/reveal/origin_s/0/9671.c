hidden_def ( _nss_dns_gethostbyname3_r ) enum nss_status _nss_dns_gethostbyname2_r ( const char * name , int af , struct hostent * result , char * buffer , size_t buflen , int * errnop , int * h_errnop ) {
 return _nss_dns_gethostbyname3_r ( name , af , result , buffer , buflen , errnop , h_errnop , NULL , NULL ) ;
 }