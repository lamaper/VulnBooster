static guint32 dissect_ies ( tvbuff_t * tvb , packet_info * pinfo , guint32 offset , proto_tree * iax_tree , proto_item * iax_item , iax2_ie_data * ie_data ) {
 DISSECTOR_ASSERT ( ie_data ) ;
 while ( offset < tvb_reported_length ( tvb ) ) {
 int ies_type = tvb_get_guint8 ( tvb , offset ) ;
 int ies_len = tvb_get_guint8 ( tvb , offset + 1 ) ;
 guint16 apparent_addr_family ;
 switch ( ies_type ) {
 case IAX_IE_DATAFORMAT : if ( ies_len != 4 ) {
 proto_tree_add_expert ( iax_tree , pinfo , & ei_iax_invalid_len , tvb , offset + 1 , 1 ) ;
 break ;
 }
 ie_data -> dataformat = tvb_get_ntohl ( tvb , offset + 2 ) ;
 break ;
 case IAX_IE_CALLED_NUMBER : iax2_info -> calledParty = wmem_strdup ( wmem_packet_scope ( ) , tvb_format_text ( tvb , offset + 2 , ies_len ) ) ;
 break ;
 case IAX_IE_CALLING_NUMBER : iax2_info -> callingParty = wmem_strdup ( wmem_packet_scope ( ) , tvb_format_text ( tvb , offset + 2 , ies_len ) ) ;
 break ;
 case IAX_IE_APPARENT_ADDR : apparent_addr_family = tvb_get_letohs ( tvb , offset + 2 ) ;
 switch ( apparent_addr_family ) {
 case LINUX_AF_INET : ie_data -> peer_ptype = PT_UDP ;
 ie_data -> peer_port = tvb_get_ntohs ( tvb , offset + 4 ) ;
 TVB_SET_ADDRESS ( & ie_data -> peer_address , AT_IPv4 , tvb , offset + 6 , 4 ) ;
 break ;
 default : expert_add_info_format ( pinfo , iax_item , & ei_iax_peer_address_unsupported , "Not supported in IAX dissector: peer address family of %u" , apparent_addr_family ) ;
 break ;
 }
 break ;
 }
 if ( iax_tree && ies_type < NUM_HF_IAX2_IES ) {
 proto_item * ti , * ie_item = NULL ;
 proto_tree * ies_tree ;
 int ie_hf = hf_iax2_ies [ ies_type ] ;
 ies_tree = proto_tree_add_subtree ( iax_tree , tvb , offset , ies_len + 2 , ett_iax2_ie , & ti , " " ) ;
 proto_tree_add_uint ( ies_tree , hf_iax2_ie_id , tvb , offset , 1 , ies_type ) ;
 proto_tree_add_uint ( ies_tree , hf_iax2_length , tvb , offset + 1 , 1 , ies_len ) ;
 switch ( ies_type ) {
 case IAX_IE_DATETIME : ie_item = dissect_datetime_ie ( tvb , offset , ies_tree ) ;
 break ;
 case IAX_IE_CAPABILITY : {
 proto_tree * codec_tree ;
 if ( ies_len != 4 ) {
 proto_tree_add_expert ( ies_tree , pinfo , & ei_iax_invalid_len , tvb , offset + 1 , 1 ) ;
 break ;
 }
 ie_item = proto_tree_add_item ( ies_tree , ie_hf , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 codec_tree = proto_item_add_subtree ( ie_item , ett_iax2_codecs ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_g723_1 , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_gsm , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_ulaw , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_alaw , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_g726_aal2 , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_adpcm , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_slinear , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_lpc10 , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_g729a , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_speex , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_ilbc , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_g726 , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_g722 , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_siren7 , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_siren14 , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_slinear16 , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_jpeg , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_png , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_h261 , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_h263 , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_h263_plus , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_h264 , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( codec_tree , hf_iax2_cap_mpeg4 , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 break ;
 }
 case IAX_IE_APPARENT_ADDR : {
 proto_tree * sockaddr_tree ;
 sockaddr_tree = proto_tree_add_subtree ( ies_tree , tvb , offset + 2 , 16 , ett_iax2_ies_apparent_addr , & ie_item , "Apparent Address" ) ;
 apparent_addr_family = tvb_get_letohs ( tvb , offset + 2 ) ;
 proto_tree_add_uint ( sockaddr_tree , hf_IAX_IE_APPARENTADDR_SINFAMILY , tvb , offset + 2 , 2 , apparent_addr_family ) ;
 if ( apparent_addr_family == LINUX_AF_INET ) {
 guint32 addr ;
 proto_tree_add_uint ( sockaddr_tree , hf_IAX_IE_APPARENTADDR_SINPORT , tvb , offset + 4 , 2 , ie_data -> peer_port ) ;
 memcpy ( & addr , ie_data -> peer_address . data , 4 ) ;
 proto_tree_add_ipv4 ( sockaddr_tree , hf_IAX_IE_APPARENTADDR_SINADDR , tvb , offset + 6 , 4 , addr ) ;
 }
 break ;
 }
 default : if ( ie_hf != - 1 ) {
 gint explen = proto_registrar_get_length ( ie_hf ) ;
 if ( explen != 0 && ies_len != explen ) {
 proto_tree_add_expert ( ies_tree , pinfo , & ei_iax_invalid_len , tvb , offset + 1 , 1 ) ;
 break ;
 }
 switch ( proto_registrar_get_ftype ( ie_hf ) ) {
 case FT_UINT8 : case FT_UINT16 : case FT_UINT24 : case FT_UINT32 : case FT_UINT64 : case FT_INT8 : case FT_INT16 : case FT_INT24 : case FT_INT32 : case FT_INT64 : case FT_BOOLEAN : case FT_IPv4 : ie_item = proto_tree_add_item ( ies_tree , ie_hf , tvb , offset + 2 , ies_len , ENC_BIG_ENDIAN ) ;
 break ;
 case FT_BYTES : case FT_NONE : ie_item = proto_tree_add_item ( ies_tree , ie_hf , tvb , offset + 2 , ies_len , ENC_NA ) ;
 break ;
 case FT_STRING : case FT_STRINGZ : ie_item = proto_tree_add_item ( ies_tree , ie_hf , tvb , offset + 2 , ies_len , ENC_UTF_8 | ENC_NA ) ;
 break ;
 default : DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 break ;
 }
 }
 else {
 guint32 value ;
 const guint8 * ptr ;
 const gchar * ie_name = val_to_str_ext_const ( ies_type , & iax_ies_type_ext , "Unknown" ) ;
 switch ( ies_len ) {
 case 1 : value = tvb_get_guint8 ( tvb , offset + 2 ) ;
 ie_item = proto_tree_add_uint_format ( ies_tree , hf_IAX_IE_UNKNOWN_BYTE , tvb , offset + 2 , 1 , value , "%s: %#02x" , ie_name , value ) ;
 break ;
 case 2 : value = tvb_get_ntohs ( tvb , offset + 2 ) ;
 ie_item = proto_tree_add_uint_format ( ies_tree , hf_IAX_IE_UNKNOWN_I16 , tvb , offset + 2 , 2 , value , "%s: %#04x" , ie_name , value ) ;
 break ;
 case 4 : value = tvb_get_ntohl ( tvb , offset + 2 ) ;
 ie_item = proto_tree_add_uint_format ( ies_tree , hf_IAX_IE_UNKNOWN_I32 , tvb , offset + 2 , 4 , value , "%s: %#08x" , ie_name , value ) ;
 break ;
 default : ptr = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset + 2 , ies_len , ENC_ASCII ) ;
 ie_item = proto_tree_add_string_format ( ies_tree , hf_IAX_IE_UNKNOWN_BYTES , tvb , offset + 2 , ies_len , ptr , "%s: %s" , ie_name , ptr ) ;
 break ;
 }
 }
 break ;
 }
 if ( ie_item && ! PROTO_ITEM_IS_HIDDEN ( ti ) ) {
 field_info * ie_finfo = PITEM_FINFO ( ie_item ) ;
 if ( ie_finfo && ie_finfo -> rep != NULL ) proto_item_set_text ( ti , "Information Element: %s" , ie_finfo -> rep -> representation ) ;
 else {
 guint8 * ie_val = ( guint8 * ) wmem_alloc ( wmem_packet_scope ( ) , ITEM_LABEL_LENGTH ) ;
 proto_item_fill_label ( ie_finfo , ie_val ) ;
 proto_item_set_text ( ti , "Information Element: %s" , ie_val ) ;
 }
 }
 }
 offset += ies_len + 2 ;
 }
 return offset ;
 }