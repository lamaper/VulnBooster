static void dissect_rtmpt_body_audio ( tvbuff_t * tvb , gint offset , proto_tree * rtmpt_tree ) {
 guint8 iCtl ;
 proto_item * ai ;
 proto_tree * at ;
 iCtl = tvb_get_guint8 ( tvb , offset ) ;
 ai = proto_tree_add_uint_format ( rtmpt_tree , hf_rtmpt_audio_control , tvb , offset , 1 , iCtl , "Control: 0x%02x (%s %s %s %s)" , iCtl , val_to_str_const ( ( iCtl & 0xf0 ) >> 4 , rtmpt_audio_codecs , "Unknown codec" ) , val_to_str_const ( ( iCtl & 0x0c ) >> 2 , rtmpt_audio_rates , "Unknown rate" ) , val_to_str_const ( ( iCtl & 0x02 ) >> 1 , rtmpt_audio_sizes , "Unknown sample size" ) , val_to_str_const ( iCtl & 0x01 , rtmpt_audio_types , "Unknown channel count" ) ) ;
 at = proto_item_add_subtree ( ai , ett_rtmpt_audio_control ) ;
 proto_tree_add_uint ( at , hf_rtmpt_audio_format , tvb , offset , 1 , iCtl ) ;
 proto_tree_add_uint ( at , hf_rtmpt_audio_rate , tvb , offset , 1 , iCtl ) ;
 proto_tree_add_uint ( at , hf_rtmpt_audio_size , tvb , offset , 1 , iCtl ) ;
 proto_tree_add_uint ( at , hf_rtmpt_audio_type , tvb , offset , 1 , iCtl ) ;
 proto_tree_add_item ( rtmpt_tree , hf_rtmpt_audio_data , tvb , offset + 1 , - 1 , ENC_NA ) ;
 }