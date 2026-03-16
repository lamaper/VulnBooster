int32 get_attavgwidth ( Oid relid , AttrNumber attnum ) {
 HeapTuple tp ;
 int32 stawidth ;
 if ( get_attavgwidth_hook ) {
 stawidth = ( * get_attavgwidth_hook ) ( relid , attnum ) ;
 if ( stawidth > 0 ) return stawidth ;
 }
 tp = SearchSysCache3 ( STATRELATTINH , ObjectIdGetDatum ( relid ) , Int16GetDatum ( attnum ) , BoolGetDatum ( false ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 stawidth = ( ( Form_pg_statistic ) GETSTRUCT ( tp ) ) -> stawidth ;
 ReleaseSysCache ( tp ) ;
 if ( stawidth > 0 ) return stawidth ;
 }
 return 0 ;
 }