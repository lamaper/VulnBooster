static void dissect_rsvp_admin_status ( proto_tree * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 guint32 status ;
 static const int * status_flags [ ] = {
 & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_REFLECT ] , & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_HANDOVER ] , & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_LOCKOUT ] , & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_INHIBIT ] , & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_CALL_MGMT ] , & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_TESTING ] , & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_DOWN ] , & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_DELETE ] , NULL }
 ;
 proto_item_set_text ( ti , "ADMIN STATUS: " ) ;
 switch ( type ) {
 case 1 : proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 status = tvb_get_ntohl ( tvb , offset2 ) ;
 proto_tree_add_bitmask ( rsvp_object_tree , tvb , offset2 , hf_rsvp_admin_status_bits , TREE ( TT_ADMIN_STATUS_FLAGS ) , status_flags , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "ADMIN-STATUS: %s%s%s%s%s%s%s%s" , ( status & ( 1U << 31 ) ) ? "Reflect " : "" , ( status & ( 1U << 6 ) ) ? "Handover " : "" , ( status & ( 1U << 5 ) ) ? "Lockout " : "" , ( status & ( 1U << 4 ) ) ? "Inhibit " : "" , ( status & ( 1U << 3 ) ) ? "Call " : "" , ( status & ( 1U << 2 ) ) ? "Testing " : "" , ( status & ( 1U << 1 ) ) ? "Admin-Down " : "" , ( status & ( 1U << 0 ) ) ? "Deleting " : "" ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_admin_status_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }