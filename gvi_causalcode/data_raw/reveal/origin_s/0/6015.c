void proto_register_btvdp_content_protection_header_scms_t ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_btvdp_l_bit , {
 "L-bit" , "btvdp.content_protection_header.scms_t.l_bit" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btvdp_cp_bit , {
 "Cp-bit" , "btvdp.content_protection_header.scms_t.cp_bit" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btvdp_reserved , {
 "Reserved" , "btvdp.content_protection_header.scms_t.reserved" , FT_BOOLEAN , 8 , NULL , 0xFC , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ] = {
 & ett_btvdp_cph_scms_t }
 ;
 proto_btvdp_cph_scms_t = proto_register_protocol ( "Bluetooth VDP Content Protection Header SCMS-T" , "BT VDP Content Protection Header SCMS-T" , "btvdp_content_protection_header_scms_t" ) ;
 proto_register_field_array ( proto_btvdp_cph_scms_t , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( "btvdp_content_protection_header_scms_t" , dissect_vdp_cp_scms_t , proto_btvdp_cph_scms_t ) ;
 }