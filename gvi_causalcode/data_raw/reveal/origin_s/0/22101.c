static iax_packet_data * iax2_get_packet_data_for_minipacket ( packet_info * pinfo , guint16 scallno , gboolean video ) {
 iax_packet_data * p = ( iax_packet_data * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_iax2 , 0 ) ;
 if ( ! p ) {
 gboolean reversed ;
 iax_call_data * iax_call ;
 iax_call = iax_lookup_call ( pinfo , scallno , 0 , & reversed ) ;
 p = iax_new_packet_data ( iax_call , reversed ) ;
 p_add_proto_data ( wmem_file_scope ( ) , pinfo , proto_iax2 , 0 , p ) ;
 if ( iax_call ) {
 if ( video ) p -> codec = reversed ? iax_call -> dst_vformat : iax_call -> src_vformat ;
 else p -> codec = reversed ? iax_call -> dst_codec : iax_call -> src_codec ;
 }
 }
 iax2_populate_pinfo_from_packet_data ( pinfo , p ) ;
 return p ;
 }