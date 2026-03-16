static gint dissect_vdp_cp_scms_t ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , void * data _U_ ) {
 proto_item * main_item ;
 proto_tree * main_tree ;
 gint offset = 0 ;
 main_item = proto_tree_add_item ( tree , proto_btvdp_cph_scms_t , tvb , offset , 1 , ENC_NA ) ;
 main_tree = proto_item_add_subtree ( main_item , ett_btvdp_cph_scms_t ) ;
 proto_tree_add_item ( main_tree , hf_btvdp_reserved , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( main_tree , hf_btvdp_cp_bit , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( main_tree , hf_btvdp_l_bit , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 return offset ;
 }