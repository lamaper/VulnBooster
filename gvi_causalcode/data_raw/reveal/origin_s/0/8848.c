static guint16 dissect_rsvp_error_value ( proto_tree * ti , tvbuff_t * tvb , int offset , guint8 error_code ) {
 guint16 error_val ;
 guint8 error_class , error_ctype ;
 value_string_ext * rsvp_error_vals_ext_p = NULL ;
 error_val = tvb_get_ntohs ( tvb , offset ) ;
 switch ( error_code ) {
 case RSVP_ERROR_ADMISSION : rsvp_error_vals_ext_p = & rsvp_admission_control_error_vals_ext ;
 break ;
 case RSVP_ERROR_POLICY : rsvp_error_vals_ext_p = & rsvp_policy_control_error_vals_ext ;
 break ;
 case RSVP_ERROR_TRAFFIC : rsvp_error_vals_ext_p = & rsvp_traffic_control_error_vals_ext ;
 break ;
 case RSVP_ERROR_ROUTING : rsvp_error_vals_ext_p = & rsvp_routing_error_vals_ext ;
 break ;
 case RSVP_ERROR_NOTIFY : rsvp_error_vals_ext_p = & rsvp_notify_error_vals_ext ;
 break ;
 case RSVP_ERROR_DIFFSERV : rsvp_error_vals_ext_p = & rsvp_diffserv_error_vals_ext ;
 break ;
 case RSVP_ERROR_DSTE : rsvp_error_vals_ext_p = & rsvp_diffserv_aware_te_error_vals_ext ;
 break ;
 case RSVP_ERROR_CALL_MGMT : rsvp_error_vals_ext_p = & rsvp_call_mgmt_error_vals_ext ;
 break ;
 }
 switch ( error_code ) {
 case RSVP_ERROR_ADMISSION : case RSVP_ERROR_TRAFFIC : if ( ( error_val & 0xc0 ) == 0 ) {
 DISSECTOR_ASSERT ( rsvp_error_vals_ext_p != NULL ) ;
 proto_tree_add_uint_format_value ( ti , hf_rsvp_error_value , tvb , offset , 2 , error_val , "%s (%u)" , val_to_str_ext ( error_val , rsvp_error_vals_ext_p , "Unknown (%d)" ) , error_val ) ;
 }
 else if ( ( error_val & 0xc0 ) == 0x80 ) {
 proto_tree_add_uint_format_value ( ti , hf_rsvp_error_value , tvb , offset , 2 , error_val , "Organization specific subcode (%u)" , error_val ) ;
 }
 else if ( ( error_val & 0xc0 ) == 0xc0 ) {
 proto_tree_add_uint_format_value ( ti , hf_rsvp_error_value , tvb , offset , 2 , error_val , "Service specific subcode (%u)" , error_val ) ;
 }
 break ;
 case RSVP_ERROR_UNKNOWN_CLASS : case RSVP_ERROR_UNKNOWN_C_TYPE : error_class = error_val / 256 ;
 error_ctype = error_val % 256 ;
 proto_tree_add_uint_format_value ( ti , hf_rsvp_class , tvb , offset , 2 , error_class , "%u (%s) - CType: %u" , error_class , val_to_str_ext_const ( error_class , & rsvp_class_vals_ext , "Unknown" ) , error_ctype ) ;
 break ;
 case RSVP_ERROR_POLICY : case RSVP_ERROR_NOTIFY : case RSVP_ERROR_ROUTING : case RSVP_ERROR_DIFFSERV : case RSVP_ERROR_DSTE : case RSVP_ERROR_CALL_MGMT : DISSECTOR_ASSERT ( rsvp_error_vals_ext_p != NULL ) ;
 proto_tree_add_uint_format_value ( ti , hf_rsvp_error_value , tvb , offset , 2 , error_val , "%s (%u)" , val_to_str_ext ( error_val , rsvp_error_vals_ext_p , "Unknown (%d)" ) , error_val ) ;
 break ;
 default : proto_tree_add_uint_format_value ( ti , hf_rsvp_error_value , tvb , offset , 2 , error_val , "%u" , error_val ) ;
 break ;
 }
 return error_val ;
 }