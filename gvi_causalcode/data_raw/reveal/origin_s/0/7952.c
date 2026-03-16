void proto_register_bta2dp_content_protection_header_scms_t ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_bta2dp_l_bit , {
 "L-bit" , "bta2dp.content_protection_header.scms_t.l_bit" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_bta2dp_cp_bit , {
 "Cp-bit" , "bta2dp.content_protection_header.scms_t.cp_bit" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_bta2dp_reserved , {
 "Reserved" , "bta2dp.content_protection_header.scms_t.reserved" , FT_BOOLEAN , 8 , NULL , 0xFC , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ] = {
 & ett_bta2dp_cph_scms_t }
 ;
 proto_bta2dp_cph_scms_t = proto_register_protocol ( "Bluetooth A2DP Content Protection Header SCMS-T" , "BT A2DP Content Protection Header SCMS-T" , "bta2dp_content_protection_header_scms_t" ) ;
 proto_register_field_array ( proto_bta2dp_cph_scms_t , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( "bta2dp_content_protection_header_scms_t" , dissect_a2dp_cp_scms_t , proto_bta2dp_cph_scms_t ) ;
 }