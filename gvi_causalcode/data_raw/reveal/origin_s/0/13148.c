int dissect_h225_GenericIdentifier ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 proto_item * ti ;
 offset = dissect_per_choice ( tvb , offset , actx , tree , hf_index , ett_h225_GenericIdentifier , GenericIdentifier_choice , NULL ) ;

 gefx = gef_ctx_get ( actx -> private_data ) ;
 if ( gefx ) {
 ti = proto_tree_add_string ( tree , hf_h225_debug_dissector_try_string , tvb , offset >> 3 , 0 , gefx -> key ) ;
 PROTO_ITEM_SET_HIDDEN ( ti ) ;
 dissector_try_string ( gef_name_dissector_table , gefx -> key , tvb_new_subset ( tvb , offset >> 3 , 0 , 0 ) , actx -> pinfo , tree , actx ) ;
 }
 actx -> private_data = gefx ;
 return offset ;
 }