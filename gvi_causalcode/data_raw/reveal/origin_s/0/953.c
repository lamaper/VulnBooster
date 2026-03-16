Oid get_opfamily_member ( Oid opfamily , Oid lefttype , Oid righttype , int16 strategy ) {
 HeapTuple tp ;
 Form_pg_amop amop_tup ;
 Oid result ;
 tp = SearchSysCache4 ( AMOPSTRATEGY , ObjectIdGetDatum ( opfamily ) , ObjectIdGetDatum ( lefttype ) , ObjectIdGetDatum ( righttype ) , Int16GetDatum ( strategy ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) return InvalidOid ;
 amop_tup = ( Form_pg_amop ) GETSTRUCT ( tp ) ;
 result = amop_tup -> amopopr ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }