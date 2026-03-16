void proto_register_h245 ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_h245_pdu_type , {
 "PDU Type" , "h245.pdu_type" , FT_UINT32 , BASE_DEC , VALS ( h245_MultimediaSystemControlMessage_vals ) , 0 , "Type of H.245 PDU" , HFILL }
 }
 , {
 & hf_h245Manufacturer , {
 "H.245 Manufacturer" , "h245.Manufacturer" , FT_UINT32 , BASE_HEX , VALS ( H221ManufacturerCode_vals ) , 0 , "h245.H.221 Manufacturer" , HFILL }
 }
 , {
 & hf_h245_subMessageIdentifier_standard , {
 "subMessageIdentifier" , "h245.subMessageIdentifier.standard" , FT_UINT32 , BASE_DEC , VALS ( h245_h239subMessageIdentifier_vals ) , 0 , NULL , HFILL }
 }
 , # include "packet-h245-hfarr.c" }
 ;
 static gint * ett [ ] = {
 & ett_h245 , & ett_h245_returnedFunction , # include "packet-h245-ettarr.c" }
 ;
 module_t * h245_module ;
 proto_h245 = proto_register_protocol ( PNAME , PSNAME , PFNAME ) ;
 register_init_routine ( h245_init ) ;
 proto_register_field_array ( proto_h245 , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 h245_module = prefs_register_protocol ( proto_h245 , NULL ) ;
 prefs_register_bool_preference ( h245_module , "reassembly" , "Reassemble H.245 messages spanning multiple TCP segments" , "Whether the H.245 dissector should reassemble messages spanning multiple TCP segments." " To use this option, you must also enable \"Allow subdissectors to reassemble TCP streams\" in the TCP protocol settings." , & h245_reassembly ) ;
 prefs_register_bool_preference ( h245_module , "shorttypes" , "Show short message types" , "Whether the dissector should show short names or the long names from the standard" , & h245_shorttypes ) ;
 register_dissector ( "h245dg" , dissect_h245_h245 , proto_h245 ) ;
 register_dissector ( "h245" , dissect_h245 , proto_h245 ) ;
 nsp_object_dissector_table = register_dissector_table ( "h245.nsp.object" , "H.245 NonStandardParameter (object)" , FT_STRING , BASE_NONE ) ;
 nsp_h221_dissector_table = register_dissector_table ( "h245.nsp.h221" , "H.245 NonStandardParameter (h221)" , FT_UINT32 , BASE_HEX ) ;
 gef_name_dissector_table = register_dissector_table ( "h245.gef.name" , "H.245 Generic Extensible Framework (names)" , FT_STRING , BASE_NONE ) ;
 gef_content_dissector_table = register_dissector_table ( "h245.gef.content" , "H.245 Generic Extensible Framework" , FT_STRING , BASE_NONE ) ;
 h245_tap = register_tap ( "h245" ) ;
 h245dg_tap = register_tap ( "h245dg" ) ;
 oid_add_from_string ( "h239ControlCapability" , "0.0.8.239.1.1" ) ;
 oid_add_from_string ( "h239ExtendedVideoCapability" , "0.0.8.239.1.2" ) ;
 oid_add_from_string ( "generic-message" , "0.0.8.239.2" ) ;
 oid_add_from_string ( "h245 version 3" , "0.0.8.245.0.3" ) ;
 oid_add_from_string ( "h245 version 4" , "0.0.8.245.0.4" ) ;
 oid_add_from_string ( "h245 version 5" , "0.0.8.245.0.5" ) ;
 oid_add_from_string ( "h245 version 6" , "0.0.8.245.0.6" ) ;
 oid_add_from_string ( "h245 version 7" , "0.0.8.245.0.7" ) ;
 oid_add_from_string ( "h245 version 8" , "0.0.8.245.0.8" ) ;
 oid_add_from_string ( "h245 version 9" , "0.0.8.245.0.9" ) ;
 oid_add_from_string ( "h245 version 10" , "0.0.8.245.0.10" ) ;
 oid_add_from_string ( "h245 version 11" , "0.0.8.245.0.11" ) ;
 oid_add_from_string ( "h245 version 12" , "0.0.8.245.0.12" ) ;
 oid_add_from_string ( "h245 version 13" , "0.0.8.245.0.13" ) ;
 oid_add_from_string ( "ISO/IEC 14496-2 MPEG-4 video" , "0.0.8.245.1.0.0" ) ;
 oid_add_from_string ( "ISO/IEC 14496-3 MPEG-4 audio" , "0.0.8.245.1.1.0" ) ;
 oid_add_from_string ( "AMR" , "0.0.8.245.1.1.1" ) ;
 oid_add_from_string ( "acelp" , "0.0.8.245.1.1.2" ) ;
 oid_add_from_string ( "us1" , "0.0.8.245.1.1.3" ) ;
 oid_add_from_string ( "is127evrc" , "0.0.8.245.1.1.4" ) ;
 oid_add_from_string ( "ISO/IEC 13818-7" , "0.0.8.245.1.1.5" ) ;
 oid_add_from_string ( "rfc3389" , "0.0.8.245.1.1.6" ) ;
 oid_add_from_string ( "L-16" , "0.0.8.245.1.1.7" ) ;
 oid_add_from_string ( "bounded-audio-stream" , "0.0.8.245.1.1.8" ) ;
 oid_add_from_string ( "AMR-NB" , "0.0.8.245.1.1.9" ) ;
 oid_add_from_string ( "AMR-WB" , "0.0.8.245.1.1.10" ) ;
 oid_add_from_string ( "ilbc" , "0.0.8.245.1.1.11" ) ;
 oid_add_from_string ( "ISO/IEC 14496-1" , "0.0.8.245.1.2.0" ) ;
 oid_add_from_string ( "Nx64" , "0.0.8.245.1.2.1" ) ;
 oid_add_from_string ( "logical-channel-bit-ratemanagement" , "0.0.8.245.1.3.0" ) ;
 oid_add_from_string ( "h264 generic-capabilities" , "0.0.8.241.0.0.1" ) ;
 oid_add_from_string ( "iPpacketization_h241AnnexA(single NAL unit mode)" , "0.0.8.241.0.0.0.0" ) ;
 oid_add_from_string ( "iPpacketization_RFC3984NonInterleaved" , "0.0.8.241.0.0.0.1" ) ;
 oid_add_from_string ( "iPpacketization_RFC3984Interleaved" , "0.0.8.241.0.0.0.2" ) ;
 }