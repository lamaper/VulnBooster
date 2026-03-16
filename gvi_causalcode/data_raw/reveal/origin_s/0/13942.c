Oid get_opfamily_proc ( Oid opfamily , Oid lefttype , Oid righttype , int16 procnum ) {
 HeapTuple tp ;
 Form_pg_amproc amproc_tup ;
 RegProcedure result ;
 tp = SearchSysCache4 ( AMPROCNUM , ObjectIdGetDatum ( opfamily ) , ObjectIdGetDatum ( lefttype ) , ObjectIdGetDatum ( righttype ) , Int16GetDatum ( procnum ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) return InvalidOid ;
 amproc_tup = ( Form_pg_amproc ) GETSTRUCT ( tp ) ;
 result = amproc_tup -> amproc ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }