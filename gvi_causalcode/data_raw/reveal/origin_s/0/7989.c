proto_item * parseByteString ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo _U_ , gint * pOffset , int hfIndex ) {
 proto_item * item = NULL ;
 char * szValue ;
 int iOffset = * pOffset ;
 gint32 iLen = tvb_get_letohl ( tvb , iOffset ) ;
 iOffset += 4 ;
 if ( iLen == - 1 ) {
 item = proto_tree_add_item ( tree , hfIndex , tvb , * pOffset , 0 , ENC_NA ) ;
 proto_item_append_text ( item , "[OpcUa Null ByteString]" ) ;
 proto_item_set_end ( item , tvb , * pOffset + 4 ) ;
 }
 else if ( iLen == 0 ) {
 item = proto_tree_add_item ( tree , hfIndex , tvb , * pOffset , 0 , ENC_NA ) ;
 proto_item_append_text ( item , "[OpcUa Empty ByteString]" ) ;
 proto_item_set_end ( item , tvb , * pOffset + 4 ) ;
 }
 else if ( iLen > 0 ) {
 item = proto_tree_add_item ( tree , hfIndex , tvb , iOffset , iLen , ENC_NA ) ;
 iOffset += iLen ;
 }
 else {
 item = proto_tree_add_item ( tree , hfIndex , tvb , * pOffset , 0 , ENC_NA ) ;
 szValue = wmem_strdup_printf ( wmem_packet_scope ( ) , "[Invalid ByteString] Invalid length: %d" , iLen ) ;
 proto_item_append_text ( item , "%s" , szValue ) ;
 proto_item_set_end ( item , tvb , * pOffset + 4 ) ;
 }
 * pOffset = iOffset ;
 return item ;
 }