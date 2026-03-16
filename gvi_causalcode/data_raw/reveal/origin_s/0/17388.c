void proto_register_packetbb ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_packetbb_header , {
 "Packet header" , "packetbb.header" , FT_NONE , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_version , {
 "Version" , "packetbb.version" , FT_UINT8 , BASE_DEC , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_header_flags , {
 "Flags" , "packetbb.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0F , NULL , HFILL }
 }
 , {
 & hf_packetbb_header_flags_phasseqnum , {
 "Has sequence number" , "packetbb.flags.phasseqnum" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , PACKET_HEADER_HASSEQNR , NULL , HFILL }
 }
 , {
 & hf_packetbb_header_flags_phastlv , {
 "Has tlv block" , "packetbb.flags.phastlv" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , PACKET_HEADER_HASTLV , NULL , HFILL }
 }
 , {
 & hf_packetbb_seqnr , {
 "Sequence number" , "packetbb.seqnr" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msg , {
 "Message" , "packetbb.msg" , FT_NONE , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader , {
 "Message header" , "packetbb.msg.header" , FT_NONE , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_type , {
 "Type" , "packetbb.msg.type" , FT_UINT8 , BASE_DEC , VALS ( msgheader_type_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_flags , {
 "Flags" , "packetbb.msg.flags" , FT_UINT8 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_flags_mhasorig , {
 "Has originator address" , "packetbb.msg.flags.mhasorig" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , MSG_HEADER_HASORIG , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_flags_mhashoplimit , {
 "Has hoplimit" , "packetbb.msg.flags.mhashoplimit" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , MSG_HEADER_HASHOPLIMIT , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_flags_mhashopcount , {
 "Has hopcount" , "packetbb.msg.flags.mhashopcount" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , MSG_HEADER_HASHOPCOUNT , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_flags_mhasseqnr , {
 "Has sequence number" , "packetbb.msg.flags.mhasseqnum" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , MSG_HEADER_HASSEQNR , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_addresssize , {
 "AddressSize" , "packetbb.msg.addrsize" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_size , {
 "Size" , "packetbb.msg.size" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_origaddripv4 , {
 "Originator address" , "packetbb.msg.origaddr4" , FT_IPv4 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_origaddripv6 , {
 "Originator address" , "packetbb.msg.origaddr6" , FT_IPv6 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_origaddrmac , {
 "Originator address" , "packetbb.msg.origaddrmac" , FT_ETHER , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_origaddrcustom , {
 "Originator address" , "packetbb.msg.origaddrcustom" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_hoplimit , {
 "Hop limit" , "packetbb.msg.hoplimit" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_hopcount , {
 "Hop count" , "packetbb.msg.hopcount" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgheader_seqnr , {
 "Sequence number" , "packetbb.msg.seqnum" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr , {
 "Address block" , "packetbb.msg.addr" , FT_NONE , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_num , {
 "Count" , "packetbb.msg.addr.num" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_flags , {
 "Flags" , "packetbb.msg.addr.flags" , FT_UINT8 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_flags_hashead , {
 "Has head" , "packetbb.msg.addr.hashead" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , ADDR_HASHEAD , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_flags_hasfulltail , {
 "Has full tail" , "packetbb.msg.addr.hasfulltail" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , ADDR_HASFULLTAIL , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_flags_haszerotail , {
 "Has zero tail" , "packetbb.msg.addr.haszerotail" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , ADDR_HASZEROTAIL , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_flags_hassingleprelen , {
 "Has single prelen" , "packetbb.msg.addr.hassingleprelen" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , ADDR_HASSINGLEPRELEN , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_flags_hasmultiprelen , {
 "Has multiple prelen" , "packetbb.msg.addr.hasmultiprelen" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , ADDR_HASMULTIPRELEN , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_head , {
 "Head" , "packetbb.msg.addr.head" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_tail , {
 "Tail" , "packetbb.msg.addr.tail" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_value [ 0 ] , {
 "Address" , "packetbb.msg.addr.value4" , FT_IPv4 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_value [ 1 ] , {
 "Address" , "packetbb.msg.addr.value6" , FT_IPv6 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_value [ 2 ] , {
 "Address" , "packetbb.msg.addr.valuemac" , FT_ETHER , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_value [ 3 ] , {
 "Address" , "packetbb.msg.addr.valuecustom" , FT_UINT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_value_mid , {
 "Mid" , "packetbb.msg.addr.value.mid" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_addr_value_prefix , {
 "Prefix" , "packetbb.msg.addr.value.prefix" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlvblock , {
 "TLV block" , "packetbb.tlvblock" , FT_NONE , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlvblock_length , {
 "Length" , "packetbb.tlvblock.length" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv , {
 "TLV" , "packetbb.tlv" , FT_NONE , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_pkttlv_type , {
 "Type" , "packetbb.pkttlv.type" , FT_UINT8 , BASE_DEC , VALS ( pkttlv_type_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_msgtlv_type , {
 "Type" , "packetbb.msgtlv.type" , FT_UINT8 , BASE_DEC , VALS ( msgtlv_type_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_addrtlv_type , {
 "Type" , "packetbb.addrtlv.type" , FT_UINT8 , BASE_DEC , VALS ( addrtlv_type_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_flags , {
 "Flags" , "packetbb.tlv.flags" , FT_UINT8 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_typeext , {
 "Extended Type" , "packetbb.tlv.typeext" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_flags_hastypext , {
 "Has type-ext" , "packetbb.tlv.hastypeext" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , TLV_HAS_TYPEEXT , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_flags_hassingleindex , {
 "Has single index" , "packetbb.tlv.hassingleindex" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , TLV_HAS_SINGLEINDEX , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_flags_hasmultiindex , {
 "Has multiple indices" , "packetbb.tlv.hasmultiindex" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , TLV_HAS_MULTIINDEX , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_flags_hasvalue , {
 "Has value" , "packetbb.tlv.hasvalue" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , TLV_HAS_VALUE , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_flags_hasextlen , {
 "Has extended length" , "packetbb.tlv.hasextlen" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , TLV_HAS_EXTLEN , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_flags_hasmultivalue , {
 "Has multiple values" , "packetbb.tlv.hasmultivalue" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , TLV_HAS_MULTIVALUE , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_indexstart , {
 "Index start" , "packetbb.tlv.indexstart" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_indexend , {
 "Index end" , "packetbb.tlv.indexend" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_length , {
 "Length" , "packetbb.tlv.length" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_value , {
 "Value" , "packetbb.tlv.value" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_packetbb_tlv_multivalue , {
 "Multivalue" , "packetbb.tlv.multivalue" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 }
 ;
 gint * ett_base [ ] = {
 & ett_packetbb , & ett_packetbb_header , & ett_packetbb_header_flags , & ett_packetbb_msgheader , & ett_packetbb_msgheader_flags , & ett_packetbb_addr , & ett_packetbb_addr_flags , & ett_packetbb_addr_value , & ett_packetbb_tlvblock , & ett_packetbb_tlv_flags , & ett_packetbb_tlv_value }
 ;
 static ei_register_info ei [ ] = {
 {
 & ei_packetbb_error , {
 "packetbb.error" , PI_PROTOCOL , PI_WARN , "ERROR!" , EXPFILL }
 }
 , }
 ;
 static gint * ett [ array_length ( ett_base ) + 2 * PACKETBB_MSG_TLV_LENGTH ] ;
 module_t * packetbb_module ;
 expert_module_t * expert_packetbb ;
 int i , j ;
 memcpy ( ett , ett_base , sizeof ( ett_base ) ) ;
 j = array_length ( ett_base ) ;
 for ( i = 0 ;
 i < PACKETBB_MSG_TLV_LENGTH ;
 i ++ ) {
 ett_packetbb_msg [ i ] = - 1 ;
 ett_packetbb_tlv [ i ] = - 1 ;
 ett [ j ++ ] = & ett_packetbb_msg [ i ] ;
 ett [ j ++ ] = & ett_packetbb_tlv [ i ] ;
 }
 proto_packetbb = proto_register_protocol ( "PacketBB Protocol" , "PacketBB" , "packetbb" ) ;
 proto_register_field_array ( proto_packetbb , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 expert_packetbb = expert_register_protocol ( proto_packetbb ) ;
 expert_register_field_array ( expert_packetbb , ei , array_length ( ei ) ) ;
 packetbb_module = prefs_register_protocol ( proto_packetbb , proto_reg_handoff_packetbb ) ;
 prefs_register_uint_preference ( packetbb_module , "communication_port" , "UDP port for packetbb" , "UDP communication port for packetbb PDUs" , 10 , & global_packetbb_port ) ;
 }