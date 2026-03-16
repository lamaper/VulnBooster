const gchar * proto_custom_set ( proto_tree * tree , GSList * field_ids , gint occurrence , gchar * result , gchar * expr , const int size ) {
 guint32 number ;
 guint64 number64 ;
 guint8 * bytes ;
 ipv4_addr_and_mask * ipv4 ;
 struct e_in6_addr * ipv6 ;
 address addr ;
 guint32 n_addr ;
 const true_false_string * tfstring ;
 int len , prev_len = 0 , last , i , offset_r = 0 , offset_e = 0 ;
 GPtrArray * finfos ;
 field_info * finfo = NULL ;
 header_field_info * hfinfo ;
 const gchar * abbrev = NULL ;
 const char * hf_str_val ;
 char number_buf [ 48 ] ;
 const char * number_out ;
 char * tmpbuf , * str ;
 int * field_idx ;
 int field_id ;
 int ii = 0 ;
 g_assert ( field_ids != NULL ) ;
 while ( ( field_idx = ( int * ) g_slist_nth_data ( field_ids , ii ++ ) ) ) {
 field_id = * field_idx ;
 PROTO_REGISTRAR_GET_NTH ( ( guint ) field_id , hfinfo ) ;
 if ( ! hfinfo ) return "" ;
 if ( occurrence < 0 ) {
 while ( hfinfo -> same_name_prev_id != - 1 ) {
 PROTO_REGISTRAR_GET_NTH ( hfinfo -> same_name_prev_id , hfinfo ) ;
 }
 }
 while ( hfinfo ) {
 finfos = proto_get_finfo_ptr_array ( tree , hfinfo -> id ) ;
 if ( ! finfos || ! ( len = g_ptr_array_len ( finfos ) ) ) {
 if ( occurrence < 0 ) {
 hfinfo = hfinfo -> same_name_next ;
 }
 else {
 hfinfo = hfinfo_same_name_get_prev ( hfinfo ) ;
 }
 continue ;
 }
 if ( ( ( occurrence - prev_len ) > len ) || ( ( occurrence + prev_len ) < - len ) ) {
 if ( occurrence < 0 ) {
 hfinfo = hfinfo -> same_name_next ;
 }
 else {
 hfinfo = hfinfo_same_name_get_prev ( hfinfo ) ;
 }
 prev_len += len ;
 continue ;
 }
 if ( occurrence < 0 ) {
 i = occurrence + len + prev_len ;
 last = i ;
 }
 else if ( occurrence > 0 ) {
 i = occurrence - 1 - prev_len ;
 last = i ;
 }
 else {
 i = 0 ;
 last = len - 1 ;
 }
 prev_len += len ;
 while ( i <= last ) {
 finfo = ( field_info * ) g_ptr_array_index ( finfos , i ) ;
 if ( offset_r && ( offset_r < ( size - 2 ) ) ) result [ offset_r ++ ] = ',' ;
 if ( offset_e && ( offset_e < ( size - 2 ) ) ) expr [ offset_e ++ ] = ',' ;
 switch ( hfinfo -> type ) {
 case FT_NONE : if ( offset_r == 0 ) {
 result [ 0 ] = '\0' ;
 }
 else if ( result [ offset_r - 1 ] == ',' ) {
 result [ offset_r - 1 ] = '\0' ;
 }
 break ;
 case FT_PROTOCOL : g_strlcpy ( result , "Yes" , size ) ;
 break ;
 case FT_UINT_BYTES : case FT_BYTES : bytes = ( guint8 * ) fvalue_get ( & finfo -> value ) ;
 if ( bytes ) {
 switch ( hfinfo -> display ) {
 case SEP_DOT : str = bytestring_to_str ( NULL , bytes , fvalue_length ( & finfo -> value ) , '.' ) ;
 break ;
 case SEP_DASH : str = bytestring_to_str ( NULL , bytes , fvalue_length ( & finfo -> value ) , '-' ) ;
 break ;
 case SEP_COLON : str = bytestring_to_str ( NULL , bytes , fvalue_length ( & finfo -> value ) , ':' ) ;
 break ;
 case SEP_SPACE : str = bytestring_to_str ( NULL , bytes , fvalue_length ( & finfo -> value ) , ' ' ) ;
 break ;
 case BASE_NONE : default : if ( prefs . display_byte_fields_with_spaces ) {
 str = bytestring_to_str ( NULL , bytes , fvalue_length ( & finfo -> value ) , ' ' ) ;
 }
 else {
 str = bytes_to_str ( NULL , bytes , fvalue_length ( & finfo -> value ) ) ;
 }
 break ;
 }
 offset_r += protoo_strlcpy ( result + offset_r , str , size - offset_r ) ;
 wmem_free ( NULL , str ) ;
 }
 else {
 if ( hfinfo -> display & BASE_ALLOW_ZERO ) {
 offset_r += protoo_strlcpy ( result + offset_r , "<none>" , size - offset_r ) ;
 }
 else {
 offset_r += protoo_strlcpy ( result + offset_r , "<MISSING>" , size - offset_r ) ;
 }
 }
 break ;
 case FT_ABSOLUTE_TIME : tmpbuf = abs_time_to_str ( NULL , ( const nstime_t * ) fvalue_get ( & finfo -> value ) , ( absolute_time_display_e ) hfinfo -> display , TRUE ) ;
 offset_r += protoo_strlcpy ( result + offset_r , tmpbuf , size - offset_r ) ;
 wmem_free ( NULL , tmpbuf ) ;
 break ;
 case FT_RELATIVE_TIME : tmpbuf = rel_time_to_secs_str ( NULL , ( const nstime_t * ) fvalue_get ( & finfo -> value ) ) ;
 offset_r += protoo_strlcpy ( result + offset_r , tmpbuf , size - offset_r ) ;
 wmem_free ( NULL , tmpbuf ) ;
 break ;
 case FT_BOOLEAN : number64 = fvalue_get_uinteger64 ( & finfo -> value ) ;
 tfstring = ( const true_false_string * ) & tfs_true_false ;
 if ( hfinfo -> strings ) {
 tfstring = ( const struct true_false_string * ) hfinfo -> strings ;
 }
 offset_r += protoo_strlcpy ( result + offset_r , number64 ? tfstring -> true_string : tfstring -> false_string , size - offset_r ) ;
 offset_e += protoo_strlcpy ( expr + offset_e , number64 ? "1" : "0" , size - offset_e ) ;
 break ;
 case FT_INT8 : case FT_INT16 : case FT_INT24 : case FT_INT32 : case FT_UINT8 : case FT_UINT16 : case FT_UINT24 : case FT_UINT32 : case FT_FRAMENUM : hf_str_val = NULL ;
 number = IS_FT_INT ( hfinfo -> type ) ? ( guint32 ) fvalue_get_sinteger ( & finfo -> value ) : fvalue_get_uinteger ( & finfo -> value ) ;
 if ( ( hfinfo -> display & FIELD_DISPLAY_E_MASK ) == BASE_CUSTOM ) {
 gchar tmp [ ITEM_LABEL_LENGTH ] ;
 custom_fmt_func_t fmtfunc = ( custom_fmt_func_t ) hfinfo -> strings ;
 DISSECTOR_ASSERT ( fmtfunc ) ;
 fmtfunc ( tmp , number ) ;
 offset_r += protoo_strlcpy ( result + offset_r , tmp , size - offset_r ) ;
 }
 else if ( hfinfo -> strings && hfinfo -> type != FT_FRAMENUM ) {
 number_out = hf_str_val = hf_try_val_to_str ( number , hfinfo ) ;
 if ( ! number_out ) number_out = hfinfo_number_value_format_display ( hfinfo , BASE_DEC , number_buf , number ) ;
 offset_r += protoo_strlcpy ( result + offset_r , number_out , size - offset_r ) ;
 }
 else {
 number_out = hfinfo_number_value_format ( hfinfo , number_buf , number ) ;
 offset_r += protoo_strlcpy ( result + offset_r , number_out , size - offset_r ) ;
 }
 if ( hf_str_val && ( hfinfo -> display & FIELD_DISPLAY_E_MASK ) == BASE_NONE ) {
 g_snprintf ( expr + offset_e , size - offset_e , "\"%s\"" , hf_str_val ) ;
 }
 else {
 number_out = hfinfo_numeric_value_format ( hfinfo , number_buf , number ) ;
 g_strlcpy ( expr + offset_e , number_out , size - offset_e ) ;
 }
 offset_e = ( int ) strlen ( expr ) ;
 break ;
 case FT_INT40 : case FT_INT48 : case FT_INT56 : case FT_INT64 : case FT_UINT40 : case FT_UINT48 : case FT_UINT56 : case FT_UINT64 : hf_str_val = NULL ;
 number64 = IS_FT_INT ( hfinfo -> type ) ? ( guint64 ) fvalue_get_sinteger64 ( & finfo -> value ) : fvalue_get_uinteger64 ( & finfo -> value ) ;
 if ( ( hfinfo -> display & FIELD_DISPLAY_E_MASK ) == BASE_CUSTOM ) {
 gchar tmp [ ITEM_LABEL_LENGTH ] ;
 custom_fmt_func_64_t fmtfunc64 = ( custom_fmt_func_64_t ) hfinfo -> strings ;
 DISSECTOR_ASSERT ( fmtfunc64 ) ;
 fmtfunc64 ( tmp , number64 ) ;
 offset_r += protoo_strlcpy ( result + offset_r , tmp , size - offset_r ) ;
 }
 else if ( hfinfo -> strings ) {
 number_out = hf_str_val = hf_try_val64_to_str ( number64 , hfinfo ) ;
 if ( ! number_out ) number_out = hfinfo_number_value_format_display64 ( hfinfo , BASE_DEC , number_buf , number64 ) ;
 offset_r += protoo_strlcpy ( result + offset_r , number_out , size - offset_r ) ;
 }
 else {
 number_out = hfinfo_number_value_format64 ( hfinfo , number_buf , number64 ) ;
 offset_r += protoo_strlcpy ( result + offset_r , number_out , size - offset_r ) ;
 }
 if ( hf_str_val && ( hfinfo -> display & FIELD_DISPLAY_E_MASK ) == BASE_NONE ) {
 g_snprintf ( expr + offset_e , size - offset_e , "\"%s\"" , hf_str_val ) ;
 }
 else {
 number_out = hfinfo_numeric_value_format64 ( hfinfo , number_buf , number64 ) ;
 g_strlcpy ( expr + offset_e , number_out , size - offset_e ) ;
 }
 offset_e = ( int ) strlen ( expr ) ;
 break ;
 case FT_EUI64 : str = eui64_to_str ( NULL , fvalue_get_uinteger64 ( & finfo -> value ) ) ;
 offset_r += protoo_strlcpy ( result + offset_r , str , size - offset_r ) ;
 wmem_free ( NULL , str ) ;
 break ;
 case FT_IPv4 : ipv4 = ( ipv4_addr_and_mask * ) fvalue_get ( & finfo -> value ) ;
 n_addr = ipv4_get_net_order_addr ( ipv4 ) ;
 set_address ( & addr , AT_IPv4 , 4 , & n_addr ) ;
 address_to_str_buf ( & addr , result + offset_r , size - offset_r ) ;
 offset_r = ( int ) strlen ( result ) ;
 break ;
 case FT_IPv6 : ipv6 = ( struct e_in6_addr * ) fvalue_get ( & finfo -> value ) ;
 set_address ( & addr , AT_IPv6 , sizeof ( struct e_in6_addr ) , ipv6 ) ;
 address_to_str_buf ( & addr , result + offset_r , size - offset_r ) ;
 offset_r = ( int ) strlen ( result ) ;
 break ;
 case FT_FCWWN : set_address ( & addr , AT_FCWWN , FCWWN_ADDR_LEN , fvalue_get ( & finfo -> value ) ) ;
 address_to_str_buf ( & addr , result + offset_r , size - offset_r ) ;
 offset_r = ( int ) strlen ( result ) ;
 break ;
 case FT_ETHER : set_address ( & addr , AT_ETHER , FT_ETHER_LEN , fvalue_get ( & finfo -> value ) ) ;
 address_to_str_buf ( & addr , result + offset_r , size - offset_r ) ;
 offset_r = ( int ) strlen ( result ) ;
 break ;
 case FT_GUID : str = guid_to_str ( NULL , ( e_guid_t * ) fvalue_get ( & finfo -> value ) ) ;
 offset_r += protoo_strlcpy ( result + offset_r , str , size - offset_r ) ;
 wmem_free ( NULL , str ) ;
 break ;
 case FT_REL_OID : bytes = ( guint8 * ) fvalue_get ( & finfo -> value ) ;
 str = rel_oid_resolved_from_encoded ( NULL , bytes , fvalue_length ( & finfo -> value ) ) ;
 offset_r += protoo_strlcpy ( result + offset_r , str , size - offset_r ) ;
 wmem_free ( NULL , str ) ;
 str = rel_oid_encoded2string ( NULL , bytes , fvalue_length ( & finfo -> value ) ) ;
 offset_e += protoo_strlcpy ( expr + offset_e , str , size - offset_e ) ;
 wmem_free ( NULL , str ) ;
 break ;
 case FT_OID : bytes = ( guint8 * ) fvalue_get ( & finfo -> value ) ;
 str = oid_resolved_from_encoded ( NULL , bytes , fvalue_length ( & finfo -> value ) ) ;
 offset_r += protoo_strlcpy ( result + offset_r , str , size - offset_r ) ;
 wmem_free ( NULL , str ) ;
 str = oid_encoded2string ( NULL , bytes , fvalue_length ( & finfo -> value ) ) ;
 offset_e += protoo_strlcpy ( expr + offset_e , str , size - offset_e ) ;
 wmem_free ( NULL , str ) ;
 break ;
 case FT_SYSTEM_ID : bytes = ( guint8 * ) fvalue_get ( & finfo -> value ) ;
 str = print_system_id ( NULL , bytes , fvalue_length ( & finfo -> value ) ) ;
 offset_r += protoo_strlcpy ( result + offset_r , str , size - offset_r ) ;
 offset_e += protoo_strlcpy ( expr + offset_e , str , size - offset_e ) ;
 wmem_free ( NULL , str ) ;
 break ;
 case FT_FLOAT : g_snprintf ( result + offset_r , size - offset_r , "%." G_STRINGIFY ( FLT_DIG ) "g" , fvalue_get_floating ( & finfo -> value ) ) ;
 offset_r = ( int ) strlen ( result ) ;
 break ;
 case FT_DOUBLE : g_snprintf ( result + offset_r , size - offset_r , "%." G_STRINGIFY ( DBL_DIG ) "g" , fvalue_get_floating ( & finfo -> value ) ) ;
 offset_r = ( int ) strlen ( result ) ;
 break ;
 case FT_STRING : case FT_STRINGZ : case FT_UINT_STRING : case FT_STRINGZPAD : bytes = ( guint8 * ) fvalue_get ( & finfo -> value ) ;
 offset_r += protoo_strlcpy ( result + offset_r , hfinfo_format_text ( hfinfo , bytes ) , size - offset_r ) ;
 break ;
 case FT_IEEE_11073_SFLOAT : str = fvalue_to_string_repr ( NULL , & finfo -> value , FTREPR_DISPLAY , hfinfo -> display ) ;
 g_snprintf ( result + offset_r , size - offset_r , "%s: %s" , hfinfo -> name , str ) ;
 wmem_free ( NULL , str ) ;
 offset_r = ( int ) strlen ( result ) ;
 break ;
 case FT_IEEE_11073_FLOAT : str = fvalue_to_string_repr ( NULL , & finfo -> value , FTREPR_DISPLAY , hfinfo -> display ) ;
 g_snprintf ( result + offset_r , size - offset_r , "%s: %s" , hfinfo -> name , str ) ;
 offset_r = ( int ) strlen ( result ) ;
 wmem_free ( NULL , str ) ;
 break ;
 case FT_IPXNET : case FT_PCRE : default : g_error ( "hfinfo->type %d (%s) not handled\n" , hfinfo -> type , ftype_name ( hfinfo -> type ) ) ;
 DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 break ;
 }
 i ++ ;
 }
 switch ( hfinfo -> type ) {
 case FT_BOOLEAN : case FT_UINT8 : case FT_UINT16 : case FT_UINT24 : case FT_UINT32 : case FT_UINT40 : case FT_UINT48 : case FT_UINT56 : case FT_UINT64 : case FT_FRAMENUM : case FT_INT8 : case FT_INT16 : case FT_INT24 : case FT_INT32 : case FT_INT40 : case FT_INT48 : case FT_INT56 : case FT_INT64 : case FT_OID : case FT_REL_OID : case FT_SYSTEM_ID : break ;
 default : g_strlcpy ( expr , result , size ) ;
 break ;
 }
 if ( ! abbrev ) {
 abbrev = hfinfo -> abbrev ;
 }
 if ( occurrence == 0 ) {
 hfinfo = hfinfo_same_name_get_prev ( hfinfo ) ;
 }
 else {
 hfinfo = NULL ;
 }
 }
 }
 return abbrev ? abbrev : "" ;
 }