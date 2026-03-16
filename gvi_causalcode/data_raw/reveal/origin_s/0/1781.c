char * get_collation_name ( Oid colloid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( COLLOID , ObjectIdGetDatum ( colloid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_collation colltup = ( Form_pg_collation ) GETSTRUCT ( tp ) ;
 char * result ;
 result = pstrdup ( NameStr ( colltup -> collname ) ) ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return NULL ;
 }