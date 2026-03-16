static void dissect_rsvp_label_request ( proto_item * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 static const value_string lab_req_type_str [ ] = {
 {
 1 , "" }
 , {
 2 , "(Label Request with ATM label Range)" }
 , {
 3 , "(Label Request with Frame-Relay label Range)" }
 , {
 4 , "(Generalized Label Request)" }
 , {
 5 , "(Generalized Channel_set Label Request)" }
 , {
 0 , NULL }
 }
 ;
 static value_string_ext lab_req_type_str_ext = VALUE_STRING_EXT_INIT ( lab_req_type_str ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "%d %s" , type , val_to_str_ext_const ( type , & lab_req_type_str_ext , "Unknown" ) ) ;
 switch ( type ) {
 case 1 : {
 unsigned short l3pid = tvb_get_ntohs ( tvb , offset2 + 2 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_request_l3pid , tvb , offset2 + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "LABEL REQUEST: Basic: L3PID: %s (0x%04x)" , val_to_str_const ( l3pid , etype_vals , "Unknown" ) , l3pid ) ;
 break ;
 }
 case 2 : {
 unsigned short l3pid = tvb_get_ntohs ( tvb , offset2 + 2 ) ;
 unsigned short min_vpi , min_vci , max_vpi , max_vci ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_request_l3pid , tvb , offset2 + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_request_m , tvb , offset2 + 4 , 1 , ENC_NA ) ;
 min_vpi = tvb_get_ntohs ( tvb , offset2 + 4 ) & 0x7f ;
 min_vci = tvb_get_ntohs ( tvb , offset2 + 6 ) ;
 max_vpi = tvb_get_ntohs ( tvb , offset2 + 8 ) & 0x7f ;
 max_vci = tvb_get_ntohs ( tvb , offset2 + 10 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_request_min_vpi , tvb , offset2 + 4 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_request_min_vci , tvb , offset2 + 6 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_request_max_vpi , tvb , offset2 + 8 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_request_max_vci , tvb , offset2 + 10 , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "LABEL REQUEST: ATM: L3PID: %s (0x%04x). VPI/VCI: Min: %d/%d, Max: %d/%d. %s Merge. " , val_to_str_const ( l3pid , etype_vals , "Unknown" ) , l3pid , min_vpi , min_vci , max_vpi , max_vci , ( tvb_get_guint8 ( tvb , offset2 + 4 ) & 0x80 ) ? "Can" : "Cannot" ) ;
 break ;
 }
 case 3 : {
 guint16 l3pid = tvb_get_ntohs ( tvb , offset2 + 2 ) ;
 guint32 min_dlci , max_dlci , dlci_len , dlci_len_code ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_request_l3pid , tvb , offset2 + 2 , 2 , ENC_BIG_ENDIAN ) ;
 dlci_len_code = ( tvb_get_ntohs ( tvb , offset2 + 4 ) & 0x0180 ) >> 7 ;
 min_dlci = tvb_get_ntohl ( tvb , offset2 + 4 ) & 0x7fffff ;
 max_dlci = tvb_get_ntohl ( tvb , offset2 + 8 ) & 0x7fffff ;
 switch ( dlci_len_code ) {
 case 0 : dlci_len = 10 ;
 min_dlci &= 0x3ff ;
 max_dlci &= 0x3ff ;
 break ;
 case 2 : dlci_len = 23 ;
 break ;
 default : dlci_len = 0 ;
 min_dlci = 0 ;
 max_dlci = 0 ;
 break ;
 }
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_dlci_length , tvb , offset2 + 4 , 2 , dlci_len , "%s (%d)" , ( dlci_len == 10 ) ? "10 bits" : ( dlci_len == 23 ) ? "23 bits" : "INVALID" , dlci_len_code ) ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_min_dlci , tvb , offset2 + 5 , 3 , min_dlci ) ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_max_dlci , tvb , offset2 + 8 , 2 , max_dlci ) ;
 proto_item_set_text ( ti , "LABEL REQUEST: Frame: L3PID: %s (0x%04x). DLCI Len: %s. Min DLCI: %d. Max DLCI: %d" , val_to_str_const ( l3pid , etype_vals , "Unknown" ) , l3pid , ( dlci_len == 10 ) ? "10 bits" : ( dlci_len == 23 ) ? "23 bits" : "INVALID" , min_dlci , max_dlci ) ;
 break ;
 }
 case 4 : case 5 : {
 unsigned short l3pid = tvb_get_ntohs ( tvb , offset2 + 2 ) ;
 unsigned char lsp_enc = tvb_get_guint8 ( tvb , offset2 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_request_lsp_encoding_type , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_request_switching_type , tvb , offset2 + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_g_pid , tvb , offset2 + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "LABEL REQUEST: Generalized: LSP Encoding=%s, " "Switching Type=%s, G-PID=%s " , rval_to_str ( lsp_enc , gmpls_lsp_enc_rvals , "Unknown (%d)" ) , rval_to_str ( tvb_get_guint8 ( tvb , offset2 + 1 ) , gmpls_switching_type_rvals , "Unknown (%d)" ) , rval_to_str_const ( l3pid , gmpls_gpid_rvals , val_to_str ( l3pid , etype_vals , "Unknown (0x%04x)" ) ) ) ;
 break ;
 }
 default : proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_request_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }