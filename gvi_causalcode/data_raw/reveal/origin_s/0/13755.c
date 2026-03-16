proto_item * parseInt32 ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo _U_ , gint * pOffset , int hfIndex ) {
 proto_item * item = proto_tree_add_item ( tree , hfIndex , tvb , * pOffset , 4 , ENC_LITTLE_ENDIAN ) ;
 * pOffset += 4 ;
 return item ;
 }