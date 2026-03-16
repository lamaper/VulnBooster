char * get_constraint_name ( Oid conoid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( CONSTROID , ObjectIdGetDatum ( conoid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_constraint contup = ( Form_pg_constraint ) GETSTRUCT ( tp ) ;
 char * result ;
 result = pstrdup ( NameStr ( contup -> conname ) ) ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return NULL ;
 }