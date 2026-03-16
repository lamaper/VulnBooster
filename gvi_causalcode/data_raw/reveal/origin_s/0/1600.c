void proto_register_amf ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_amf_version , {
 "AMF version" , "amf.version" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_amf_header_count , {
 "Header count" , "amf.header_count" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_amf_header_name , {
 "Name" , "amf.header.name" , FT_UINT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_amf_header_must_understand , {
 "Must understand" , "amf.header.must_understand" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_amf_header_length , {
 "Length" , "amf.header.length" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , # if 0 {
 & hf_amf_header_value_type , {
 "Value type" , "amf.header.value_type" , FT_UINT32 , BASE_HEX , VALS ( rtmpt_type_vals ) , 0x0 , NULL , HFILL }
 }
 , # endif {
 & hf_amf_message_count , {
 "Message count" , "amf.message_count" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_amf_message_target_uri , {
 "Target URI" , "amf.message.target_uri" , FT_UINT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_amf_message_response_uri , {
 "Response URI" , "amf.message.response_uri" , FT_UINT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_amf_message_length , {
 "Length" , "amf.message.length" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_amf_amf0_type , {
 "AMF0 type" , "amf.amf0_type" , FT_UINT8 , BASE_HEX , VALS ( amf0_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_amf_amf3_type , {
 "AMF3 type" , "amf.amf3_type" , FT_UINT8 , BASE_HEX , VALS ( amf3_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_amf_number , {
 "Number" , "amf.number" , FT_DOUBLE , BASE_NONE , NULL , 0x0 , "AMF number" , HFILL }
 }
 , {
 & hf_amf_integer , {
 "Integer" , "amf.integer" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "RTMPT AMF3 integer" , HFILL }
 }
 , {
 & hf_amf_boolean , {
 "Boolean" , "amf.boolean" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , "AMF boolean" , HFILL }
 }
 , {
 & hf_amf_stringlength , {
 "String length" , "amf.stringlength" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "AMF string length" , HFILL }
 }
 , {
 & hf_amf_string , {
 "String" , "amf.string" , FT_STRING , BASE_NONE , NULL , 0x0 , "AMF string" , HFILL }
 }
 , {
 & hf_amf_string_reference , {
 "String reference" , "amf.string_reference" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "RTMPT AMF3 string reference" , HFILL }
 }
 , {
 & hf_amf_object_reference , {
 "Object reference" , "amf.object_reference" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "AMF object reference" , HFILL }
 }
 , {
 & hf_amf_date , {
 "Date" , "amf.date" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0x0 , "AMF date" , HFILL }
 }
 , # if 0 {
 & hf_amf_longstringlength , {
 "String length" , "amf.longstringlength" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "AMF long string length" , HFILL }
 }
 , # endif {
 & hf_amf_longstring , {
 "Long string" , "amf.longstring" , FT_STRING , BASE_NONE , NULL , 0x0 , "AMF long string" , HFILL }
 }
 , {
 & hf_amf_xml_doc , {
 "XML document" , "amf.xml_doc" , FT_STRING , BASE_NONE , NULL , 0x0 , "AMF XML document" , HFILL }
 }
 , {
 & hf_amf_xmllength , {
 "XML text length" , "amf.xmllength" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "AMF E4X XML length" , HFILL }
 }
 , {
 & hf_amf_xml , {
 "XML" , "amf.xml" , FT_STRING , BASE_NONE , NULL , 0x0 , "AMF E4X XML" , HFILL }
 }
 , {
 & hf_amf_int64 , {
 "Int64" , "amf.int64" , FT_INT64 , BASE_DEC , NULL , 0x0 , "AMF int64" , HFILL }
 }
 , {
 & hf_amf_bytearraylength , {
 "ByteArray length" , "amf.bytearraylength" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "RTMPT AMF3 ByteArray length" , HFILL }
 }
 , {
 & hf_amf_bytearray , {
 "ByteArray" , "amf.bytearray" , FT_BYTES , BASE_NONE , NULL , 0x0 , "RTMPT AMF3 ByteArray" , HFILL }
 }
 , {
 & hf_amf_object , {
 "Object" , "amf.object" , FT_NONE , BASE_NONE , NULL , 0x0 , "AMF object" , HFILL }
 }
 , {
 & hf_amf_traitcount , {
 "Trait count" , "amf.traitcount" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "AMF count of traits for an object" , HFILL }
 }
 , {
 & hf_amf_classnamelength , {
 "Class name length" , "amf.classnamelength" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "AMF class name length" , HFILL }
 }
 , {
 & hf_amf_classname , {
 "Class name" , "amf.classname" , FT_STRING , BASE_NONE , NULL , 0x0 , "AMF class name" , HFILL }
 }
 , {
 & hf_amf_membernamelength , {
 "Member name length" , "amf.membernamelength" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "AMF member name length" , HFILL }
 }
 , {
 & hf_amf_membername , {
 "Member name" , "amf.membername" , FT_STRING , BASE_NONE , NULL , 0x0 , "AMF member name" , HFILL }
 }
 , {
 & hf_amf_trait_reference , {
 "Trait reference" , "amf.trait_reference" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "AMF trait reference" , HFILL }
 }
 , {
 & hf_amf_ecmaarray , {
 "ECMA array" , "amf.ecmaarray" , FT_NONE , BASE_NONE , NULL , 0x0 , "AMF ECMA array" , HFILL }
 }
 , {
 & hf_amf_strictarray , {
 "Strict array" , "amf.strictarray" , FT_NONE , BASE_NONE , NULL , 0x0 , "AMF strict array" , HFILL }
 }
 , {
 & hf_amf_array , {
 "Array" , "amf.array" , FT_NONE , BASE_NONE , NULL , 0x0 , "RTMPT AMF3 array" , HFILL }
 }
 , {
 & hf_amf_arraylength , {
 "Array length" , "amf.arraylength" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "AMF array length" , HFILL }
 }
 , {
 & hf_amf_arraydenselength , {
 "Length of dense portion" , "amf.arraydenselength" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "AMF length of dense portion of array" , HFILL }
 }
 , {
 & hf_amf_end_of_object_marker , {
 "End Of Object Marker" , "amf.end_of_object_marker" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_amf_end_of_associative_part , {
 "End of associative part" , "amf.end_of_associative_part" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_amf_end_of_dynamic_members , {
 "End Of dynamic members" , "amf.end_of_dynamic_members" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , }
 ;
 static gint * ett [ ] = {
 & ett_amf , & ett_amf_headers , & ett_amf_messages , & ett_amf_value , & ett_amf_property , & ett_amf_string , & ett_amf_array_element , & ett_amf_traits , & ett_amf_trait_member , }
 ;
 proto_amf = proto_register_protocol ( "Action Message Format" , "AMF" , "amf" ) ;
 proto_register_field_array ( proto_amf , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 }