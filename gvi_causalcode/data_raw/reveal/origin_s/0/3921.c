static Asn1Generic * Asn1GenericNew ( void ) {
 Asn1Generic * obj ;
 obj = SCMalloc ( sizeof ( Asn1Generic ) ) ;
 if ( obj != NULL ) memset ( obj , 0 , sizeof ( Asn1Generic ) ) ;
 return obj ;
 }