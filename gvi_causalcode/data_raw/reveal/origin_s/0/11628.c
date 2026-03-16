static void dissect_rtmpt_body_aggregate ( tvbuff_t * tvb , gint offset , proto_tree * rtmpt_tree ) {
 proto_tree * tag_tree ;
 proto_tree * data_tree ;
 while ( tvb_reported_length_remaining ( tvb , offset ) > 0 ) {
 guint8 iTagType ;
 guint iDataSize ;
 iTagType = tvb_get_guint8 ( tvb , offset + 0 ) ;
 iDataSize = tvb_get_ntoh24 ( tvb , offset + 1 ) ;
 tag_tree = proto_tree_add_subtree ( rtmpt_tree , tvb , offset , 11 + iDataSize + 4 , ett_rtmpt_tag , NULL , val_to_str_const ( iTagType , rtmpt_tag_vals , "Unknown Tag" ) ) ;
 proto_tree_add_item ( tag_tree , hf_rtmpt_tag_type , tvb , offset + 0 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tag_tree , hf_rtmpt_tag_datasize , tvb , offset + 1 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tag_tree , hf_rtmpt_tag_timestamp , tvb , offset + 4 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tag_tree , hf_rtmpt_tag_ets , tvb , offset + 7 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tag_tree , hf_rtmpt_tag_streamid , tvb , offset + 8 , 3 , ENC_BIG_ENDIAN ) ;
 data_tree = proto_tree_add_subtree ( tag_tree , tvb , offset + 11 , iDataSize , ett_rtmpt_tag_data , NULL , "Data" ) ;
 switch ( iTagType ) {
 case 8 : dissect_rtmpt_body_audio ( tvb , offset + 11 , data_tree ) ;
 break ;
 case 9 : dissect_rtmpt_body_video ( tvb , offset + 11 , data_tree ) ;
 break ;
 case 18 : dissect_rtmpt_body_command ( tvb , offset + 11 , data_tree , FALSE ) ;
 break ;
 default : break ;
 }
 proto_tree_add_item ( tag_tree , hf_rtmpt_tag_tagsize , tvb , offset + 11 + iDataSize , 4 , ENC_BIG_ENDIAN ) ;
 offset += 11 + iDataSize + 4 ;
 }
 }