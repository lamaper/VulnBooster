static void show_setup_info ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree ) {
 struct _rtp_conversation_info * p_conv_data = NULL ;
 proto_tree * rtp_setup_tree ;
 proto_item * ti ;
 p_conv_data = ( struct _rtp_conversation_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_rtp , 0 ) ;
 if ( ! p_conv_data ) return ;
 ti = proto_tree_add_string_format ( tree , hf_rtp_setup , tvb , 0 , 0 , "" , "Stream setup by %s (frame %u)" , p_conv_data -> method , p_conv_data -> frame_number ) ;
 PROTO_ITEM_SET_GENERATED ( ti ) ;
 rtp_setup_tree = proto_item_add_subtree ( ti , ett_rtp_setup ) ;
 if ( rtp_setup_tree ) {
 proto_item * item = proto_tree_add_uint ( rtp_setup_tree , hf_rtp_setup_frame , tvb , 0 , 0 , p_conv_data -> frame_number ) ;
 PROTO_ITEM_SET_GENERATED ( item ) ;
 item = proto_tree_add_string ( rtp_setup_tree , hf_rtp_setup_method , tvb , 0 , 0 , p_conv_data -> method ) ;
 PROTO_ITEM_SET_GENERATED ( item ) ;
 }
 }