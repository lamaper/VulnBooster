static int dissect_rsl ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 proto_item * ti ;
 proto_tree * rsl_tree ;
 guint8 msg_type ;
 int offset = 0 ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "RSL" ) ;
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 msg_type = tvb_get_guint8 ( tvb , offset + 1 ) & 0x7f ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s " , val_to_str_ext ( msg_type , & rsl_msg_type_vals_ext , "unknown %u" ) ) ;
 top_tree = tree ;
 ti = proto_tree_add_item ( tree , proto_rsl , tvb , 0 , - 1 , ENC_NA ) ;
 if ( ! global_rsl_use_nano_bts ) {
 guint8 msg_disc = tvb_get_guint8 ( tvb , offset ) >> 1 ;
 if ( msg_disc == RSL_MSGDISC_IPACCESS ) return 0 ;
 }
 rsl_tree = proto_item_add_subtree ( ti , ett_rsl ) ;
 proto_tree_add_item ( rsl_tree , hf_rsl_msg_dsc , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsl_tree , hf_rsl_T_bit , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset = dissct_rsl_msg ( tvb , pinfo , rsl_tree , offset ) ;
 return offset ;
 }