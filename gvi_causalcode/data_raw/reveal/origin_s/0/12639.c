void show_setup_info ( tvbuff_t * tvb , proto_tree * tree , t38_conv * p_t38_conversation ) {
 proto_tree * t38_setup_tree ;
 proto_item * ti ;
 if ( ! p_t38_conversation || p_t38_conversation -> setup_frame_number == 0 ) {
 return ;
 }
 ti = proto_tree_add_string_format ( tree , hf_t38_setup , tvb , 0 , 0 , "" , "Stream setup by %s (frame %u)" , p_t38_conversation -> setup_method , p_t38_conversation -> setup_frame_number ) ;
 PROTO_ITEM_SET_GENERATED ( ti ) ;
 t38_setup_tree = proto_item_add_subtree ( ti , ett_t38_setup ) ;
 if ( t38_setup_tree ) {
 proto_item * item = proto_tree_add_uint ( t38_setup_tree , hf_t38_setup_frame , tvb , 0 , 0 , p_t38_conversation -> setup_frame_number ) ;
 PROTO_ITEM_SET_GENERATED ( item ) ;
 item = proto_tree_add_string ( t38_setup_tree , hf_t38_setup_method , tvb , 0 , 0 , p_t38_conversation -> setup_method ) ;
 PROTO_ITEM_SET_GENERATED ( item ) ;
 }
 }