static void ns_parse_questions ( tvbuff_t * tvb , gint * offset , proto_tree * alljoyn_tree , guint8 questions , guint message_version ) {
 while ( questions -- ) {
 proto_item * alljoyn_questions_ti ;
 proto_tree * alljoyn_questions_tree ;
 gint count ;
 alljoyn_questions_ti = proto_tree_add_item ( alljoyn_tree , hf_alljoyn_ns_whohas , tvb , * offset , 2 , ENC_NA ) ;
 alljoyn_questions_tree = proto_item_add_subtree ( alljoyn_questions_ti , ett_alljoyn_whohas ) ;
 if ( 0 == message_version ) {
 proto_tree_add_item ( alljoyn_questions_tree , hf_alljoyn_ns_whohas_t_flag , tvb , * offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_questions_tree , hf_alljoyn_ns_whohas_u_flag , tvb , * offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_questions_tree , hf_alljoyn_ns_whohas_s_flag , tvb , * offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( alljoyn_questions_tree , hf_alljoyn_ns_whohas_f_flag , tvb , * offset , 1 , ENC_NA ) ;
 }
 ( * offset ) += 1 ;
 proto_tree_add_item ( alljoyn_questions_tree , hf_alljoyn_ns_whohas_count , tvb , * offset , 1 , ENC_NA ) ;
 count = tvb_get_guint8 ( tvb , * offset ) ;
 ( * offset ) += 1 ;
 while ( count -- ) {
 proto_item * alljoyn_bus_name_ti ;
 proto_tree * alljoyn_bus_name_tree ;
 gint bus_name_size = 0 ;
 bus_name_size = tvb_get_guint8 ( tvb , * offset ) ;
 alljoyn_bus_name_ti = proto_tree_add_item ( alljoyn_questions_tree , hf_alljoyn_string , tvb , * offset , 1 + bus_name_size , ENC_NA ) ;
 alljoyn_bus_name_tree = proto_item_add_subtree ( alljoyn_bus_name_ti , ett_alljoyn_ns_string ) ;
 proto_tree_add_item ( alljoyn_bus_name_tree , hf_alljoyn_string_size_8bit , tvb , * offset , 1 , ENC_NA ) ;
 ( * offset ) += 1 ;
 proto_tree_add_item ( alljoyn_bus_name_tree , hf_alljoyn_string_data , tvb , * offset , bus_name_size , ENC_ASCII | ENC_NA ) ;
 ( * offset ) += bus_name_size ;
 }
 }
 }