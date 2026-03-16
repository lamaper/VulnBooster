static iax_call_data * iax_lookup_call_from_dest ( packet_info * pinfo , proto_item * item , guint src_circuit_id , guint dst_circuit_id , guint framenum , gboolean * reversed_p ) {
 circuit_t * dst_circuit ;
 iax_call_data * iax_call ;
 gboolean reversed = FALSE ;
 dst_circuit = find_circuit ( CT_IAX2 , dst_circuit_id , framenum ) ;
 if ( ! dst_circuit ) {


 return NULL ;
 }


 DISSECTOR_ASSERT ( iax_call ) ;
 if ( is_forward_circuit ( dst_circuit_id , iax_call ) ) {


 if ( iax_call -> n_reverse_circuit_ids == 0 ) {




 else if ( ! is_reverse_circuit ( src_circuit_id , iax_call ) ) {
 expert_add_info_format ( pinfo , item , & ei_iax_circuit_id_conflict , "IAX Packet %u from circuit ids %u->%u conflicts with earlier call with circuit ids %u->%u" , framenum , src_circuit_id , dst_circuit_id , iax_call -> forward_circuit_ids [ 0 ] , iax_call -> reverse_circuit_ids [ 0 ] ) ;
 return NULL ;
 }
 }
 else if ( is_reverse_circuit ( dst_circuit_id , iax_call ) ) {


 if ( ! is_forward_circuit ( src_circuit_id , iax_call ) ) {
 expert_add_info_format ( pinfo , item , & ei_iax_circuit_id_conflict , "IAX Packet %u from circuit ids %u->%u conflicts with earlier call with circuit ids %u->%u" , framenum , src_circuit_id , dst_circuit_id , iax_call -> forward_circuit_ids [ 0 ] , iax_call -> reverse_circuit_ids [ 0 ] ) ;
 if ( reversed_p ) * reversed_p = FALSE ;
 return NULL ;
 }
 }
 else {
 DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }
 if ( reversed_p ) * reversed_p = reversed ;
 return iax_call ;
 }