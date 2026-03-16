bool type_is_enum ( Oid typid ) {
 return ( get_typtype ( typid ) == TYPTYPE_ENUM ) ;
 }