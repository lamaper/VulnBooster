Oid get_relname_relid ( const char * relname , Oid relnamespace ) {
 return GetSysCacheOid2 ( RELNAMENSP , PointerGetDatum ( relname ) , ObjectIdGetDatum ( relnamespace ) ) ;
 }