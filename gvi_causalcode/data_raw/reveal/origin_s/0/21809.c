proto_item * parseDateTime ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo _U_ , gint * pOffset , int hfIndex ) {
 proto_item * item = NULL ;
 * pOffset = dissect_nt_64bit_time_ex ( tvb , tree , * pOffset , hfIndex , & item , FALSE ) ;
 return item ;
 }