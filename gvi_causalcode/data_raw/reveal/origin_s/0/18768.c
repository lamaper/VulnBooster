static int dissect_t38_T_field_data ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 guint32 value_len ;
 offset = dissect_per_octet_string ( tvb , offset , actx , tree , hf_index , 1 , 65535 , FALSE , & value_tvb ) ;
 value_len = tvb_reported_length ( value_tvb ) ;

 if ( value_len < 8 ) {
 col_append_fstr ( actx -> pinfo -> cinfo , COL_INFO , "[%s]" , tvb_bytes_to_str ( wmem_packet_scope ( ) , value_tvb , 0 , value_len ) ) ;
 }
 else {
 col_append_fstr ( actx -> pinfo -> cinfo , COL_INFO , "[%s...]" , tvb_bytes_to_str ( wmem_packet_scope ( ) , value_tvb , 0 , 7 ) ) ;
 }
 }
 if ( primary_part && ( Data_Field_item_num < 2 ) ) {
 fragment_head * frag_msg = NULL ;
 if ( Data_Field_field_type_value == 0 || Data_Field_field_type_value == 6 ) {
 gboolean save_fragmented = actx -> pinfo -> fragmented ;
 actx -> pinfo -> fragmented = TRUE ;
 if ( p_t38_packet_conv && p_t38_conv && ( p_t38_packet_conv_info -> reass_ID == 0 ) ) {
 p_t38_conv_info -> reass_ID = actx -> pinfo -> fd -> num ;
 p_t38_conv_info -> reass_start_seqnum = seq_number ;
 p_t38_conv_info -> time_first_t4_data = nstime_to_sec ( & actx -> pinfo -> rel_ts ) ;
 p_t38_conv_info -> additional_hdlc_data_field_counter = 0 ;
 p_t38_packet_conv_info -> reass_ID = p_t38_conv_info -> reass_ID ;
 p_t38_packet_conv_info -> reass_start_seqnum = p_t38_conv_info -> reass_start_seqnum ;
 p_t38_packet_conv_info -> seqnum_prev_data_field = p_t38_conv_info -> seqnum_prev_data_field ;
 p_t38_packet_conv_info -> additional_hdlc_data_field_counter = p_t38_conv_info -> additional_hdlc_data_field_counter ;
 p_t38_packet_conv_info -> time_first_t4_data = p_t38_conv_info -> time_first_t4_data ;
 }
 if ( seq_number == ( guint32 ) p_t38_packet_conv_info -> seqnum_prev_data_field ) {
 p_t38_packet_conv_info -> additional_hdlc_data_field_counter ++ ;
 if ( p_t38_conv ) {
 p_t38_conv_info -> additional_hdlc_data_field_counter = p_t38_packet_conv_info -> additional_hdlc_data_field_counter ;
 }
 }
 frag_msg = fragment_add_seq ( & data_reassembly_table , value_tvb , 0 , actx -> pinfo , p_t38_packet_conv_info -> reass_ID , NULL , seq_number - ( guint32 ) p_t38_packet_conv_info -> reass_start_seqnum + ( guint32 ) p_t38_packet_conv_info -> additional_hdlc_data_field_counter , value_len , TRUE , 0 ) ;
 p_t38_packet_conv_info -> seqnum_prev_data_field = ( gint32 ) seq_number ;
 process_reassembled_data ( tvb , offset , actx -> pinfo , "Reassembled T38" , frag_msg , & data_frag_items , NULL , tree ) ;
 if ( ! frag_msg ) {
 if ( Data_Field_field_type_value == 0 ) {
 col_append_fstr ( actx -> pinfo -> cinfo , COL_INFO , " (HDLC fragment %u)" , seq_number + ( guint32 ) p_t38_packet_conv_info -> additional_hdlc_data_field_counter - ( guint32 ) p_t38_packet_conv_info -> reass_start_seqnum ) ;
 }
 else {
 col_append_fstr ( actx -> pinfo -> cinfo , COL_INFO , " (t4-data fragment %u)" , seq_number - ( guint32 ) p_t38_packet_conv_info -> reass_start_seqnum ) ;
 }
 }
 actx -> pinfo -> fragmented = save_fragmented ;
 }
 }
 return offset ;
 }