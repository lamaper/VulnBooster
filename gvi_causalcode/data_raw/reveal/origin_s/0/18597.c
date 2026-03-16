int dissect_ber_UTCTime ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint hf_id ) {
 char outstr [ 33 ] ;
 char * outstrptr = outstr ;
 const guint8 * instr ;
 gint8 ber_class ;
 gboolean pc ;
 gint32 tag ;
 guint32 len , i , n ;
 int hoffset ;
 proto_item * cause ;
 proto_tree * error_tree ;
 const gchar * error_str = NULL ;
 if ( ! implicit_tag ) {
 hoffset = offset ;
 offset = dissect_ber_identifier ( actx -> pinfo , tree , tvb , offset , & ber_class , & pc , & tag ) ;
 offset = dissect_ber_length ( actx -> pinfo , tree , tvb , offset , & len , NULL ) ;
 if ( ( ber_class != BER_CLASS_UNI ) || ( tag != BER_UNI_TAG_UTCTime ) ) {
 tvb_ensure_bytes_exist ( tvb , hoffset , 2 ) ;
 cause = proto_tree_add_string_format_value ( tree , hf_ber_error , tvb , offset , len , "utctime_expected" , "UTCTime expected but class:%s(%d) %s tag:%d was unexpected" , val_to_str_const ( ber_class , ber_class_codes , "Unknown" ) , ber_class , pc ? ber_pc_codes_short . true_string : ber_pc_codes_short . false_string , tag ) ;
 expert_add_info ( actx -> pinfo , cause , & ei_ber_expected_utc_time ) ;
 if ( decode_unexpected ) {
 proto_tree * unknown_tree = proto_item_add_subtree ( cause , ett_ber_unknown ) ;
 dissect_unknown_ber ( actx -> pinfo , tvb , hoffset , unknown_tree ) ;
 }
 return offset + len ;
 }
 }
 else {
 len = tvb_reported_length_remaining ( tvb , offset ) ;
 }
 if ( ( len < 10 ) || ( len > 19 ) ) {
 error_str = wmem_strdup_printf ( wmem_packet_scope ( ) , "BER Error: UTCTime invalid length: %u" , len ) ;
 instr = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset , len > 19 ? 19 : len , ENC_ASCII ) ;
 goto malformed ;
 }
 instr = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset , len , ENC_ASCII ) ;
 for ( i = 0 ;
 i < 10 ;
 i ++ ) {
 if ( ( instr [ i ] < '0' ) || ( instr [ i ] > '9' ) ) {
 error_str = "BER Error: malformed UTCTime encoding, " "first 10 octets have to contain YYMMDDhhmm in digits" ;
 goto malformed ;
 }
 }
 g_snprintf ( outstrptr , 15 , "%.2s-%.2s-%.2s %.2s:%.2s" , instr , instr + 2 , instr + 4 , instr + 6 , instr + 8 ) ;
 outstrptr += 14 ;
 if ( len >= 12 ) {
 if ( ( instr [ i ] >= '0' ) && ( instr [ i ] <= '9' ) ) {
 i ++ ;
 if ( ( instr [ i ] >= '0' ) && ( instr [ i ] <= '9' ) ) {
 i ++ ;
 g_snprintf ( outstrptr , 4 , ":%.2s" , instr + 10 ) ;
 outstrptr += 3 ;
 }
 else {
 error_str = "BER Error: malformed UTCTime encoding, " "if 11th octet is a digit for seconds, " "the 12th octet has to be a digit, too" ;
 goto malformed ;
 }
 }
 }
 switch ( instr [ i ] ) {
 case 'Z' : if ( len != ( i + 1 ) ) {
 error_str = "BER Error: malformed UTCTime encoding, " "there must be no further octets after \'Z\'" ;
 goto malformed ;
 }
 g_snprintf ( outstrptr , 7 , " (UTC)" ) ;
 i ++ ;
 break ;
 case '-' : case '+' : if ( len != ( i + 5 ) ) {
 error_str = "BER Error: malformed UTCTime encoding, " "4 digits must follow on \'+\' resp. \'-\'" ;
 goto malformed ;
 }
 for ( n = i + 1 ;
 n < i + 5 ;
 n ++ ) {
 if ( ( instr [ n ] < '0' ) || ( instr [ n ] > '9' ) ) {
 error_str = "BER Error: malformed UTCTime encoding, " "4 digits must follow on \'+\' resp. \'-\'" ;
 goto malformed ;
 }
 }
 g_snprintf ( outstrptr , 12 , " (UTC%c%.4s)" , instr [ i ] , instr + i + 1 ) ;
 i += 5 ;
 break ;
 default : error_str = wmem_strdup_printf ( wmem_packet_scope ( ) , "BER Error: malformed UTCTime encoding, " "unexpected character in %dth octet, " "must be \'Z\', \'+\' or \'-\'" , i + 1 ) ;
 goto malformed ;
 break ;
 }
 if ( len != i ) {
 error_str = wmem_strdup_printf ( wmem_packet_scope ( ) , "BER Error: malformed UTCTime encoding, %d unexpected character%s after %dth octet" , len - i , ( len == ( i - 1 ) ? "s" : "" ) , i ) ;
 goto malformed ;
 }
 if ( hf_id >= 0 ) {
 proto_tree_add_string ( tree , hf_id , tvb , offset , len , outstr ) ;
 }
 return offset + len ;
 malformed : if ( hf_id >= 0 ) {
 cause = proto_tree_add_string ( tree , hf_id , tvb , offset , len , instr ) ;
 error_tree = proto_item_add_subtree ( cause , ett_ber_unknown ) ;
 }
 else {
 error_tree = tree ;
 }
 cause = proto_tree_add_string_format ( error_tree , hf_ber_error , tvb , offset , len , "invalid_utctime" , "%s" , error_str ) ;
 expert_add_info ( actx -> pinfo , cause , & ei_ber_invalid_format_utctime ) ;
 return offset + len ;
 }