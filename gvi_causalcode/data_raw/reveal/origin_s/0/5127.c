bool type_is_collatable ( Oid typid ) {
 return OidIsValid ( get_typcollation ( typid ) ) ;
 }