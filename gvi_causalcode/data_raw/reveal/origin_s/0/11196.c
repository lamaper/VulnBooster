void proto_register_mpa ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_mpa_req , {
 "Request frame header" , "iwarp_mpa.req" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_rep , {
 "Reply frame header" , "iwarp_mpa.rep" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_fpdu , {
 "FPDU" , "iwarp_mpa.fpdu" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_marker , {
 "Markers" , "iwarp_mpa.markers" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_key_req , {
 "ID Req frame" , "iwarp_mpa.key.req" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_key_rep , {
 "ID Rep frame" , "iwarp_mpa.key.rep" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_flag_m , {
 "Marker flag" , "iwarp_mpa.marker_flag" , FT_BOOLEAN , 8 , NULL , MPA_MARKER_FLAG , NULL , HFILL }
 }
 , {
 & hf_mpa_flag_c , {
 "CRC flag" , "iwarp_mpa.crc_flag" , FT_BOOLEAN , 8 , NULL , MPA_CRC_FLAG , NULL , HFILL }
 }
 , {
 & hf_mpa_flag_r , {
 "Connection rejected flag" , "iwarp_mpa.rej_flag" , FT_BOOLEAN , 8 , NULL , MPA_REJECT_FLAG , NULL , HFILL }
 }
 , {
 & hf_mpa_flag_res , {
 "Reserved" , "iwarp_mpa.res" , FT_UINT8 , BASE_HEX , NULL , MPA_RESERVED_FLAG , NULL , HFILL }
 }
 , {
 & hf_mpa_rev , {
 "Revision" , "iwarp_mpa.rev" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_pd_length , {
 "Private data length" , "iwarp_mpa.pdlength" , FT_UINT16 , BASE_DEC | BASE_UNIT_STRING , & units_byte_bytes , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_private_data , {
 "Private data" , "iwarp_mpa.privatedata" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_ulpdu_length , {
 "ULPDU length" , "iwarp_mpa.ulpdulength" , FT_UINT16 , BASE_DEC | BASE_UNIT_STRING , & units_byte_bytes , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_pad , {
 "Padding" , "iwarp_mpa.pad" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_crc , {
 "CRC" , "iwarp_mpa.crc" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_crc_check , {
 "CRC check" , "iwarp_mpa.crc_check" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_mpa_marker_res , {
 "Reserved" , "iwarp_mpa.marker_res" , FT_UINT16 , BASE_HEX , NULL , 0x0 , "Marker: Reserved" , HFILL }
 }
 , {
 & hf_mpa_marker_fpduptr , {
 "FPDU back pointer" , "iwarp_mpa.marker_fpduptr" , FT_UINT16 , BASE_DEC | BASE_UNIT_STRING , & units_byte_bytes , 0x0 , "Marker: FPDU Pointer" , HFILL }
 }
 }
 ;
 static gint * ett [ ] = {
 & ett_mpa , & ett_mpa_req , & ett_mpa_rep , & ett_mpa_fpdu , & ett_mpa_marker }
 ;
 static ei_register_info ei [ ] = {
 {
 & ei_mpa_res_field_not_set0 , {
 "iwarp_mpa.res.not_set0" , PI_REQUEST_CODE , PI_WARN , "Res field is NOT set to zero as required by RFC 5044" , EXPFILL }
 }
 , {
 & ei_mpa_rev_field_not_set1 , {
 "iwarp_mpa.rev.not_set1" , PI_REQUEST_CODE , PI_WARN , "Rev field is NOT set to one as required by RFC 5044" , EXPFILL }
 }
 , {
 & ei_mpa_reject_bit_responder , {
 "iwarp_mpa.reject_bit_responder" , PI_RESPONSE_CODE , PI_NOTE , "Reject bit set by Responder" , EXPFILL }
 }
 , {
 & ei_mpa_bad_length , {
 "iwarp_mpa.bad_length" , PI_MALFORMED , PI_ERROR , "Bad length" , EXPFILL }
 }
 , }
 ;
 expert_module_t * expert_iwarp_mpa ;
 proto_iwarp_mpa = proto_register_protocol ( "iWARP Marker Protocol data unit Aligned framing" , "IWARP_MPA" , "iwarp_mpa" ) ;
 proto_register_field_array ( proto_iwarp_mpa , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 expert_iwarp_mpa = expert_register_protocol ( proto_iwarp_mpa ) ;
 expert_register_field_array ( expert_iwarp_mpa , ei , array_length ( ei ) ) ;
 }