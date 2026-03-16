bool get_attstatsslot ( HeapTuple statstuple , Oid atttype , int32 atttypmod , int reqkind , Oid reqop , Oid * actualop , Datum * * values , int * nvalues , float4 * * numbers , int * nnumbers ) {
 Form_pg_statistic stats = ( Form_pg_statistic ) GETSTRUCT ( statstuple ) ;
 int i , j ;
 Datum val ;
 bool isnull ;
 ArrayType * statarray ;
 Oid arrayelemtype ;
 int narrayelem ;
 HeapTuple typeTuple ;
 Form_pg_type typeForm ;
 for ( i = 0 ;
 i < STATISTIC_NUM_SLOTS ;
 i ++ ) {
 if ( ( & stats -> stakind1 ) [ i ] == reqkind && ( reqop == InvalidOid || ( & stats -> staop1 ) [ i ] == reqop ) ) break ;
 }
 if ( i >= STATISTIC_NUM_SLOTS ) return false ;
 if ( actualop ) * actualop = ( & stats -> staop1 ) [ i ] ;
 if ( values ) {
 val = SysCacheGetAttr ( STATRELATTINH , statstuple , Anum_pg_statistic_stavalues1 + i , & isnull ) ;
 if ( isnull ) elog ( ERROR , "stavalues is null" ) ;
 statarray = DatumGetArrayTypeP ( val ) ;
 arrayelemtype = ARR_ELEMTYPE ( statarray ) ;
 typeTuple = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( arrayelemtype ) ) ;
 if ( ! HeapTupleIsValid ( typeTuple ) ) elog ( ERROR , "cache lookup failed for type %u" , arrayelemtype ) ;
 typeForm = ( Form_pg_type ) GETSTRUCT ( typeTuple ) ;
 deconstruct_array ( statarray , arrayelemtype , typeForm -> typlen , typeForm -> typbyval , typeForm -> typalign , values , NULL , nvalues ) ;
 if ( ! typeForm -> typbyval ) {
 for ( j = 0 ;
 j < * nvalues ;
 j ++ ) {
 ( * values ) [ j ] = datumCopy ( ( * values ) [ j ] , typeForm -> typbyval , typeForm -> typlen ) ;
 }
 }
 ReleaseSysCache ( typeTuple ) ;
 if ( ( Pointer ) statarray != DatumGetPointer ( val ) ) pfree ( statarray ) ;
 }
 if ( numbers ) {
 val = SysCacheGetAttr ( STATRELATTINH , statstuple , Anum_pg_statistic_stanumbers1 + i , & isnull ) ;
 if ( isnull ) elog ( ERROR , "stanumbers is null" ) ;
 statarray = DatumGetArrayTypeP ( val ) ;
 narrayelem = ARR_DIMS ( statarray ) [ 0 ] ;
 if ( ARR_NDIM ( statarray ) != 1 || narrayelem <= 0 || ARR_HASNULL ( statarray ) || ARR_ELEMTYPE ( statarray ) != FLOAT4OID ) elog ( ERROR , "stanumbers is not a 1-D float4 array" ) ;
 * numbers = ( float4 * ) palloc ( narrayelem * sizeof ( float4 ) ) ;
 memcpy ( * numbers , ARR_DATA_PTR ( statarray ) , narrayelem * sizeof ( float4 ) ) ;
 * nnumbers = narrayelem ;
 if ( ( Pointer ) statarray != DatumGetPointer ( val ) ) pfree ( statarray ) ;
 }
 return true ;
 }