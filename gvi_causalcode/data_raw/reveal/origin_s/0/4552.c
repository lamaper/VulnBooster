static void ns_parse_answers_v1 ( tvbuff_t * tvb , gint * offset , proto_tree * alljoyn_tree , guint8 answers ) {
 while ( answers -- ) {
 proto_item * alljoyn_answers_ti ;
 proto_tree * alljoyn_answers_tree ;
 gint flags ;
 gint count ;
 alljoyn_answers_ti = proto_tree_add_item ( alljoyn_tree , hf_alljoyn_answer , tvb , * offset , 2 , ENC_NA ) ;
 alljoyn_answers_tree = proto_item_add_subtree ( alljoyn_answers_ti , ett_alljoyn_ns_answers ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_g_flag , tvb , * offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_c_flag , tvb , * offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_r4_flag , tvb , * offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_u4_flag , tvb , * offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_r6_flag , tvb , * offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_u6_flag , tvb , * offset , 1 , ENC_NA ) ;
 flags = tvb_get_guint8 ( tvb , * offset ) ;
 ( * offset ) += 1 ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_count , tvb , * offset , 1 , ENC_NA ) ;
 count = tvb_get_guint8 ( tvb , * offset ) ;
 ( * offset ) += 1 ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_transport_mask , tvb , * offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_transport_mask_wfd , tvb , * offset , 2 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_transport_mask_ice , tvb , * offset , 2 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_transport_mask_lan , tvb , * offset , 2 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_transport_mask_wwan , tvb , * offset , 2 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_transport_mask_tcp , tvb , * offset , 2 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_transport_mask_bluetooth , tvb , * offset , 2 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_transport_mask_local , tvb , * offset , 2 , ENC_NA ) ;
 ( * offset ) += 2 ;
 if ( flags & ISAT_R4 ) {
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_ipv4 , tvb , * offset , 4 , ENC_BIG_ENDIAN ) ;
 ( * offset ) += 4 ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_port , tvb , * offset , 2 , ENC_BIG_ENDIAN ) ;
 ( * offset ) += 2 ;
 }
 if ( flags & ISAT_U4 ) {
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_ipv4 , tvb , * offset , 4 , ENC_BIG_ENDIAN ) ;
 ( * offset ) += 4 ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_port , tvb , * offset , 2 , ENC_BIG_ENDIAN ) ;
 ( * offset ) += 2 ;
 }
 if ( flags & ISAT_R6 ) {
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_ipv6 , tvb , * offset , 16 , ENC_NA ) ;
 ( * offset ) += 16 ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_port , tvb , * offset , 2 , ENC_BIG_ENDIAN ) ;
 ( * offset ) += 2 ;
 }
 if ( flags & ISAT_U6 ) {
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_ipv6 , tvb , * offset , 16 , ENC_NA ) ;
 ( * offset ) += 16 ;
 proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_ns_isat_port , tvb , * offset , 2 , ENC_BIG_ENDIAN ) ;
 ( * offset ) += 2 ;
 }
 if ( flags & ISAT_G ) {
 proto_item * alljoyn_string_ti ;
 proto_tree * alljoyn_string_tree ;
 gint guid_size ;
 guid_size = tvb_get_guint8 ( tvb , * offset ) ;
 alljoyn_string_ti = proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_isat_guid_string , tvb , * offset , 1 + guid_size , ENC_NA ) ;
 alljoyn_string_tree = proto_item_add_subtree ( alljoyn_string_ti , ett_alljoyn_ns_guid_string ) ;
 proto_tree_add_item ( alljoyn_string_tree , hf_alljoyn_string_size_8bit , tvb , * offset , 1 , ENC_NA ) ;
 ( * offset ) += 1 ;
 proto_tree_add_item ( alljoyn_string_tree , hf_alljoyn_string_data , tvb , * offset , guid_size , ENC_ASCII | ENC_NA ) ;
 ( * offset ) += guid_size ;
 }
 while ( count -- ) {
 proto_item * alljoyn_entry_ti ;
 proto_tree * alljoyn_entry_tree ;
 proto_tree * alljoyn_bus_name_ti ;
 proto_tree * alljoyn_bus_name_tree ;
 gint bus_name_size = tvb_get_guint8 ( tvb , * offset ) ;
 alljoyn_entry_ti = proto_tree_add_item ( alljoyn_answers_tree , hf_alljoyn_isat_entry , tvb , * offset , 1 + bus_name_size , ENC_NA ) ;
 alljoyn_entry_tree = proto_item_add_subtree ( alljoyn_entry_ti , ett_alljoyn_isat_entry ) ;
 alljoyn_bus_name_ti = proto_tree_add_item ( alljoyn_entry_tree , hf_alljoyn_string , tvb , * offset , 1 + bus_name_size , ENC_NA ) ;
 alljoyn_bus_name_tree = proto_item_add_subtree ( alljoyn_bus_name_ti , ett_alljoyn_string ) ;
 proto_tree_add_item ( alljoyn_bus_name_tree , hf_alljoyn_string_size_8bit , tvb , * offset , 1 , ENC_NA ) ;
 ( * offset ) += 1 ;
 proto_tree_add_item ( alljoyn_bus_name_tree , hf_alljoyn_string_data , tvb , * offset , bus_name_size , ENC_ASCII | ENC_NA ) ;
 ( * offset ) += bus_name_size ;
 }
 }
 }