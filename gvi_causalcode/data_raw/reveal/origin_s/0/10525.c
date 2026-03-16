static int dissect_h245_T_returnedFunction ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 proto_item * item ;
 proto_tree * subtree ;
 h245_packet_info * saved_h245_pi ;
 offset = dissect_per_octet_string ( tvb , offset , actx , tree , hf_index , NO_BOUND , NO_BOUND , FALSE , & next_tvb ) ;
 if ( next_tvb && tvb_length ( next_tvb ) ) {
 saved_h245_pi = h245_pi ;
 h245_pi = NULL ;
 item = proto_tree_add_text ( tree , next_tvb , 0 , - 1 , "The returned function" ) ;
 subtree = proto_item_add_subtree ( item , ett_h245_returnedFunction ) ;
 PROTO_ITEM_SET_GENERATED ( item ) ;
 dissect_h245_MultimediaSystemControlMessage ( next_tvb , 0 , actx , subtree , hf_h245_pdu_type ) ;
 h245_pi = saved_h245_pi ;
 }
 return offset ;
 }