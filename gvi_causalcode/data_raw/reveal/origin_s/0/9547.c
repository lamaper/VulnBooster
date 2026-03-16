char * get_namespace_name_or_temp ( Oid nspid ) {
 if ( isTempNamespace ( nspid ) ) return "pg_temp" ;
 else return get_namespace_name ( nspid ) ;
 }