Oid get_commutator ( Oid opno ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( OPEROID , ObjectIdGetDatum ( opno ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_operator optup = ( Form_pg_operator ) GETSTRUCT ( tp ) ;
 Oid result ;
 result = optup -> oprcom ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return InvalidOid ;
 }