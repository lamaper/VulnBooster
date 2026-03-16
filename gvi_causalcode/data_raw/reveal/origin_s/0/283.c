VALUE asn1str_to_str ( const ASN1_STRING * str ) {
 return rb_str_new ( ( const char * ) str -> data , str -> length ) ;
 }