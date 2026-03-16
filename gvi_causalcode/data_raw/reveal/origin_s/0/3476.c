static void dissect_rsvp_ero_rro_subobjects ( proto_tree * ti , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class ) {
 int i , j , k , l , flags ;
 proto_tree * ti2 = NULL , * rsvp_ro_subtree , * rsvp_rro_flags_subtree ;
 int tree_type ;
 switch ( rsvp_class ) {
 case RSVP_CLASS_EXPLICIT_ROUTE : tree_type = TREE ( TT_EXPLICIT_ROUTE_SUBOBJ ) ;
 break ;
 case RSVP_CLASS_RECORD_ROUTE : tree_type = TREE ( TT_RECORD_ROUTE_SUBOBJ ) ;
 break ;
 default : return ;
 }
 for ( i = 1 , l = 0 ;
 l < obj_length - 4 ;
 i ++ ) {
 j = tvb_get_guint8 ( tvb , offset + l ) & 0x7f ;
 switch ( j ) {
 case 1 : k = tvb_get_guint8 ( tvb , offset + l ) & 0x80 ;
 rsvp_ro_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + l , 8 , tree_type , & ti2 , "IPv4 Subobject - %s%s" , tvb_ip_to_str ( tvb , offset + l + 2 ) , rsvp_class == RSVP_CLASS_EXPLICIT_ROUTE ? ( k ? ", Loose" : ", Strict" ) : "" ) ;
 if ( rsvp_class == RSVP_CLASS_EXPLICIT_ROUTE ) proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_loose_hop , tvb , offset + l , 1 , ENC_NA ) ;
 proto_tree_add_uint_format_value ( rsvp_ro_subtree , hf_rsvp_type , tvb , offset + l , 1 , j , "1 (IPv4)" ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_length , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_ipv4_hop , tvb , offset + l + 2 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_prefix_length , tvb , offset + l + 6 , 1 , ENC_BIG_ENDIAN ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "IPv4 %s%s" , tvb_ip_to_str ( tvb , offset + l + 2 ) , k ? " [L]" : "" ) ;
 }
 if ( rsvp_class == RSVP_CLASS_RECORD_ROUTE ) {
 flags = tvb_get_guint8 ( tvb , offset + l + 7 ) ;
 if ( flags & 0x20 ) {
 proto_item_append_text ( ti , " (Node-id)" ) ;
 proto_item_append_text ( ti2 , " (Node-id)" ) ;
 }
 if ( flags & 0x01 ) proto_item_append_text ( ti2 , ", Local Protection Available" ) ;
 if ( flags & 0x02 ) proto_item_append_text ( ti2 , ", Local Protection In Use" ) ;
 if ( flags & 0x04 ) proto_item_append_text ( ti2 , ", Backup BW Avail" ) ;
 if ( flags & 0x08 ) proto_item_append_text ( ti2 , ", Backup is Next-Next-Hop" ) ;
 ti2 = proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_flags , tvb , offset + l + 7 , 1 , ENC_BIG_ENDIAN ) ;
 rsvp_rro_flags_subtree = proto_item_add_subtree ( ti2 , TREE ( TT_RECORD_ROUTE_SUBOBJ_FLAGS ) ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_local_avail , tvb , offset + l + 7 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_local_in_use , tvb , offset + l + 7 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_bandwidth , tvb , offset + l + 7 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_node , tvb , offset + l + 7 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_node_address , tvb , offset + l + 7 , 1 , ENC_BIG_ENDIAN ) ;
 }
 break ;
 case 2 : rsvp_ro_subtree = proto_tree_add_subtree ( rsvp_object_tree , tvb , offset + l , 20 , tree_type , & ti2 , "IPv6 Subobject" ) ;
 k = tvb_get_guint8 ( tvb , offset + l ) & 0x80 ;
 if ( rsvp_class == RSVP_CLASS_EXPLICIT_ROUTE ) proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_loose_hop , tvb , offset + l , 1 , ENC_NA ) ;
 proto_tree_add_uint_format_value ( rsvp_ro_subtree , hf_rsvp_type , tvb , offset + l , 1 , j , "2 (IPv6)" ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_length , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_ipv6_hop , tvb , offset + l + 2 , 16 , ENC_NA ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_prefix_length , tvb , offset + l + 18 , 1 , ENC_BIG_ENDIAN ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "IPv6 [...]%s" , k ? " [L]" : "" ) ;
 }
 if ( rsvp_class == RSVP_CLASS_RECORD_ROUTE ) {
 flags = tvb_get_guint8 ( tvb , offset + l + 19 ) ;
 if ( flags & 0x20 ) {
 proto_item_append_text ( ti , " (Node-id)" ) ;
 proto_item_append_text ( ti2 , " (Node-id)" ) ;
 }
 if ( flags & 0x01 ) proto_item_append_text ( ti2 , ", Local Protection Available" ) ;
 if ( flags & 0x02 ) proto_item_append_text ( ti2 , ", Local Protection In Use" ) ;
 if ( flags & 0x04 ) proto_item_append_text ( ti2 , ", Backup BW Avail" ) ;
 if ( flags & 0x08 ) proto_item_append_text ( ti2 , ", Backup is Next-Next-Hop" ) ;
 ti2 = proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_flags , tvb , offset + l + 19 , 1 , ENC_BIG_ENDIAN ) ;
 rsvp_rro_flags_subtree = proto_item_add_subtree ( ti2 , TREE ( TT_RECORD_ROUTE_SUBOBJ_FLAGS ) ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_local_avail , tvb , offset + l + 19 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_local_in_use , tvb , offset + l + 19 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_backup_tunnel_bandwidth , tvb , offset + l + 19 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_backup_tunnel_hop , tvb , offset + l + 19 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_node_address , tvb , offset + l + 19 , 1 , ENC_BIG_ENDIAN ) ;
 }
 break ;
 case 3 : k = tvb_get_guint8 ( tvb , offset + l ) & 0x80 ;
 rsvp_ro_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + l , 8 , tree_type , & ti2 , "Label Subobject - %d, %s" , tvb_get_ntohl ( tvb , offset + l + 4 ) , rsvp_class == RSVP_CLASS_EXPLICIT_ROUTE ? ( k ? "Loose" : "Strict" ) : "" ) ;
 if ( rsvp_class == RSVP_CLASS_EXPLICIT_ROUTE ) proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_loose_hop , tvb , offset + l , 1 , ENC_NA ) ;
 proto_tree_add_uint_format_value ( rsvp_ro_subtree , hf_rsvp_type , tvb , offset + l , 1 , j , "3 (Label)" ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_length , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 if ( rsvp_class == RSVP_CLASS_RECORD_ROUTE ) {
 flags = tvb_get_guint8 ( tvb , offset + l + 2 ) ;
 if ( flags & 0x01 ) proto_item_append_text ( ti2 , "The label will be understood if received on any interface" ) ;
 ti2 = proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_flags , tvb , offset + l + 2 , 1 , ENC_BIG_ENDIAN ) ;
 rsvp_rro_flags_subtree = proto_item_add_subtree ( ti2 , TREE ( TT_RECORD_ROUTE_SUBOBJ_FLAGS ) ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_global_label , tvb , offset + l + 2 , 1 , ENC_BIG_ENDIAN ) ;
 }
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ctype , tvb , offset + l + 3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_label , tvb , offset + l + 4 , 4 , ENC_BIG_ENDIAN ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "Label %d%s" , tvb_get_ntohl ( tvb , offset + l + 4 ) , k ? " [L]" : "" ) ;
 }
 break ;
 case 4 : k = tvb_get_guint8 ( tvb , offset + l ) & 0x80 ;
 rsvp_ro_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + l , 8 , tree_type , & ti2 , "Unnumbered Interface-ID - %s, %d, %s" , tvb_ip_to_str ( tvb , offset + l + 4 ) , tvb_get_ntohl ( tvb , offset + l + 8 ) , rsvp_class == RSVP_CLASS_EXPLICIT_ROUTE ? ( k ? "Loose" : "Strict" ) : "" ) ;
 if ( rsvp_class == RSVP_CLASS_EXPLICIT_ROUTE ) proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_loose_hop , tvb , offset + l , 1 , ENC_NA ) ;
 proto_tree_add_uint_format_value ( rsvp_ro_subtree , hf_rsvp_type , tvb , offset + l , 1 , j , "4 (Unnumbered Interface-ID)" ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_length , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 if ( rsvp_class == RSVP_CLASS_RECORD_ROUTE ) {
 flags = tvb_get_guint8 ( tvb , offset + l + 2 ) ;
 if ( flags & 0x01 ) proto_item_append_text ( ti2 , ", Local Protection Available" ) ;
 if ( flags & 0x02 ) proto_item_append_text ( ti2 , ", Local Protection In Use" ) ;
 ti2 = proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_flags , tvb , offset + l + 2 , 1 , ENC_BIG_ENDIAN ) ;
 rsvp_rro_flags_subtree = proto_item_add_subtree ( ti2 , TREE ( TT_RECORD_ROUTE_SUBOBJ_FLAGS ) ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_local_avail , tvb , offset + l + 2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_rro_flags_subtree , hf_rsvp_rro_flags_local_in_use , tvb , offset + l + 2 , 1 , ENC_BIG_ENDIAN ) ;
 }
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_router_id , tvb , offset + l + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_interface_id , tvb , offset + l + 8 , 4 , ENC_BIG_ENDIAN ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "Unnum %s/%d%s" , tvb_ip_to_str ( tvb , offset + l + 4 ) , tvb_get_ntohl ( tvb , offset + l + 8 ) , k ? " [L]" : "" ) ;
 }
 break ;
 case 32 : if ( rsvp_class == RSVP_CLASS_RECORD_ROUTE ) goto defaultsub ;
 k = tvb_get_ntohs ( tvb , offset + l + 2 ) ;
 rsvp_ro_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + l , 4 , tree_type , & ti2 , "Autonomous System %u" , k ) ;
 proto_tree_add_uint_format_value ( rsvp_ro_subtree , hf_rsvp_type , tvb , offset + l , 1 , j , "32 (Autonomous System Number)" ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_length , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_autonomous_system , tvb , offset + l + 2 , 2 , ENC_BIG_ENDIAN ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "AS %d" , tvb_get_ntohs ( tvb , offset + l + 2 ) ) ;
 }
 break ;
 case 64 : if ( rsvp_class == RSVP_CLASS_RECORD_ROUTE ) goto defaultsub ;
 k = tvb_get_ntohs ( tvb , offset + l + 2 ) ;
 rsvp_ro_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + l , 8 , tree_type , & ti2 , "Path Key subobject - %s, %u" , tvb_ip_to_str ( tvb , offset + l + 4 ) , k ) ;
 proto_tree_add_uint_format_value ( rsvp_ro_subtree , hf_rsvp_type , tvb , offset + l , 1 , j , "64 (Path Key with IPv4 PCE-ID)" ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_length , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_path_key , tvb , offset + l + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_pce_id_ipv4 , tvb , offset + l + 4 , 4 , ENC_BIG_ENDIAN ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "Path Key %d" , k ) ;
 }
 break ;
 case 65 : if ( rsvp_class == RSVP_CLASS_RECORD_ROUTE ) goto defaultsub ;
 k = tvb_get_ntohs ( tvb , offset + l + 2 ) ;
 rsvp_ro_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + l , 8 , tree_type , & ti2 , "Path Key subobject - %s, %u" , tvb_ip6_to_str ( tvb , offset + l + 4 ) , k ) ;
 proto_tree_add_uint_format_value ( rsvp_ro_subtree , hf_rsvp_type , tvb , offset + l , 1 , j , "65 (Path Key with IPv6 PCE-ID)" ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_length , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_path_key , tvb , offset + l + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_pce_id_ipv6 , tvb , offset + l + 4 , 16 , ENC_NA ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "Path Key %d" , k ) ;
 }
 break ;
 case 124 : case 125 : case 126 : case 127 : if ( rsvp_class == RSVP_CLASS_RECORD_ROUTE ) goto defaultsub ;
 else goto privatesub ;
 break ;
 case 252 : case 253 : case 254 : case 255 : if ( rsvp_class == RSVP_CLASS_EXPLICIT_ROUTE ) goto defaultsub ;
 else goto privatesub ;
 break ;
 privatesub : {
 guint8 private_so_len = tvb_get_guint8 ( tvb , offset + l + 1 ) ;
 rsvp_ro_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + l , tvb_get_guint8 ( tvb , offset + l + 1 ) , tree_type , & ti2 , "Private Subobject: %d" , j ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_loose_hop , tvb , offset + l , 1 , ENC_NA ) ;
 proto_tree_add_uint_format_value ( rsvp_ro_subtree , hf_rsvp_type , tvb , offset + l , 1 , j , "%u (Private)" , j ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_private_length , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_filter [ RSVPF_ENT_CODE ] , tvb , offset + l + 4 , 4 , ENC_BIG_ENDIAN ) ;
 if ( private_so_len > 8 ) {
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_private_data , tvb , offset + l + 8 , private_so_len - 8 , ENC_NA ) ;
 }
 }
 break ;
 default : defaultsub : rsvp_ro_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + l , tvb_get_guint8 ( tvb , offset + l + 1 ) , tree_type , & ti2 , "Unknown subobject: %d" , j ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_loose_hop , tvb , offset + l , 1 , ENC_NA ) ;
 proto_tree_add_uint_format_value ( rsvp_ro_subtree , hf_rsvp_type , tvb , offset + l , 1 , j , "%u (Unknown)" , j ) ;
 proto_tree_add_item ( rsvp_ro_subtree , hf_rsvp_ero_rro_subobjects_length , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 break ;
 }
 if ( tvb_get_guint8 ( tvb , offset + l + 1 ) < 1 ) {
 proto_tree_add_expert_format ( rsvp_ro_subtree , pinfo , & ei_rsvp_invalid_length , tvb , offset + l + 1 , 1 , "Invalid length: %u" , tvb_get_guint8 ( tvb , offset + l + 1 ) ) ;
 return ;
 }
 l += tvb_get_guint8 ( tvb , offset + l + 1 ) ;
 if ( l < obj_length - 4 ) {
 if ( i < 4 ) proto_item_append_text ( ti , ", " ) ;
 else if ( i == 4 ) proto_item_append_text ( ti , "..." ) ;
 }
 }
 }