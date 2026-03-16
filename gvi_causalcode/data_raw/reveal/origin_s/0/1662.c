static enum nss_status gaih_getanswer ( const querybuf * answer1 , int anslen1 , const querybuf * answer2 , int anslen2 , const char * qname , struct gaih_addrtuple * * pat , char * buffer , size_t buflen , int * errnop , int * h_errnop , int32_t * ttlp ) {
 int first = 1 ;
 enum nss_status status = NSS_STATUS_NOTFOUND ;
 if ( anslen1 > 0 ) status = gaih_getanswer_slice ( answer1 , anslen1 , qname , & pat , & buffer , & buflen , errnop , h_errnop , ttlp , & first ) ;
 if ( ( status == NSS_STATUS_SUCCESS || status == NSS_STATUS_NOTFOUND || ( status == NSS_STATUS_TRYAGAIN && ( * errnop != ERANGE || * h_errnop == NO_RECOVERY ) ) ) && answer2 != NULL && anslen2 > 0 ) {
 enum nss_status status2 = gaih_getanswer_slice ( answer2 , anslen2 , qname , & pat , & buffer , & buflen , errnop , h_errnop , ttlp , & first ) ;
 if ( status != NSS_STATUS_SUCCESS && status2 != NSS_STATUS_NOTFOUND ) status = status2 ;
 }
 return status ;
 }