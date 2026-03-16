static void dissect_rtmpt_body_scm ( tvbuff_t * tvb , gint offset , proto_tree * rtmpt_tree , guint scm ) {
 switch ( scm ) {
 case RTMPT_TYPE_CHUNK_SIZE : proto_tree_add_item ( rtmpt_tree , hf_rtmpt_scm_chunksize , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case RTMPT_TYPE_ABORT_MESSAGE : proto_tree_add_item ( rtmpt_tree , hf_rtmpt_scm_csid , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case RTMPT_TYPE_ACKNOWLEDGEMENT : proto_tree_add_item ( rtmpt_tree , hf_rtmpt_scm_seq , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case RTMPT_TYPE_UCM : proto_tree_add_item ( rtmpt_tree , hf_rtmpt_ucm_eventtype , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 break ;
 case RTMPT_TYPE_WINDOW : proto_tree_add_item ( rtmpt_tree , hf_rtmpt_scm_was , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case RTMPT_TYPE_PEER_BANDWIDTH : proto_tree_add_item ( rtmpt_tree , hf_rtmpt_scm_was , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rtmpt_tree , hf_rtmpt_scm_limittype , tvb , offset + 4 , 1 , ENC_BIG_ENDIAN ) ;
 break ;
 }
 }