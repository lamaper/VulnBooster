bool type_is_rowtype ( Oid typid ) {
 return ( typid == RECORDOID || get_typtype ( typid ) == TYPTYPE_COMPOSITE ) ;
 }