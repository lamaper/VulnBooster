static gint dissect_seid ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gint offset , gint seid_side , gint i_item , guint32 * sep_seid , guint32 interface_id , guint32 adapter_id , guint32 chandle , guint32 frame_number ) {
 guint32 seid ;
 proto_tree * seid_tree = NULL ;
 proto_item * seid_item = NULL ;
 guint32 direction ;
 seid = tvb_get_guint8 ( tvb , offset ) >> 2 ;
 if ( sep_seid ) {
 * sep_seid = seid ;
 }
 if ( seid_side == SEID_ACP ) {
 direction = pinfo -> p2p_dir ;
 seid_item = proto_tree_add_none_format ( tree , hf_btavdtp_acp_seid_item , tvb , offset , 1 , "ACP SEID [%u - %s %s]" , seid , get_sep_media_type ( interface_id , adapter_id , chandle , direction , seid , frame_number ) , get_sep_type ( interface_id , adapter_id , chandle , direction , seid , frame_number ) ) ;
 seid_tree = proto_item_add_subtree ( seid_item , ett_btavdtp_sep ) ;
 proto_tree_add_item ( seid_tree , hf_btavdtp_acp_seid , tvb , offset , 1 , ENC_NA ) ;
 if ( i_item > 0 ) proto_item_append_text ( seid_item , " item %u" , i_item ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " - ACP SEID [%u - %s %s]" , seid , get_sep_media_type ( interface_id , adapter_id , chandle , direction , seid , frame_number ) , get_sep_type ( interface_id , adapter_id , chandle , direction , seid , frame_number ) ) ;
 }
 else {
 direction = ( pinfo -> p2p_dir == P2P_DIR_SENT ) ? P2P_DIR_RECV : P2P_DIR_SENT ;
 seid_item = proto_tree_add_none_format ( tree , hf_btavdtp_int_seid_item , tvb , offset , 1 , "INT SEID [%u - %s %s]" , seid , get_sep_media_type ( interface_id , adapter_id , chandle , direction , seid , frame_number ) , get_sep_type ( interface_id , adapter_id , chandle , direction , seid , frame_number ) ) ;
 seid_tree = proto_item_add_subtree ( seid_item , ett_btavdtp_sep ) ;
 proto_tree_add_item ( seid_tree , hf_btavdtp_int_seid , tvb , offset , 1 , ENC_NA ) ;
 if ( i_item > 0 ) proto_item_append_text ( seid_item , " item %u" , i_item ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " - INT SEID [%u - %s %s]" , seid , get_sep_media_type ( interface_id , adapter_id , chandle , direction , seid , frame_number ) , get_sep_type ( interface_id , adapter_id , chandle , direction , seid , frame_number ) ) ;
 }
 proto_tree_add_item ( seid_tree , hf_btavdtp_rfa_seid , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 return offset ;
 }