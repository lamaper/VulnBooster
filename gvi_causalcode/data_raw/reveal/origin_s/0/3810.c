static ASN1_GENERALIZEDTIME * obj_to_asn1gtime ( VALUE time ) {
 time_t sec ;
 ASN1_GENERALIZEDTIME * t ;

 ossl_time_split ( time , & sec , & off_days ) ;
 if ( ! ( t = ASN1_GENERALIZEDTIME_adj ( NULL , sec , off_days , 0 ) ) ) # else sec = time_to_time_t ( time ) ;
 if ( ! ( t = ASN1_GENERALIZEDTIME_set ( NULL , sec ) ) ) # endif ossl_raise ( eASN1Error , NULL ) ;
 return t ;
 }