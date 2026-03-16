void getTypeBinaryInputInfo ( Oid type , Oid * typReceive , Oid * typIOParam ) {
 HeapTuple typeTuple ;
 Form_pg_type pt ;
 typeTuple = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( type ) ) ;
 if ( ! HeapTupleIsValid ( typeTuple ) ) elog ( ERROR , "cache lookup failed for type %u" , type ) ;
 pt = ( Form_pg_type ) GETSTRUCT ( typeTuple ) ;
 if ( ! pt -> typisdefined ) ereport ( ERROR , ( errcode ( ERRCODE_UNDEFINED_OBJECT ) , errmsg ( "type %s is only a shell" , format_type_be ( type ) ) ) ) ;
 if ( ! OidIsValid ( pt -> typreceive ) ) ereport ( ERROR , ( errcode ( ERRCODE_UNDEFINED_FUNCTION ) , errmsg ( "no binary input function available for type %s" , format_type_be ( type ) ) ) ) ;
 * typReceive = pt -> typreceive ;
 * typIOParam = getTypeIOParam ( typeTuple ) ;
 ReleaseSysCache ( typeTuple ) ;
 }