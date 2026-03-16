static void dissect_rsvp_gen_uni ( proto_tree * ti , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type , rsvp_conversation_info * rsvph ) {
 int offset2 = offset + 4 ;
 int mylen , i , j , k , l ;
 proto_item * ti2 = NULL , * len_item ;
 proto_tree * rsvp_gen_uni_subtree , * rsvp_session_subtree , * rsvp_template_subtree ;
 int s_len , s_class , s_type , sobj_len , nsap_len ;
 int offset3 ;
 proto_item_set_text ( ti , "GENERALIZED UNI: " ) ;
 mylen = obj_length - 4 ;
 switch ( type ) {
 case 1 : {
 const char * c ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 for ( i = 1 , l = 0 ;
 l < mylen ;
 i ++ ) {
 sobj_len = tvb_get_ntohs ( tvb , offset2 + l ) ;
 j = tvb_get_guint8 ( tvb , offset2 + l + 2 ) ;
 switch ( j ) {
 case 1 : case 2 : c = ( j == 1 ) ? "Source" : "Destination" ;
 k = tvb_get_guint8 ( tvb , offset2 + l + 3 ) ;
 switch ( k ) {
 case 1 : rsvp_gen_uni_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset2 + l , 8 , TREE ( TT_GEN_UNI_SUBOBJ ) , NULL , "%s IPv4 TNA: %s" , c , tvb_ip_to_str ( tvb , offset2 + l + 4 ) ) ;
 proto_tree_add_uint_format_value ( rsvp_gen_uni_subtree , hf_rsvp_class , tvb , offset2 + l + 2 , 1 , j , "%d (%s)" , j , c ) ;
 proto_tree_add_uint_format_value ( rsvp_gen_uni_subtree , hf_rsvp_type , tvb , offset2 + l + 3 , 1 , k , "1 (IPv4)" ) ;
 proto_tree_add_uint ( rsvp_gen_uni_subtree , hf_rsvp_class_length , tvb , offset2 + l , 2 , sobj_len ) ;
 if ( j == 1 ) proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_filter [ RSVPF_GUNI_SRC_IPV4 ] , tvb , offset2 + l + 4 , 4 , ENC_BIG_ENDIAN ) ;
 else proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_filter [ RSVPF_GUNI_DST_IPV4 ] , tvb , offset2 + l + 4 , 4 , ENC_BIG_ENDIAN ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "%s IPv4 TNA: %s" , c , tvb_ip_to_str ( tvb , offset2 + l + 4 ) ) ;
 }
 break ;
 case 2 : rsvp_gen_uni_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset2 + l , 20 , TREE ( TT_GEN_UNI_SUBOBJ ) , NULL , "%s IPv6 TNA:" , c ) ;
 proto_tree_add_uint_format_value ( rsvp_gen_uni_subtree , hf_rsvp_class , tvb , offset2 + l + 2 , 1 , j , "%d (%s)" , j , c ) ;
 proto_tree_add_uint_format_value ( rsvp_gen_uni_subtree , hf_rsvp_type , tvb , offset2 + l + 3 , 1 , k , "2 (IPv6)" ) ;
 proto_tree_add_uint ( rsvp_gen_uni_subtree , hf_rsvp_class_length , tvb , offset2 + l , 2 , sobj_len ) ;
 if ( j == 1 ) proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_filter [ RSVPF_GUNI_SRC_IPV6 ] , tvb , offset2 + l + 4 , 16 , ENC_NA ) ;
 else proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_filter [ RSVPF_GUNI_DST_IPV6 ] , tvb , offset2 + l + 4 , 16 , ENC_NA ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "%s IPv6 TNA: %s" , c , tvb_ip6_to_str ( tvb , offset2 + l + 4 ) ) ;
 }
 break ;
 case 3 : rsvp_gen_uni_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset2 + l , tvb_get_ntohs ( tvb , offset2 + l ) , TREE ( TT_GEN_UNI_SUBOBJ ) , NULL , "%s NSAP TNA: " , c ) ;
 nsap_len = tvb_get_guint8 ( tvb , offset2 + l + 4 ) ;
 proto_tree_add_uint_format_value ( rsvp_gen_uni_subtree , hf_rsvp_class , tvb , offset2 + l + 2 , 1 , j , "%d (%s)" , j , c ) ;
 proto_tree_add_uint_format_value ( rsvp_gen_uni_subtree , hf_rsvp_type , tvb , offset2 + l + 3 , 1 , k , "3 (NSAP)" ) ;
 proto_tree_add_uint ( rsvp_gen_uni_subtree , hf_rsvp_class_length , tvb , offset2 + l , 2 , sobj_len ) ;
 proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_nsap_length , tvb , offset2 + l + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_string ( rsvp_gen_uni_subtree , hf_rsvp_nsap_address , tvb , offset2 + l + 5 , sobj_len - 4 , print_nsap_net ( tvb , offset2 + l + 5 , nsap_len ) ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "%s NSAP TNA: %s" , c , print_nsap_net ( tvb , offset2 + l + 5 , nsap_len ) ) ;
 }
 break ;
 default : rsvp_gen_uni_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset2 + l , tvb_get_ntohs ( tvb , offset2 + l ) , TREE ( TT_GEN_UNI_SUBOBJ ) , NULL , "%s UNKNOWN TNA" , c ) ;
 proto_tree_add_uint_format_value ( rsvp_gen_uni_subtree , hf_rsvp_class , tvb , offset2 + l + 2 , 1 , j , "%d (%s)" , j , c ) ;
 proto_tree_add_uint_format_value ( rsvp_gen_uni_subtree , hf_rsvp_type , tvb , offset2 + l + 3 , 1 , k , "%d (UNKNOWN)" , k ) ;
 proto_tree_add_uint ( rsvp_gen_uni_subtree , hf_rsvp_class_length , tvb , offset2 + l , 2 , sobj_len ) ;
 proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_gen_uni_data , tvb , offset2 + l + 4 , sobj_len - 4 , ENC_NA ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "%s UNKNOWN" , c ) ;
 }
 break ;
 }
 break ;
 case 3 : k = tvb_get_guint8 ( tvb , offset2 + l + 3 ) ;
 switch ( k ) {
 default : case 1 : rsvp_gen_uni_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset2 + l , tvb_get_ntohs ( tvb , offset2 + l ) , TREE ( TT_GEN_UNI_SUBOBJ ) , & ti2 , "Diversity Subobject" ) ;
 proto_tree_add_uint_format_value ( rsvp_gen_uni_subtree , hf_rsvp_class , tvb , offset2 + l + 2 , 1 , j , "%d (Diversity)" , j ) ;
 proto_tree_add_uint ( rsvp_gen_uni_subtree , hf_rsvp_type , tvb , offset2 + l + 3 , 1 , k ) ;
 proto_tree_add_uint ( rsvp_gen_uni_subtree , hf_rsvp_class_length , tvb , offset2 + l , 2 , sobj_len ) ;
 proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_class_diversity , tvb , offset2 + l + 4 , 1 , ENC_NA ) ;
 s_len = tvb_get_ntohs ( tvb , offset2 + l + 8 ) ;
 s_class = tvb_get_guint8 ( tvb , offset2 + l + 10 ) ;
 s_type = tvb_get_guint8 ( tvb , offset2 + l + 11 ) ;
 rsvp_session_subtree = proto_tree_add_subtree ( rsvp_gen_uni_subtree , tvb , offset2 + l + 8 , s_len , TREE ( rsvp_class_to_tree_type ( s_class ) ) , & ti2 , "Session" ) ;
 len_item = proto_tree_add_uint ( rsvp_session_subtree , hf_rsvp_length , tvb , offset2 + l + 8 , 2 , s_len ) ;
 if ( s_len < 4 ) {
 expert_add_info_format ( pinfo , len_item , & ei_rsvp_invalid_length , "Length: %u (bogus, must be >= 4)" , s_len ) ;
 break ;
 }
 proto_tree_add_uint ( rsvp_session_subtree , hf_rsvp_filter [ RSVPF_OBJECT ] , tvb , offset2 + 8 + l + 10 , 1 , s_class ) ;
 dissect_rsvp_session ( ti2 , rsvp_session_subtree , tvb , offset2 + l + 8 , s_len , s_class , s_type , rsvph ) ;
 offset3 = offset2 + s_len ;
 s_len = tvb_get_ntohs ( tvb , offset3 + l + 8 ) ;
 s_class = tvb_get_guint8 ( tvb , offset3 + l + 10 ) ;
 s_type = tvb_get_guint8 ( tvb , offset3 + l + 11 ) ;
 rsvp_template_subtree = proto_tree_add_subtree ( rsvp_gen_uni_subtree , tvb , offset3 + l + 8 , s_len , TREE ( rsvp_class_to_tree_type ( s_class ) ) , & ti2 , "Template" ) ;
 proto_tree_add_uint ( rsvp_template_subtree , hf_rsvp_length , tvb , offset3 + l + 8 , 2 , s_len ) ;
 if ( s_len < 4 ) {
 expert_add_info_format ( pinfo , len_item , & ei_rsvp_invalid_length , "Length: %u (bogus, must be >= 4)" , s_len ) ;
 break ;
 }
 proto_tree_add_uint ( rsvp_template_subtree , hf_rsvp_filter [ RSVPF_OBJECT ] , tvb , offset3 + 8 + l + 10 , 1 , s_class ) ;
 dissect_rsvp_template_filter ( ti2 , rsvp_template_subtree , tvb , offset3 + l + 8 , s_len , s_class , s_type , rsvph ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "Diversity" ) ;
 }
 break ;
 }
 break ;
 case 4 : k = tvb_get_guint8 ( tvb , offset2 + l + 3 ) ;
 if ( k == 1 ) rsvp_gen_uni_subtree = proto_tree_add_subtree ( rsvp_object_tree , tvb , offset2 + l , sobj_len , TREE ( TT_GEN_UNI_SUBOBJ ) , & ti2 , "Egress Label Subobject" ) ;
 else if ( k == 2 ) rsvp_gen_uni_subtree = proto_tree_add_subtree ( rsvp_object_tree , tvb , offset2 + l , sobj_len , TREE ( TT_GEN_UNI_SUBOBJ ) , & ti2 , "SPC Label Subobject" ) ;
 else rsvp_gen_uni_subtree = proto_tree_add_subtree ( rsvp_object_tree , tvb , offset2 + l , sobj_len , TREE ( TT_GEN_UNI_SUBOBJ ) , & ti2 , "Unknown Label Subobject" ) ;
 proto_tree_add_uint_format_value ( rsvp_gen_uni_subtree , hf_rsvp_class , tvb , offset2 + l + 2 , 1 , j , "%d (Egress/SPC Label)" , j ) ;
 proto_tree_add_uint ( rsvp_gen_uni_subtree , hf_rsvp_type , tvb , offset2 + l + 3 , 1 , k ) ;
 proto_tree_add_uint ( rsvp_gen_uni_subtree , hf_rsvp_class_length , tvb , offset2 + l , 2 , sobj_len ) ;
 proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_gen_uni_direction , tvb , offset + l + 2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_egress_label_type , tvb , offset2 + l + 7 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_gen_uni_logical_port_id , tvb , offset2 + l + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti2 , ": %s, Label type %d, Port ID %d, Label " , tvb_get_guint8 ( tvb , offset2 + l + 4 ) & 0x80 ? "Upstream" : "Downstream" , tvb_get_guint8 ( tvb , offset2 + l + 7 ) , tvb_get_ntohl ( tvb , offset2 + l + 8 ) ) ;
 for ( j = 12 ;
 j < sobj_len ;
 j += 4 ) {
 proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_egress_label , tvb , offset2 + l + j , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti2 , "%u " , tvb_get_ntohl ( tvb , offset2 + l + j ) ) ;
 }
 if ( i < 4 ) {
 if ( k == 1 ) proto_item_append_text ( ti , "Egress Label" ) ;
 else if ( k == 2 ) proto_item_append_text ( ti , "SPC Label" ) ;
 }
 break ;
 case 5 : k = tvb_get_guint8 ( tvb , offset2 + l + 3 ) ;
 switch ( k ) {
 default : case 1 : rsvp_gen_uni_subtree = proto_tree_add_subtree ( rsvp_object_tree , tvb , offset2 + l , sobj_len , TREE ( TT_GEN_UNI_SUBOBJ ) , & ti2 , "Service Level Subobject" ) ;
 proto_tree_add_uint_format_value ( rsvp_gen_uni_subtree , hf_rsvp_class , tvb , offset2 + l + 2 , 1 , j , "%d (Service Level)" , j ) ;
 proto_tree_add_uint ( rsvp_gen_uni_subtree , hf_rsvp_type , tvb , offset2 + l + 3 , 1 , k ) ;
 proto_tree_add_uint ( rsvp_gen_uni_subtree , hf_rsvp_class_length , tvb , offset2 + l , 2 , sobj_len ) ;
 proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_gen_uni_service_level , tvb , offset2 + l + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti2 , ": %u" , tvb_get_guint8 ( tvb , offset2 + l + 4 ) ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "Service Level %d" , tvb_get_guint8 ( tvb , offset2 + l + 4 ) ) ;
 }
 break ;
 }
 break ;
 default : rsvp_gen_uni_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset2 + l , sobj_len , TREE ( TT_GEN_UNI_SUBOBJ ) , NULL , "Unknown subobject: %u" , j ) ;
 proto_tree_add_uint_format_value ( rsvp_gen_uni_subtree , hf_rsvp_type , tvb , offset2 + l , 1 , j , "%u (Unknown)" , j ) ;
 proto_tree_add_item ( rsvp_gen_uni_subtree , hf_rsvp_class_length , tvb , offset2 + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 break ;
 }
 if ( tvb_get_guint8 ( tvb , offset2 + l + 1 ) < 1 ) {
 proto_tree_add_expert_format ( rsvp_gen_uni_subtree , pinfo , & ei_rsvp_invalid_length , tvb , offset2 + l + 1 , 1 , "Invalid length: %u" , tvb_get_guint8 ( tvb , offset2 + l + 1 ) ) ;
 return ;
 }
 l += tvb_get_guint8 ( tvb , offset2 + l + 1 ) ;
 if ( l < mylen ) {
 if ( i < 4 ) proto_item_append_text ( ti , ", " ) ;
 else if ( i == 4 ) proto_item_append_text ( ti , "..." ) ;
 }
 }
 break ;
 }
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_gen_uni_data , tvb , offset2 , mylen , ENC_NA ) ;
 break ;
 }
 }