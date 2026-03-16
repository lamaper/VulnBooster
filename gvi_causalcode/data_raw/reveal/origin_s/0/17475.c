static int ossl_asn1_is_explicit ( VALUE obj ) {
 VALUE s ;
 s = ossl_asn1_get_tagging ( obj ) ;
 if ( NIL_P ( s ) || s == sym_IMPLICIT ) return 0 ;
 else if ( s == sym_EXPLICIT ) return 1 ;
 else ossl_raise ( eASN1Error , "invalid tag default" ) ;
 }