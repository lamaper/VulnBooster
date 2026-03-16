void proto_item_fill_label ( field_info * fi , gchar * label_str ) {
 header_field_info * hfinfo ;
 guint8 * bytes ;
 guint32 integer ;
 guint64 integer64 ;
 ipv4_addr_and_mask * ipv4 ;
 e_guid_t * guid ;
 guint32 n_addr ;
 gchar * name ;
 address addr ;
 char * addr_str ;
 char * tmp ;
 if ( ! fi ) {
 if ( label_str ) label_str [ 0 ] = '\0' ;
 return ;
 }
 hfinfo = fi -> hfinfo ;
 switch ( hfinfo -> type ) {
 case FT_NONE : case FT_PROTOCOL : g_strlcpy ( label_str , hfinfo -> name , ITEM_LABEL_LENGTH ) ;
 break ;
 case FT_BOOLEAN : fill_label_boolean ( fi , label_str ) ;
 break ;
 case FT_BYTES : case FT_UINT_BYTES : bytes = ( guint8 * ) fvalue_get ( & fi -> value ) ;
 if ( bytes ) {
 char * str = NULL ;
 switch ( hfinfo -> display ) {
 case SEP_DOT : str = bytestring_to_str ( NULL , bytes , fvalue_length ( & fi -> value ) , '.' ) ;
 break ;
 case SEP_DASH : str = bytestring_to_str ( NULL , bytes , fvalue_length ( & fi -> value ) , '-' ) ;
 break ;
 case SEP_COLON : str = bytestring_to_str ( NULL , bytes , fvalue_length ( & fi -> value ) , ':' ) ;
 break ;
 case SEP_SPACE : str = bytestring_to_str ( NULL , bytes , fvalue_length ( & fi -> value ) , ' ' ) ;
 break ;
 case BASE_NONE : default : if ( prefs . display_byte_fields_with_spaces ) {
 str = bytestring_to_str ( NULL , bytes , fvalue_length ( & fi -> value ) , ' ' ) ;
 }
 else {
 str = bytes_to_str ( NULL , bytes , fvalue_length ( & fi -> value ) ) ;
 }
 break ;
 }
 label_fill ( label_str , 0 , hfinfo , str ) ;
 wmem_free ( NULL , str ) ;
 }
 else {
 if ( hfinfo -> display & BASE_ALLOW_ZERO ) {
 label_fill ( label_str , 0 , hfinfo , "<none>" ) ;
 }
 else {
 label_fill ( label_str , 0 , hfinfo , "<MISSING>" ) ;
 }
 }
 break ;
 case FT_UINT8 : case FT_UINT16 : case FT_UINT24 : case FT_UINT32 : if ( hfinfo -> bitmask ) {
 fill_label_bitfield ( fi , label_str , FALSE ) ;
 }
 else {
 fill_label_number ( fi , label_str , FALSE ) ;
 }
 break ;
 case FT_FRAMENUM : fill_label_number ( fi , label_str , FALSE ) ;
 break ;
 case FT_UINT40 : case FT_UINT48 : case FT_UINT56 : case FT_UINT64 : if ( hfinfo -> bitmask ) {
 fill_label_bitfield64 ( fi , label_str , FALSE ) ;
 }
 else {
 fill_label_number64 ( fi , label_str , FALSE ) ;
 }
 break ;
 case FT_INT8 : case FT_INT16 : case FT_INT24 : case FT_INT32 : if ( hfinfo -> bitmask ) {
 fill_label_bitfield ( fi , label_str , TRUE ) ;
 }
 else {
 fill_label_number ( fi , label_str , TRUE ) ;
 }
 break ;
 case FT_INT40 : case FT_INT48 : case FT_INT56 : case FT_INT64 : if ( hfinfo -> bitmask ) {
 fill_label_bitfield64 ( fi , label_str , TRUE ) ;
 }
 else {
 fill_label_number64 ( fi , label_str , TRUE ) ;
 }
 break ;
 case FT_FLOAT : g_snprintf ( label_str , ITEM_LABEL_LENGTH , "%s: %." G_STRINGIFY ( FLT_DIG ) "g" , hfinfo -> name , fvalue_get_floating ( & fi -> value ) ) ;
 break ;
 case FT_DOUBLE : g_snprintf ( label_str , ITEM_LABEL_LENGTH , "%s: %." G_STRINGIFY ( DBL_DIG ) "g" , hfinfo -> name , fvalue_get_floating ( & fi -> value ) ) ;
 break ;
 case FT_ABSOLUTE_TIME : tmp = abs_time_to_str ( NULL , ( const nstime_t * ) fvalue_get ( & fi -> value ) , ( absolute_time_display_e ) hfinfo -> display , TRUE ) ;
 label_fill ( label_str , 0 , hfinfo , tmp ) ;
 wmem_free ( NULL , tmp ) ;
 break ;
 case FT_RELATIVE_TIME : tmp = rel_time_to_secs_str ( NULL , ( const nstime_t * ) fvalue_get ( & fi -> value ) ) ;
 g_snprintf ( label_str , ITEM_LABEL_LENGTH , "%s: %s seconds" , hfinfo -> name , tmp ) ;
 wmem_free ( NULL , tmp ) ;
 break ;
 case FT_IPXNET : integer = fvalue_get_uinteger ( & fi -> value ) ;
 tmp = get_ipxnet_name ( NULL , integer ) ;
 g_snprintf ( label_str , ITEM_LABEL_LENGTH , "%s: %s (0x%08X)" , hfinfo -> name , tmp , integer ) ;
 wmem_free ( NULL , tmp ) ;
 break ;
 case FT_AX25 : addr . type = AT_AX25 ;
 addr . len = AX25_ADDR_LEN ;
 addr . data = ( guint8 * ) fvalue_get ( & fi -> value ) ;
 addr_str = ( char * ) address_to_str ( NULL , & addr ) ;
 g_snprintf ( label_str , ITEM_LABEL_LENGTH , "%s: %s" , hfinfo -> name , addr_str ) ;
 wmem_free ( NULL , addr_str ) ;
 break ;
 case FT_VINES : addr . type = vines_address_type ;
 addr . len = VINES_ADDR_LEN ;
 addr . data = ( guint8 * ) fvalue_get ( & fi -> value ) ;
 addr_str = ( char * ) address_to_str ( NULL , & addr ) ;
 g_snprintf ( label_str , ITEM_LABEL_LENGTH , "%s: %s" , hfinfo -> name , addr_str ) ;
 wmem_free ( NULL , addr_str ) ;
 break ;
 case FT_ETHER : bytes = ( guint8 * ) fvalue_get ( & fi -> value ) ;
 addr . type = AT_ETHER ;
 addr . len = 6 ;
 addr . data = bytes ;
 addr_str = ( char * ) address_with_resolution_to_str ( NULL , & addr ) ;
 g_snprintf ( label_str , ITEM_LABEL_LENGTH , "%s: %s" , hfinfo -> name , addr_str ) ;
 wmem_free ( NULL , addr_str ) ;
 break ;
 case FT_IPv4 : ipv4 = ( ipv4_addr_and_mask * ) fvalue_get ( & fi -> value ) ;
 n_addr = ipv4_get_net_order_addr ( ipv4 ) ;
 addr . type = AT_IPv4 ;
 addr . len = 4 ;
 addr . data = & n_addr ;
 if ( hfinfo -> display == BASE_NETMASK ) {
 addr_str = ( char * ) address_to_str ( NULL , & addr ) ;
 }
 else {
 addr_str = ( char * ) address_with_resolution_to_str ( NULL , & addr ) ;
 }
 g_snprintf ( label_str , ITEM_LABEL_LENGTH , "%s: %s" , hfinfo -> name , addr_str ) ;
 wmem_free ( NULL , addr_str ) ;
 break ;
 case FT_IPv6 : bytes = ( guint8 * ) fvalue_get ( & fi -> value ) ;
 addr . type = AT_IPv6 ;
 addr . len = 16 ;
 addr . data = bytes ;
 addr_str = ( char * ) address_with_resolution_to_str ( NULL , & addr ) ;
 g_snprintf ( label_str , ITEM_LABEL_LENGTH , "%s: %s" , hfinfo -> name , addr_str ) ;
 wmem_free ( NULL , addr_str ) ;
 break ;
 case FT_FCWWN : addr . type = AT_FCWWN ;
 addr . len = FCWWN_ADDR_LEN ;
 addr . data = ( guint8 * ) fvalue_get ( & fi -> value ) ;
 addr_str = ( char * ) address_with_resolution_to_str ( NULL , & addr ) ;
 g_snprintf ( label_str , ITEM_LABEL_LENGTH , "%s: %s" , hfinfo -> name , addr_str ) ;
 wmem_free ( NULL , addr_str ) ;
 break ;
 case FT_GUID : guid = ( e_guid_t * ) fvalue_get ( & fi -> value ) ;
 tmp = guid_to_str ( NULL , guid ) ;
 label_fill ( label_str , 0 , hfinfo , tmp ) ;
 wmem_free ( NULL , tmp ) ;
 break ;
 case FT_OID : bytes = ( guint8 * ) fvalue_get ( & fi -> value ) ;
 name = oid_resolved_from_encoded ( NULL , bytes , fvalue_length ( & fi -> value ) ) ;
 tmp = oid_encoded2string ( NULL , bytes , fvalue_length ( & fi -> value ) ) ;
 if ( name ) {
 label_fill_descr ( label_str , 0 , hfinfo , tmp , name ) ;
 wmem_free ( NULL , name ) ;
 }
 else {
 label_fill ( label_str , 0 , hfinfo , tmp ) ;
 }
 wmem_free ( NULL , tmp ) ;
 break ;
 case FT_REL_OID : bytes = ( guint8 * ) fvalue_get ( & fi -> value ) ;
 name = rel_oid_resolved_from_encoded ( NULL , bytes , fvalue_length ( & fi -> value ) ) ;
 tmp = rel_oid_encoded2string ( NULL , bytes , fvalue_length ( & fi -> value ) ) ;
 if ( name ) {
 label_fill_descr ( label_str , 0 , hfinfo , tmp , name ) ;
 wmem_free ( NULL , name ) ;
 }
 else {
 label_fill ( label_str , 0 , hfinfo , tmp ) ;
 }
 wmem_free ( NULL , tmp ) ;
 break ;
 case FT_SYSTEM_ID : bytes = ( guint8 * ) fvalue_get ( & fi -> value ) ;
 tmp = print_system_id ( NULL , bytes , fvalue_length ( & fi -> value ) ) ;
 label_fill ( label_str , 0 , hfinfo , tmp ) ;
 wmem_free ( NULL , tmp ) ;
 break ;
 case FT_EUI64 : integer64 = fvalue_get_uinteger64 ( & fi -> value ) ;
 addr_str = eui64_to_str ( NULL , integer64 ) ;
 tmp = ( char * ) eui64_to_display ( NULL , integer64 ) ;
 label_fill_descr ( label_str , 0 , hfinfo , tmp , addr_str ) ;
 wmem_free ( NULL , tmp ) ;
 wmem_free ( NULL , addr_str ) ;
 break ;
 case FT_STRING : case FT_STRINGZ : case FT_UINT_STRING : case FT_STRINGZPAD : bytes = ( guint8 * ) fvalue_get ( & fi -> value ) ;
 label_fill ( label_str , 0 , hfinfo , hfinfo_format_text ( hfinfo , bytes ) ) ;
 break ;
 case FT_IEEE_11073_SFLOAT : tmp = fvalue_to_string_repr ( NULL , & fi -> value , FTREPR_DISPLAY , hfinfo -> display ) ;
 g_snprintf ( label_str , ITEM_LABEL_LENGTH , "%s: %s" , hfinfo -> name , tmp ) ;
 wmem_free ( NULL , tmp ) ;
 break ;
 case FT_IEEE_11073_FLOAT : tmp = fvalue_to_string_repr ( NULL , & fi -> value , FTREPR_DISPLAY , hfinfo -> display ) ;
 g_snprintf ( label_str , ITEM_LABEL_LENGTH , "%s: %s" , hfinfo -> name , tmp ) ;
 wmem_free ( NULL , tmp ) ;
 break ;
 default : g_error ( "hfinfo->type %d (%s) not handled\n" , hfinfo -> type , ftype_name ( hfinfo -> type ) ) ;
 DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 break ;
 }
 }