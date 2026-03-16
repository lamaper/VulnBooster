Oid get_promoted_array_type ( Oid typid ) {
 Oid array_type = get_array_type ( typid ) ;
 if ( OidIsValid ( array_type ) ) return array_type ;
 if ( OidIsValid ( get_element_type ( typid ) ) ) return typid ;
 return InvalidOid ;
 }