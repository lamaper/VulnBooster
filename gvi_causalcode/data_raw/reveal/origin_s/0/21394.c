proto_item * parseString ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo _U_ , gint * pOffset , int hfIndex ) {
 proto_item * item = NULL ;
 char * szValue ;
 gint iOffset = * pOffset ;
 gint32 iLen = tvb_get_letohl ( tvb , * pOffset ) ;
 iOffset += 4 ;
 if ( iLen == - 1 ) {
 item = proto_tree_add_item ( tree , hfIndex , tvb , * pOffset , 0 , ENC_NA ) ;
 proto_item_append_text ( item , "[OpcUa Null String]" ) ;
 proto_item_set_end ( item , tvb , * pOffset + 4 ) ;
 }
 else if ( iLen == 0 ) {
 item = proto_tree_add_item ( tree , hfIndex , tvb , * pOffset , 0 , ENC_NA ) ;
 proto_item_append_text ( item , "[OpcUa Empty String]" ) ;
 proto_item_set_end ( item , tvb , * pOffset + 4 ) ;
 }
 else if ( iLen > 0 ) {
 item = proto_tree_add_item ( tree , hfIndex , tvb , iOffset , iLen , ENC_UTF_8 | ENC_NA ) ;
 iOffset += iLen ;
 }
 else {
 item = proto_tree_add_item ( tree , hfIndex , tvb , * pOffset , 0 , ENC_NA ) ;
 szValue = wmem_strdup_printf ( wmem_packet_scope ( ) , "[Invalid String] Invalid length: %d" , iLen ) ;
 proto_item_append_text ( item , "%s" , szValue ) ;
 proto_item_set_end ( item , tvb , * pOffset + 4 ) ;
 }
 * pOffset = iOffset ;
 return item ;
 }