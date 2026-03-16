static ASN1_UTCTIME * obj_to_asn1utime ( VALUE time ) {
 time_t sec ;
 ASN1_UTCTIME * t ;

 ossl_time_split ( time , & sec , & off_days ) ;
 if ( ! ( t = ASN1_UTCTIME_adj ( NULL , sec , off_days , 0 ) ) ) # else sec = time_to_time_t ( time ) ;
 if ( ! ( t = ASN1_UTCTIME_set ( NULL , sec ) ) ) # endif ossl_raise ( eASN1Error , NULL ) ;
 return t ;
 }