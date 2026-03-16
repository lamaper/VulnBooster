static gboolean construct_match_selected_string ( field_info * finfo , epan_dissect_t * edt , char * * filter ) {
 header_field_info * hfinfo ;
 int abbrev_len ;
 char * ptr ;
 int buf_len ;
 int dfilter_len , i ;
 gint start , length , length_remaining ;
 guint8 c ;
 gchar is_signed_num = FALSE ;
 if ( ! finfo ) return FALSE ;
 hfinfo = finfo -> hfinfo ;
 DISSECTOR_ASSERT ( hfinfo ) ;
 abbrev_len = ( int ) strlen ( hfinfo -> abbrev ) ;
 if ( hfinfo -> strings && ( hfinfo -> display & FIELD_DISPLAY_E_MASK ) == BASE_NONE ) {
 const gchar * str = NULL ;
 switch ( hfinfo -> type ) {
 case FT_INT8 : case FT_INT16 : case FT_INT24 : case FT_INT32 : str = hf_try_val_to_str ( fvalue_get_sinteger ( & finfo -> value ) , hfinfo ) ;
 break ;
 case FT_UINT8 : case FT_UINT16 : case FT_UINT24 : case FT_UINT32 : str = hf_try_val_to_str ( fvalue_get_uinteger ( & finfo -> value ) , hfinfo ) ;
 break ;
 default : break ;
 }
 if ( str != NULL && filter != NULL ) {
 * filter = wmem_strdup_printf ( NULL , "%s == \"%s\"" , hfinfo -> abbrev , str ) ;
 return TRUE ;
 }
 }
 switch ( hfinfo -> type ) {
 case FT_INT8 : case FT_INT16 : case FT_INT24 : case FT_INT32 : is_signed_num = TRUE ;
 case FT_UINT8 : case FT_UINT16 : case FT_UINT24 : case FT_UINT32 : case FT_FRAMENUM : if ( filter != NULL ) {
 guint32 number ;
 char buf [ 32 ] ;
 const char * out ;
 if ( is_signed_num ) number = fvalue_get_sinteger ( & finfo -> value ) ;
 else number = fvalue_get_uinteger ( & finfo -> value ) ;
 out = hfinfo_numeric_value_format ( hfinfo , buf , number ) ;
 * filter = wmem_strdup_printf ( NULL , "%s == %s" , hfinfo -> abbrev , out ) ;
 }
 break ;
 case FT_INT40 : case FT_INT48 : case FT_INT56 : case FT_INT64 : is_signed_num = TRUE ;
 case FT_UINT40 : case FT_UINT48 : case FT_UINT56 : case FT_UINT64 : if ( filter != NULL ) {
 guint64 number ;
 char buf [ 48 ] ;
 const char * out ;
 if ( is_signed_num ) number = fvalue_get_sinteger64 ( & finfo -> value ) ;
 else number = fvalue_get_uinteger64 ( & finfo -> value ) ;
 out = hfinfo_numeric_value_format64 ( hfinfo , buf , number ) ;
 * filter = wmem_strdup_printf ( NULL , "%s == %s" , hfinfo -> abbrev , out ) ;
 }
 break ;
 case FT_PROTOCOL : if ( filter != NULL ) * filter = wmem_strdup ( NULL , finfo -> hfinfo -> abbrev ) ;
 break ;
 case FT_NONE : length = finfo -> length ;
 if ( length == 0 ) {
 if ( filter != NULL ) * filter = wmem_strdup ( NULL , finfo -> hfinfo -> abbrev ) ;
 break ;
 }
 if ( length < 0 ) return FALSE ;
 if ( edt == NULL ) return FALSE ;
 if ( finfo -> ds_tvb != edt -> tvb ) return FALSE ;
 length_remaining = tvb_captured_length_remaining ( finfo -> ds_tvb , finfo -> start ) ;
 if ( length > length_remaining ) length = length_remaining ;
 if ( length <= 0 ) return FALSE ;
 if ( filter != NULL ) {
 start = finfo -> start ;
 buf_len = 32 + length * 3 ;
 * filter = ( char * ) wmem_alloc0 ( NULL , buf_len ) ;
 ptr = * filter ;
 ptr += g_snprintf ( ptr , ( gulong ) ( buf_len - ( ptr - * filter ) ) , "frame[%d:%d] == " , finfo -> start , length ) ;
 for ( i = 0 ;
 i < length ;
 i ++ ) {
 c = tvb_get_guint8 ( finfo -> ds_tvb , start ) ;
 start ++ ;
 if ( i == 0 ) {
 ptr += g_snprintf ( ptr , ( gulong ) ( buf_len - ( ptr - * filter ) ) , "%02x" , c ) ;
 }
 else {
 ptr += g_snprintf ( ptr , ( gulong ) ( buf_len - ( ptr - * filter ) ) , ":%02x" , c ) ;
 }
 }
 }
 break ;
 case FT_PCRE : DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 break ;
 default : if ( filter != NULL ) {
 char * str ;
 dfilter_len = fvalue_string_repr_len ( & finfo -> value , FTREPR_DFILTER , finfo -> hfinfo -> display ) ;
 dfilter_len += abbrev_len + 4 + 1 ;
 * filter = ( char * ) wmem_alloc0 ( NULL , dfilter_len ) ;
 str = fvalue_to_string_repr ( NULL , & finfo -> value , FTREPR_DFILTER , finfo -> hfinfo -> display ) ;
 g_snprintf ( * filter , dfilter_len , "%s == %s" , hfinfo -> abbrev , str ) ;
 wmem_free ( NULL , str ) ;
 }
 break ;
 }
 return TRUE ;
 }