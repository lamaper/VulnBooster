static gboolean is_reverse_circuit ( guint circuit_id , const iax_call_data * iax_call ) {
 guint i ;
 for ( i = 0 ;
 i < iax_call -> n_reverse_circuit_ids ;
 i ++ ) {
 if ( circuit_id == iax_call -> reverse_circuit_ids [ i ] ) return TRUE ;
 }
 return FALSE ;
 }