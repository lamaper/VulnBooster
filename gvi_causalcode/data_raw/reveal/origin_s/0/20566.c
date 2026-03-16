static gboolean is_forward_circuit ( guint circuit_id , const iax_call_data * iax_call ) {
 guint i ;
 for ( i = 0 ;
 i < iax_call -> n_forward_circuit_ids ;
 i ++ ) {
 if ( circuit_id == iax_call -> forward_circuit_ids [ i ] ) return TRUE ;
 }
 return FALSE ;
 }