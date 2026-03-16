void free_attstatsslot ( Oid atttype , Datum * values , int nvalues , float4 * numbers , int nnumbers ) {
 if ( values ) {
 if ( ! get_typbyval ( atttype ) ) {
 int i ;
 for ( i = 0 ;
 i < nvalues ;
 i ++ ) pfree ( DatumGetPointer ( values [ i ] ) ) ;
 }
 pfree ( values ) ;
 }
 if ( numbers ) pfree ( numbers ) ;
 }