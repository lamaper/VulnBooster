static void dissect_rsvp_fast_reroute ( proto_tree * ti , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 guint8 flags ;
 proto_tree * ti2 , * rsvp_frr_flags_tree ;
 proto_item_set_text ( ti , "FAST_REROUTE: " ) ;
 switch ( type ) {
 case 1 : case 7 : if ( ( ( type == 1 ) && ( obj_length != 24 ) ) || ( ( type == 7 ) && ( obj_length != 20 ) ) ) {
 proto_tree_add_expert_format ( rsvp_object_tree , pinfo , & ei_rsvp_invalid_length , tvb , offset , obj_length , "Invalid length: cannot decode" ) ;
 proto_item_append_text ( ti , "Invalid length" ) ;
 break ;
 }
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_fast_reroute_setup_priority , tvb , offset + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_fast_reroute_hold_priority , tvb , offset + 5 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_fast_reroute_hop_limit , tvb , offset + 6 , 1 , ENC_BIG_ENDIAN ) ;
 flags = tvb_get_guint8 ( tvb , offset + 7 ) ;
 ti2 = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_fast_reroute_flags , tvb , offset + 7 , 1 , ENC_BIG_ENDIAN ) ;
 rsvp_frr_flags_tree = proto_item_add_subtree ( ti2 , TREE ( TT_FAST_REROUTE_FLAGS ) ) ;
 proto_tree_add_item ( rsvp_frr_flags_tree , hf_rsvp_frr_flags_one2one_backup , tvb , offset + 7 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_frr_flags_tree , hf_rsvp_frr_flags_facility_backup , tvb , offset + 7 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_fast_reroute_bandwidth , tvb , offset + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_fast_reroute_include_any , tvb , offset + 12 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_fast_reroute_exclude_any , tvb , offset + 16 , 4 , ENC_BIG_ENDIAN ) ;
 if ( type == 1 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_fast_reroute_include_all , tvb , offset + 20 , 4 , ENC_BIG_ENDIAN ) ;
 }
 proto_item_append_text ( ti , "%s%s" , flags & 0x01 ? "One-to-One Backup, " : "" , flags & 0x02 ? "Facility Backup" : "" ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_fast_reroute_data , tvb , offset + 4 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }