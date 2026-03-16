static int ossl_asn1_tag_class ( VALUE obj ) {
 VALUE s ;
 s = ossl_asn1_get_tag_class ( obj ) ;
 if ( NIL_P ( s ) || s == sym_UNIVERSAL ) return V_ASN1_UNIVERSAL ;
 else if ( s == sym_APPLICATION ) return V_ASN1_APPLICATION ;
 else if ( s == sym_CONTEXT_SPECIFIC ) return V_ASN1_CONTEXT_SPECIFIC ;
 else if ( s == sym_PRIVATE ) return V_ASN1_PRIVATE ;
 else ossl_raise ( eASN1Error , "invalid tag class" ) ;
 }