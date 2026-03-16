static guint8 * handle_message_header_fields ( tvbuff_t * tvb , packet_info * pinfo , proto_item * header_tree , guint encoding , gint offset , guint32 header_length , guint8 * signature_length ) {
 gint end_of_header ;
 proto_item * item ;
 proto_tree * tree ;
 guint8 * signature = NULL ;
 item = proto_tree_add_item ( header_tree , hf_alljoyn_mess_header_fields , tvb , offset , header_length , ENC_NA ) ;
 tree = proto_item_add_subtree ( item , ett_alljoyn_mess_header ) ;
 end_of_header = offset + header_length ;
 while ( offset < end_of_header ) {
 offset = handle_message_field ( tvb , pinfo , tree , encoding , offset , & signature , signature_length ) ;
 }
 return signature ;
 }