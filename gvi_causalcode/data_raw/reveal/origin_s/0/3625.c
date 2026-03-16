static void dissect_rtmpt_body_video ( tvbuff_t * tvb , gint offset , proto_tree * rtmpt_tree ) {
 guint8 iCtl ;
 proto_item * vi ;
 proto_tree * vt ;
 iCtl = tvb_get_guint8 ( tvb , offset ) ;
 vi = proto_tree_add_uint_format ( rtmpt_tree , hf_rtmpt_video_control , tvb , offset , 1 , iCtl , "Control: 0x%02x (%s %s)" , iCtl , val_to_str_const ( ( iCtl & 0xf0 ) >> 4 , rtmpt_video_types , "Unknown frame type" ) , val_to_str_const ( iCtl & 0x0f , rtmpt_video_codecs , "Unknown codec" ) ) ;
 vt = proto_item_add_subtree ( vi , ett_rtmpt_video_control ) ;
 proto_tree_add_uint ( vt , hf_rtmpt_video_type , tvb , offset , 1 , iCtl ) ;
 proto_tree_add_uint ( vt , hf_rtmpt_video_format , tvb , offset , 1 , iCtl ) ;
 proto_tree_add_item ( rtmpt_tree , hf_rtmpt_video_data , tvb , offset + 1 , - 1 , ENC_NA ) ;
 }