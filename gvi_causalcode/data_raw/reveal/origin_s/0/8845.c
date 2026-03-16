static iax_call_data * iax_lookup_call ( packet_info * pinfo , guint32 scallno , guint32 dcallno , gboolean * reversed_p ) {
 gboolean reversed = FALSE ;
 iax_call_data * iax_call = NULL ;
 guint src_circuit_id ;


 dststr = address_to_str ( NULL , & pinfo -> dst ) ;
 g_debug ( "++ iax_lookup_circuit_details: Looking up circuit for frame %u, " "from {
%s:%u:%u}
 to {
%s:%u:%u}
" , pinfo -> fd -> num , srcstr , pinfo -> srcport , scallno , dststr , pinfo -> destport , dcallno ) ;
 wmem_free ( NULL , srcstr ) ;
 wmem_free ( NULL , dststr ) ;

 if ( dcallno != 0 ) {
 guint dst_circuit_id ;


 iax_call = iax_lookup_call_from_dest ( pinfo , NULL , src_circuit_id , dst_circuit_id , pinfo -> fd -> num , & reversed ) ;
 }
 else {
 circuit_t * src_circuit ;
 src_circuit = find_circuit ( CT_IAX2 , src_circuit_id , pinfo -> fd -> num ) ;
 if ( src_circuit ) {
 iax_call = ( iax_call_data * ) circuit_get_proto_data ( src_circuit , proto_iax2 ) ;
 DISSECTOR_ASSERT ( iax_call ) ;
 if ( is_forward_circuit ( src_circuit_id , iax_call ) ) reversed = FALSE ;
 else if ( is_reverse_circuit ( src_circuit_id , iax_call ) ) reversed = TRUE ;
 else {
 DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }
 }
 }
 if ( reversed_p ) * reversed_p = reversed ;

 g_debug ( "++ Found call for packet: id %u, reversed=%c" , iax_call -> forward_circuit_ids [ 0 ] , reversed ? '1' : '0' ) ;
 }
 else {
 g_debug ( "++ Call not found. Must have missed the NEW packet?" ) ;
 }

 }