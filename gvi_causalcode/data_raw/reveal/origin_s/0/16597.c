Oid get_range_subtype ( Oid rangeOid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( RANGETYPE , ObjectIdGetDatum ( rangeOid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_range rngtup = ( Form_pg_range ) GETSTRUCT ( tp ) ;
 Oid result ;
 result = rngtup -> rngsubtype ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return InvalidOid ;
 }