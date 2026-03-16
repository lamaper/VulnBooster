static Selectivity mcelem_array_selec ( ArrayType * array , TypeCacheEntry * typentry , Datum * mcelem , int nmcelem , float4 * numbers , int nnumbers , float4 * hist , int nhist , Oid operator , FmgrInfo * cmpfunc ) {
 Selectivity selec ;
 int num_elems ;
 Datum * elem_values ;
 bool * elem_nulls ;
 bool null_present ;
 int nonnull_nitems ;
 int i ;
 deconstruct_array ( array , typentry -> type_id , typentry -> typlen , typentry -> typbyval , typentry -> typalign , & elem_values , & elem_nulls , & num_elems ) ;
 nonnull_nitems = 0 ;
 null_present = false ;
 for ( i = 0 ;
 i < num_elems ;
 i ++ ) {
 if ( elem_nulls [ i ] ) null_present = true ;
 else elem_values [ nonnull_nitems ++ ] = elem_values [ i ] ;
 }
 if ( null_present && operator == OID_ARRAY_CONTAINS_OP ) {
 pfree ( elem_values ) ;
 pfree ( elem_nulls ) ;
 return ( Selectivity ) 0.0 ;
 }
 qsort_arg ( elem_values , nonnull_nitems , sizeof ( Datum ) , element_compare , cmpfunc ) ;
 if ( operator == OID_ARRAY_CONTAINS_OP || operator == OID_ARRAY_OVERLAP_OP ) selec = mcelem_array_contain_overlap_selec ( mcelem , nmcelem , numbers , nnumbers , elem_values , nonnull_nitems , operator , cmpfunc ) ;
 else if ( operator == OID_ARRAY_CONTAINED_OP ) selec = mcelem_array_contained_selec ( mcelem , nmcelem , numbers , nnumbers , elem_values , nonnull_nitems , hist , nhist , operator , cmpfunc ) ;
 else {
 elog ( ERROR , "arraycontsel called for unrecognized operator %u" , operator ) ;
 selec = 0.0 ;
 }
 pfree ( elem_values ) ;
 pfree ( elem_nulls ) ;
 return selec ;
 }