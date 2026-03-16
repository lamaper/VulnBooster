static void dissect_cip_safety_data ( proto_tree * tree , proto_item * item , tvbuff_t * tvb , int item_length , packet_info * pinfo ) {
 int base_length , io_data_size ;
 gboolean multicast = ( ( ( pntoh32 ( pinfo -> dst . data ) ) & 0xf0000000 ) == 0xe0000000 ) ;
 gboolean server_dir = FALSE ;
 enum enip_connid_type conn_type = ECIDT_UNKNOWN ;
 enum cip_safety_format_type format = CIP_SAFETY_BASE_FORMAT ;
 cip_safety_info_t * safety_info = ( cip_safety_info_t * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_cipsafety , 0 ) ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "CIP Safety" ) ;
 if ( safety_info != NULL ) {
 conn_type = safety_info -> conn_type ;
 format = safety_info -> format ;
 server_dir = safety_info -> server_dir ;
 }
 base_length = multicast ? 12 : 6 ;
 if ( item_length <= base_length ) {
 expert_add_info ( pinfo , item , & ei_mal_io ) ;
 return ;
 }
 if ( ( ( conn_type == ECIDT_O2T ) && ( server_dir == FALSE ) ) || ( ( conn_type == ECIDT_T2O ) && ( server_dir == TRUE ) ) ) {
 dissect_ack_byte ( tree , tvb , 0 , pinfo ) ;
 proto_tree_add_item ( tree , hf_cipsafety_consumer_time_value , tvb , 1 , 2 , ENC_LITTLE_ENDIAN ) ;
 switch ( format ) {
 case CIP_SAFETY_BASE_FORMAT : proto_tree_add_item ( tree , hf_cipsafety_ack_byte2 , tvb , 3 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s3 , tvb , 4 , 2 , ENC_LITTLE_ENDIAN ) ;
 break ;
 case CIP_SAFETY_EXTENDED_FORMAT : proto_tree_add_item ( tree , hf_cipsafety_crc_s5_0 , tvb , 3 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_1 , tvb , 4 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_2 , tvb , 5 , 1 , ENC_LITTLE_ENDIAN ) ;
 break ;
 }
 }
 else if ( ( ( conn_type == ECIDT_O2T ) && ( server_dir == TRUE ) ) || ( ( conn_type == ECIDT_T2O ) && ( server_dir == FALSE ) ) ) {
 switch ( format ) {
 case CIP_SAFETY_BASE_FORMAT : if ( item_length - base_length <= 2 ) {
 proto_tree_add_item ( tree , hf_cipsafety_data , tvb , 0 , item_length - base_length , ENC_NA ) ;
 dissect_mode_byte ( tree , tvb , item_length - base_length , pinfo ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s1 , tvb , item_length - base_length + 1 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s2 , tvb , item_length - base_length + 2 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_timestamp , tvb , item_length - base_length + 3 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s1 , tvb , item_length - base_length + 5 , 1 , ENC_LITTLE_ENDIAN ) ;
 if ( multicast ) {
 dissect_mcast_byte ( tree , tvb , item_length - 6 , pinfo ) ;
 proto_tree_add_item ( tree , hf_cipsafety_time_correction , tvb , item_length - 5 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_mcast_byte2 , tvb , item_length - 3 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s3 , tvb , item_length - 2 , 2 , ENC_LITTLE_ENDIAN ) ;
 }
 }
 else {
 if ( item_length % 2 == 1 ) {
 expert_add_info ( pinfo , item , & ei_mal_io ) ;
 return ;
 }
 io_data_size = multicast ? ( ( item_length - 14 ) / 2 ) : ( ( item_length - 8 ) / 2 ) ;
 proto_tree_add_item ( tree , hf_cipsafety_data , tvb , 0 , io_data_size , ENC_NA ) ;
 dissect_mode_byte ( tree , tvb , io_data_size , pinfo ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s3 , tvb , io_data_size + 1 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_complement_data , tvb , io_data_size + 3 , io_data_size , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s3 , tvb , ( io_data_size * 2 ) + 3 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_timestamp , tvb , ( io_data_size * 2 ) + 5 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s1 , tvb , ( io_data_size * 2 ) + 7 , 1 , ENC_LITTLE_ENDIAN ) ;
 if ( multicast ) {
 dissect_mcast_byte ( tree , tvb , ( io_data_size * 2 ) + 5 , pinfo ) ;
 proto_tree_add_item ( tree , hf_cipsafety_time_correction , tvb , ( io_data_size * 2 ) + 6 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_mcast_byte2 , tvb , ( io_data_size * 2 ) + 8 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s3 , tvb , ( io_data_size * 2 ) + 9 , 2 , ENC_LITTLE_ENDIAN ) ;
 }
 }
 break ;
 case CIP_SAFETY_EXTENDED_FORMAT : if ( item_length - base_length <= 2 ) {
 proto_tree_add_item ( tree , hf_cipsafety_data , tvb , 0 , item_length - base_length , ENC_NA ) ;
 dissect_mode_byte ( tree , tvb , item_length - base_length , pinfo ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_0 , tvb , item_length - base_length + 1 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_1 , tvb , item_length - base_length + 2 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_timestamp , tvb , item_length - base_length + 3 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_2 , tvb , item_length - base_length + 5 , 1 , ENC_LITTLE_ENDIAN ) ;
 if ( multicast ) {
 dissect_mcast_byte ( tree , tvb , item_length - 6 , pinfo ) ;
 proto_tree_add_item ( tree , hf_cipsafety_time_correction , tvb , item_length - 5 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_0 , tvb , item_length - 3 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_1 , tvb , item_length - 2 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_2 , tvb , item_length - 1 , 1 , ENC_LITTLE_ENDIAN ) ;
 }
 }
 else {
 if ( item_length % 2 == 1 ) {
 expert_add_info ( pinfo , item , & ei_mal_io ) ;
 return ;
 }
 io_data_size = multicast ? ( ( item_length - 14 ) / 2 ) : ( ( item_length - 8 ) / 2 ) ;
 proto_tree_add_item ( tree , hf_cipsafety_data , tvb , 0 , io_data_size , ENC_NA ) ;
 dissect_mode_byte ( tree , tvb , io_data_size , pinfo ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s3 , tvb , io_data_size + 1 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_complement_data , tvb , io_data_size + 3 , io_data_size , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_0 , tvb , ( io_data_size * 2 ) + 3 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_1 , tvb , ( io_data_size * 2 ) + 4 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_timestamp , tvb , ( io_data_size * 2 ) + 5 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_2 , tvb , ( io_data_size * 2 ) + 7 , 1 , ENC_LITTLE_ENDIAN ) ;
 if ( multicast ) {
 dissect_mcast_byte ( tree , tvb , ( io_data_size * 2 ) + 8 , pinfo ) ;
 proto_tree_add_item ( tree , hf_cipsafety_time_correction , tvb , ( io_data_size * 2 ) + 9 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_0 , tvb , ( io_data_size * 2 ) + 11 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_1 , tvb , ( io_data_size * 2 ) + 12 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_cipsafety_crc_s5_2 , tvb , ( io_data_size * 2 ) + 13 , 1 , ENC_LITTLE_ENDIAN ) ;
 }
 }
 break ;
 }
 }
 else {
 proto_tree_add_item ( tree , hf_cipsafety_data , tvb , 0 , item_length , ENC_NA ) ;
 }
 }