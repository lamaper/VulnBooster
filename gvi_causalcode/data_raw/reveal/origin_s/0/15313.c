proto_item * parseDouble ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo _U_ , gint * pOffset , int hfIndex ) {
 proto_item * item = proto_tree_add_item ( tree , hfIndex , tvb , * pOffset , ( int ) sizeof ( gdouble ) , ENC_LITTLE_ENDIAN ) ;
 * pOffset += ( int ) sizeof ( gdouble ) ;
 return item ;
 }