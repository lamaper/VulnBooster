Oid getTypeIOParam ( HeapTuple typeTuple ) {
 Form_pg_type typeStruct = ( Form_pg_type ) GETSTRUCT ( typeTuple ) ;
 if ( OidIsValid ( typeStruct -> typelem ) ) return typeStruct -> typelem ;
 else return HeapTupleGetOid ( typeTuple ) ;
 }