static VALUE ossl_asn1_class2sym ( int tc ) {
 if ( ( tc & V_ASN1_PRIVATE ) == V_ASN1_PRIVATE ) return sym_PRIVATE ;
 else if ( ( tc & V_ASN1_CONTEXT_SPECIFIC ) == V_ASN1_CONTEXT_SPECIFIC ) return sym_CONTEXT_SPECIFIC ;
 else if ( ( tc & V_ASN1_APPLICATION ) == V_ASN1_APPLICATION ) return sym_APPLICATION ;
 else return sym_UNIVERSAL ;
 }