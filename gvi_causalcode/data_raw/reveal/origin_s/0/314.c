static circuit_t * iax2_new_circuit_for_call ( packet_info * pinfo , proto_item * item , guint circuit_id , guint framenum , iax_call_data * iax_call , gboolean reversed ) {
 circuit_t * res ;
 if ( ! iax_call ) {
 return NULL ;
 }
 if ( ( reversed && iax_call -> n_reverse_circuit_ids >= IAX_MAX_TRANSFERS ) || ( ! reversed && iax_call -> n_forward_circuit_ids >= IAX_MAX_TRANSFERS ) ) {
 expert_add_info ( pinfo , item , & ei_iax_too_many_transfers ) ;
 return NULL ;
 }
 res = circuit_new ( CT_IAX2 , circuit_id , framenum ) ;
 circuit_add_proto_data ( res , proto_iax2 , iax_call ) ;
 if ( reversed ) iax_call -> reverse_circuit_ids [ iax_call -> n_reverse_circuit_ids ++ ] = circuit_id ;
 else iax_call -> forward_circuit_ids [ iax_call -> n_forward_circuit_ids ++ ] = circuit_id ;
 return res ;
 }