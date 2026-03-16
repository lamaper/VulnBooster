Node * get_typdefault ( Oid typid ) {
 HeapTuple typeTuple ;
 Form_pg_type type ;
 Datum datum ;
 bool isNull ;
 Node * expr ;
 typeTuple = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( ! HeapTupleIsValid ( typeTuple ) ) elog ( ERROR , "cache lookup failed for type %u" , typid ) ;
 type = ( Form_pg_type ) GETSTRUCT ( typeTuple ) ;
 datum = SysCacheGetAttr ( TYPEOID , typeTuple , Anum_pg_type_typdefaultbin , & isNull ) ;
 if ( ! isNull ) {
 expr = stringToNode ( TextDatumGetCString ( datum ) ) ;
 }
 else {
 datum = SysCacheGetAttr ( TYPEOID , typeTuple , Anum_pg_type_typdefault , & isNull ) ;
 if ( ! isNull ) {
 char * strDefaultVal ;
 strDefaultVal = TextDatumGetCString ( datum ) ;
 datum = OidInputFunctionCall ( type -> typinput , strDefaultVal , getTypeIOParam ( typeTuple ) , - 1 ) ;
 expr = ( Node * ) makeConst ( typid , - 1 , type -> typcollation , type -> typlen , datum , false , type -> typbyval ) ;
 pfree ( strDefaultVal ) ;
 }
 else {
 expr = NULL ;
 }
 }
 ReleaseSysCache ( typeTuple ) ;
 return expr ;
 }