static int dissect_h245_DataType ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 offset = dissect_per_choice ( tvb , offset , actx , tree , hf_index , ett_h245_DataType , DataType_choice , & choice_index ) ;
 if ( upcoming_channel ) {
 if ( choice_index == 2 ) {
 upcoming_channel -> is_video = TRUE ;
 }
 else {
 upcoming_channel -> is_video = FALSE ;
 }
 }
 return offset ;
 }