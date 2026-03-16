static int dissect_t38_T_field_type ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_enumerated ( tvb , offset , actx , tree , hf_index , 8 , & Data_Field_field_type_value , ( use_pre_corrigendum_asn1_specification ) ? FALSE : TRUE , ( use_pre_corrigendum_asn1_specification ) ? 0 : 4 , NULL ) ;

 col_append_fstr ( actx -> pinfo -> cinfo , COL_INFO , " %s" , val_to_str ( Data_Field_field_type_value , t38_T_field_type_vals , "<unknown>" ) ) ;
 }
 if ( primary_part && ( Data_Field_item_num < 2 ) ) {
 if ( Data_Field_field_type_value == 2 || Data_Field_field_type_value == 4 || Data_Field_field_type_value == 7 ) {
 fragment_head * frag_msg = NULL ;
 tvbuff_t * new_tvb = NULL ;
 gboolean save_fragmented = actx -> pinfo -> fragmented ;
 actx -> pinfo -> fragmented = TRUE ;
 if ( p_t38_packet_conv_info -> reass_start_seqnum != - 1 ) {
 frag_msg = fragment_add_seq ( & data_reassembly_table , tvb , offset , actx -> pinfo , p_t38_packet_conv_info -> reass_ID , NULL , seq_number + Data_Field_item_num - ( guint32 ) p_t38_packet_conv_info -> reass_start_seqnum + ( guint32 ) p_t38_packet_conv_info -> additional_hdlc_data_field_counter , 0 , FALSE , 0 ) ;
 if ( Data_Field_field_type_value == 7 ) {
 if ( ! frag_msg ) {
 force_reassemble_seq ( & data_reassembly_table , actx -> pinfo , p_t38_packet_conv_info -> reass_ID ) ;
 }
 else {
 col_append_str ( actx -> pinfo -> cinfo , COL_INFO , " (t4-data Reassembled: No packet lost)" ) ;
 g_snprintf ( t38_info -> desc_comment , MAX_T38_DESC , "No packet lost" ) ;
 }
 if ( p_t38_packet_conv_info -> packet_lost ) {
 g_snprintf ( t38_info -> desc_comment , MAX_T38_DESC , " Pack lost: %d, Pack burst lost: %d" , p_t38_packet_conv_info -> packet_lost , p_t38_packet_conv_info -> burst_lost ) ;
 }
 else {
 g_snprintf ( t38_info -> desc_comment , MAX_T38_DESC , "No packet lost" ) ;
 }
 process_reassembled_data ( tvb , offset , actx -> pinfo , "Reassembled T38" , frag_msg , & data_frag_items , NULL , tree ) ;
 actx -> pinfo -> fragmented = save_fragmented ;
 t38_info -> time_first_t4_data = p_t38_packet_conv_info -> time_first_t4_data ;
 t38_info -> frame_num_first_t4_data = p_t38_packet_conv_info -> reass_ID ;
 }
 else {
 new_tvb = process_reassembled_data ( tvb , offset , actx -> pinfo , "Reassembled T38" , frag_msg , & data_frag_items , NULL , tree ) ;
 actx -> pinfo -> fragmented = save_fragmented ;
 if ( new_tvb ) call_dissector_with_data ( ( t30_hdlc_handle ) ? t30_hdlc_handle : data_handle , new_tvb , actx -> pinfo , tree , t38_info ) ;
 }
 }
 else {
 proto_tree_add_expert_format ( tree , actx -> pinfo , & ei_t38_malformed , tvb , offset , tvb_reported_length_remaining ( tvb , offset ) , "[RECEIVED END OF FRAGMENT W/OUT ANY FRAGMENT DATA]" ) ;
 col_append_str ( actx -> pinfo -> cinfo , COL_INFO , " [Malformed?]" ) ;
 actx -> pinfo -> fragmented = save_fragmented ;
 }
 }
 if ( p_t38_conv && ( ( ( Data_Field_field_type_value > 0 ) && ( Data_Field_field_type_value < 6 ) ) || ( Data_Field_field_type_value == 7 ) ) ) {
 p_t38_conv_info -> reass_ID = 0 ;
 p_t38_conv_info -> reass_start_seqnum = - 1 ;
 p_t38_conv_info -> additional_hdlc_data_field_counter = 0 ;
 p_t38_conv_info -> seqnum_prev_data_field = - 1 ;
 }
 t38_info -> Data_Field_field_type_value = Data_Field_field_type_value ;
 }
 return offset ;
 }