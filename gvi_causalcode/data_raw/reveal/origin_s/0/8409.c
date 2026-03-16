static void dissect_rsvp_session_attribute ( proto_item * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 guint8 flags ;
 guint8 name_len ;
 proto_tree * ti2 , * rsvp_sa_flags_tree ;
 switch ( type ) {
 case 1 : case 7 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "%u - IPv4 LSP (%sResource Affinities)" , type , ( type == 1 ) ? "" : "No " ) ;
 if ( type == 1 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_session_attribute_exclude_any , tvb , offset2 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_session_attribute_include_any , tvb , offset2 + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_session_attribute_include_all , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 offset2 = offset2 + 12 ;
 }
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_session_attribute_setup_priority , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_session_attribute_hold_priority , tvb , offset2 + 1 , 1 , ENC_BIG_ENDIAN ) ;
 flags = tvb_get_guint8 ( tvb , offset2 + 2 ) ;
 ti2 = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_session_attribute_flags , tvb , offset2 + 2 , 1 , ENC_BIG_ENDIAN ) ;
 rsvp_sa_flags_tree = proto_item_add_subtree ( ti2 , TREE ( TT_SESSION_ATTRIBUTE_FLAGS ) ) ;
 proto_tree_add_item ( rsvp_sa_flags_tree , hf_rsvp_sa_flags_local , tvb , offset2 + 2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_sa_flags_tree , hf_rsvp_sa_flags_label , tvb , offset2 + 2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_sa_flags_tree , hf_rsvp_sa_flags_se_style , tvb , offset2 + 2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_sa_flags_tree , hf_rsvp_sa_flags_bandwidth , tvb , offset2 + 2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_sa_flags_tree , hf_rsvp_sa_flags_node , tvb , offset2 + 2 , 1 , ENC_BIG_ENDIAN ) ;
 name_len = tvb_get_guint8 ( tvb , offset2 + 3 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_session_attribute_name_length , tvb , offset2 + 3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_session_attribute_name , tvb , offset2 + 4 , name_len , ENC_NA | ENC_ASCII ) ;
 proto_item_set_text ( ti , "SESSION ATTRIBUTE: SetupPrio %d, HoldPrio %d, %s%s%s%s%s [%s]" , tvb_get_guint8 ( tvb , offset2 ) , tvb_get_guint8 ( tvb , offset2 + 1 ) , flags & 0x01 ? "Local Protection, " : "" , flags & 0x02 ? "Label Recording, " : "" , flags & 0x04 ? "SE Style, " : "" , flags & 0x08 ? "Bandwidth Protection, " : "" , flags & 0x10 ? "Node Protection, " : "" , name_len ? tvb_format_text ( tvb , offset2 + 4 , name_len ) : "" ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_session_attribute_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }