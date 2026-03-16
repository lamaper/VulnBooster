static void ss_interpretation ( tvbuff_t * tvb , proto_tree * tree , guint8 ss , guint number_of_mac_is_sdus , guint offset ) {
 switch ( ss ) {
 case 0 : if ( number_of_mac_is_sdus > 1 ) {
 proto_tree_add_uint_format_value ( tree , hf_mac_edch_type2_ss_interpretation , tvb , offset , 1 , ss , "The first MAC-is SDU of the MAC-is PDU is a complete MAC-d PDU or MAC-c PDU. The last MAC-is SDU of the MAC-is PDU is a complete MAC-d PDU or MAC-c PDU." ) ;
 }
 else {
 proto_tree_add_uint_format_value ( tree , hf_mac_edch_type2_ss_interpretation , tvb , offset , 1 , ss , "The MAC-is SDU of the MAC-is PDU is a complete MAC-d PDU or MAC-c PDU." ) ;
 }
 break ;
 case 1 : if ( number_of_mac_is_sdus > 1 ) {
 proto_tree_add_uint_format_value ( tree , hf_mac_edch_type2_ss_interpretation , tvb , offset , 1 , ss , "The last MAC-is SDU of the MAC-is PDU is a complete MAC-d PDU or MAC-c PDU. The first MAC-is SDU of the MAC-is PDU is the last segment of a MAC-d PDU or MAC-c PDU." ) ;
 }
 else {
 proto_tree_add_uint_format_value ( tree , hf_mac_edch_type2_ss_interpretation , tvb , offset , 1 , ss , "The MAC-is SDU of the MAC-is PDU is the last segment of a MAC-d PDU or MAC-c PDU." ) ;
 }
 break ;
 case 2 : if ( number_of_mac_is_sdus > 1 ) {
 proto_tree_add_uint_format_value ( tree , hf_mac_edch_type2_ss_interpretation , tvb , offset , 1 , ss , "The first MAC-is SDU of the MAC-is PDU is a complete MAC-d PDU or MAC-c PDU. The last MAC-is SDU of the MAC-is PDU is the first segment of a MAC-d PDU or MAC-c PDU." ) ;
 }
 else {
 proto_tree_add_uint_format_value ( tree , hf_mac_edch_type2_ss_interpretation , tvb , offset , 1 , ss , "The MAC-is SDU of the MAC-is PDU is the first segment of a MAC-d PDU or MAC-c PDU." ) ;
 }
 break ;
 case 3 : if ( number_of_mac_is_sdus > 1 ) {
 proto_tree_add_uint_format_value ( tree , hf_mac_edch_type2_ss_interpretation , tvb , offset , 1 , ss , "The first MAC-is SDU of the MAC-is PDU is the last segment of a MAC-d PDU or MAC-c PDU and the last MAC-is SDU of MAC-is PDU is the first segment of a MAC-d PDU or MAC-c PDU." ) ;
 }
 else {
 proto_tree_add_uint_format_value ( tree , hf_mac_edch_type2_ss_interpretation , tvb , offset , 1 , ss , "The MAC-is SDU is a middle segment of a MAC-d PDU or MAC-c PDU." ) ;
 }
 break ;
 }
 }