void getTypeBinaryOutputInfo ( Oid type , Oid * typSend , bool * typIsVarlena ) {
 HeapTuple typeTuple ;
 Form_pg_type pt ;
 typeTuple = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( type ) ) ;
 if ( ! HeapTupleIsValid ( typeTuple ) ) elog ( ERROR , "cache lookup failed for type %u" , type ) ;
 pt = ( Form_pg_type ) GETSTRUCT ( typeTuple ) ;
 if ( ! pt -> typisdefined ) ereport ( ERROR , ( errcode ( ERRCODE_UNDEFINED_OBJECT ) , errmsg ( "type %s is only a shell" , format_type_be ( type ) ) ) ) ;
 if ( ! OidIsValid ( pt -> typsend ) ) ereport ( ERROR , ( errcode ( ERRCODE_UNDEFINED_FUNCTION ) , errmsg ( "no binary output function available for type %s" , format_type_be ( type ) ) ) ) ;
 * typSend = pt -> typsend ;
 * typIsVarlena = ( ! pt -> typbyval ) && ( pt -> typlen == - 1 ) ;
 ReleaseSysCache ( typeTuple ) ;
 }