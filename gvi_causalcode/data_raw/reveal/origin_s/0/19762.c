static guint16 de_cause ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len , gchar * add_string , int string_len ) {
 guint8 oct ;
 guint8 cause ;
 guint32 curr_offset ;
 guint32 diag_length ;
 proto_tree * subtree ;
 const gchar * str ;
 curr_offset = offset ;
 proto_tree_add_item ( tree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_de_cause_coding_standard , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_location , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 if ( ! ( oct & 0x80 ) ) {
 proto_tree_add_item ( tree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_recommendation , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 }
 proto_tree_add_item ( tree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 cause = oct & 0x7f ;
 switch ( cause ) {
 case 1 : str = "Unassigned (unallocated) number" ;
 break ;
 case 3 : str = "No route to destination" ;
 break ;
 case 6 : str = "Channel unacceptable" ;
 break ;
 case 8 : str = "Operator determined barring" ;
 break ;
 case 16 : str = "Normal call clearing" ;
 break ;
 case 17 : str = "User busy" ;
 break ;
 case 18 : str = "No user responding" ;
 break ;
 case 19 : str = "User alerting, no answer" ;
 break ;
 case 21 : str = "Call rejected" ;
 break ;
 case 22 : str = "Call rejected due to feature at the destination" ;
 break ;
 case 24 : str = "Number changed" ;
 break ;
 case 25 : str = "Pre-emption" ;
 break ;
 case 26 : str = "Non selected user clearing" ;
 break ;
 case 27 : str = "Destination out of order" ;
 break ;
 case 28 : str = "Invalid number format (incomplete number)" ;
 break ;
 case 29 : str = "Facility rejected" ;
 break ;
 case 30 : str = "Response to STATUS ENQUIRY" ;
 break ;
 case 31 : str = "Normal, unspecified" ;
 break ;
 case 34 : str = "No circuit/channel available" ;
 break ;
 case 38 : str = "Network out of order" ;
 break ;
 case 41 : str = "Temporary failure" ;
 break ;
 case 42 : str = "Switching equipment congestion" ;
 break ;
 case 43 : str = "Access information discarded" ;
 break ;
 case 44 : str = "requested circuit/channel not available" ;
 break ;
 case 47 : str = "Resources unavailable, unspecified" ;
 break ;
 case 49 : str = "Quality of service unavailable" ;
 break ;
 case 50 : str = "Requested facility not subscribed" ;
 break ;
 case 55 : str = "Incoming calls barred within the CUG" ;
 break ;
 case 57 : str = "Bearer capability not authorized" ;
 break ;
 case 58 : str = "Bearer capability not presently available" ;
 break ;
 case 63 : str = "Service or option not available, unspecified" ;
 break ;
 case 65 : str = "Bearer service not implemented" ;
 break ;
 case 68 : str = "ACM equal to or greater than ACMmax" ;
 break ;
 case 69 : str = "Requested facility not implemented" ;
 break ;
 case 70 : str = "Only restricted digital information bearer capability is available" ;
 break ;
 case 79 : str = "Service or option not implemented, unspecified" ;
 break ;
 case 81 : str = "Invalid transaction identifier value" ;
 break ;
 case 87 : str = "User not member of CUG" ;
 break ;
 case 88 : str = "Incompatible destination" ;
 break ;
 case 91 : str = "Invalid transit network selection" ;
 break ;
 case 95 : str = "Semantically incorrect message" ;
 break ;
 case 96 : str = "Invalid mandatory information" ;
 break ;
 case 97 : str = "Message type non-existent or not implemented" ;
 break ;
 case 98 : str = "Message type not compatible with protocol state" ;
 break ;
 case 99 : str = "Information element non-existent or not implemented" ;
 break ;
 case 100 : str = "Conditional IE error" ;
 break ;
 case 101 : str = "Message not compatible with protocol state" ;
 break ;
 case 102 : str = "Recovery on timer expiry" ;
 break ;
 case 111 : str = "Protocol error, unspecified" ;
 break ;
 case 127 : str = "Interworking, unspecified" ;
 break ;
 default : if ( cause <= 31 ) {
 str = "Treat as Normal, unspecified" ;
 }
 else if ( ( cause >= 32 ) && ( cause <= 47 ) ) {
 str = "Treat as Resources unavailable, unspecified" ;
 }
 else if ( ( cause >= 48 ) && ( cause <= 63 ) ) {
 str = "Treat as Service or option not available, unspecified" ;
 }
 else if ( ( cause >= 64 ) && ( cause <= 79 ) ) {
 str = "Treat as Service or option not implemented, unspecified" ;
 }
 else if ( ( cause >= 80 ) && ( cause <= 95 ) ) {
 str = "Treat as Semantically incorrect message" ;
 }
 else if ( ( cause >= 96 ) && ( cause <= 111 ) ) {
 str = "Treat as Protocol error, unspecified" ;
 }
 else {
 str = "Treat as Interworking, unspecified" ;
 }
 break ;
 }
 proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_cause , tvb , curr_offset , 1 , cause , "Cause: (%u) %s" , cause , str ) ;
 curr_offset ++ ;
 if ( add_string ) g_snprintf ( add_string , string_len , " - (%u) %s" , cause , str ) ;
 NO_MORE_DATA_CHECK ( len ) ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , len - ( curr_offset - offset ) , ett_gsm_dtap_elem [ DE_CAUSE ] , NULL , "Diagnostics" ) ;
 if ( ( cause == 17 ) || ( cause == 29 ) || ( cause == 34 ) || ( cause == 50 ) || ( cause == 55 ) || ( cause == 69 ) || ( cause == 87 ) ) {
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_cause_ss_diagnostics , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 }
 else {
 diag_length = len - ( curr_offset - offset ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_data , tvb , curr_offset , diag_length , ENC_NA ) ;
 curr_offset += diag_length ;
 }
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }