void proto_register_opcua ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_opcua_fragments , {
 "Message fragments" , "opcua.fragments" , FT_NONE , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_opcua_fragment , {
 "Message fragment" , "opcua.fragment" , FT_FRAMENUM , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_opcua_fragment_overlap , {
 "Message fragment overlap" , "opcua.fragment.overlap" , FT_BOOLEAN , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_opcua_fragment_overlap_conflicts , {
 "Message fragment overlapping with conflicting data" , "opcua.fragment.overlap.conflicts" , FT_BOOLEAN , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_opcua_fragment_multiple_tails , {
 "Message has multiple tail fragments" , "opcua.fragment.multiple_tails" , FT_BOOLEAN , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_opcua_fragment_too_long_fragment , {
 "Message fragment too long" , "opcua.fragment.too_long_fragment" , FT_BOOLEAN , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_opcua_fragment_error , {
 "Message defragmentation error" , "opcua.fragment.error" , FT_FRAMENUM , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_opcua_fragment_count , {
 "Message fragment count" , "opcua.fragment.count" , FT_UINT32 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_opcua_reassembled_in , {
 "Reassembled in" , "opcua.reassembled.in" , FT_FRAMENUM , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_opcua_reassembled_length , {
 "Reassembled length" , "opcua.reassembled.length" , FT_UINT32 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ] = {
 & ett_opcua_extensionobject , & ett_opcua_nodeid , & ett_opcua_transport , & ett_opcua_fragment , & ett_opcua_fragments }
 ;
 proto_opcua = proto_register_protocol ( "OpcUa Binary Protocol" , "OpcUa" , "opcua" ) ;
 registerTransportLayerTypes ( proto_opcua ) ;
 registerSecurityLayerTypes ( proto_opcua ) ;
 registerApplicationLayerTypes ( proto_opcua ) ;
 registerSimpleTypes ( proto_opcua ) ;
 registerEnumTypes ( proto_opcua ) ;
 registerComplexTypes ( ) ;
 registerServiceTypes ( ) ;
 registerFieldTypes ( proto_opcua ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 proto_register_field_array ( proto_opcua , hf , array_length ( hf ) ) ;
 reassembly_table_register ( & opcua_reassembly_table , & addresses_reassembly_table_functions ) ;
 }