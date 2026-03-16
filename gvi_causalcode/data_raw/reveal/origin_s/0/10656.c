bool type_is_range ( Oid typid ) {
 return ( get_typtype ( typid ) == TYPTYPE_RANGE ) ;
 }