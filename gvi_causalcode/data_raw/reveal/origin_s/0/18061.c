guint16 de_sup_codec_list ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guint8 length ;
 proto_tree * subtree ;
 guint8 sysid_counter ;
 curr_offset = offset ;
 sysid_counter = 0 ;
 while ( len > ( curr_offset - offset ) ) {
 sysid_counter ++ ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_sysid , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_bitmap_length , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 length = tvb_get_guint8 ( tvb , curr_offset ) ;
 curr_offset ++ ;
 if ( length > 0 ) {
 subtree = proto_tree_add_subtree_format ( tree , tvb , curr_offset , length , ett_gsm_dtap_elem [ DE_SUP_CODEC_LIST ] , NULL , "Codec Bitmap for SysID %u" , sysid_counter ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_tdma_efr , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_umts_amr_2 , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_umts_amr , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_hr_amr , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_fr_amr , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_gsm_efr , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_gsm_hr , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_gsm_fr , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 length -- ;
 if ( length > 0 ) {
 proto_tree_add_bits_item ( subtree , hf_gsm_a_spare_bits , tvb , curr_offset << 3 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_ohr_amr_wb , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_ofr_amr_wb , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_ohr_amr , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_umts_amr_wb , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_fr_amr_wb , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_codec_pdc_efr , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 length -- ;
 }
 }
 curr_offset = curr_offset + length ;
 }
 return ( curr_offset - offset ) ;
 }