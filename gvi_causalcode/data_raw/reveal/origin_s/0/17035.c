proto_item * parseGuid ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo _U_ , gint * pOffset , int hfIndex ) {
 proto_item * item = proto_tree_add_item ( tree , hfIndex , tvb , * pOffset , GUID_LEN , ENC_NA ) ;
 * pOffset += GUID_LEN ;
 return item ;
 }