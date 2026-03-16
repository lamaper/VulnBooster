static void label_mark_truncated ( char * label_str , gsize name_pos ) {
 static const char trunc_str [ ] = " [truncated]" ;
 const size_t trunc_len = sizeof ( trunc_str ) - 1 ;
 gchar * last_char ;
 if ( name_pos < ITEM_LABEL_LENGTH - trunc_len ) {
 memmove ( label_str + name_pos + trunc_len , label_str + name_pos , ITEM_LABEL_LENGTH - name_pos - trunc_len ) ;
 memcpy ( label_str + name_pos , trunc_str , trunc_len ) ;
 last_char = g_utf8_prev_char ( & label_str [ ITEM_LABEL_LENGTH ] ) ;
 * last_char = '\0' ;
 }
 else if ( name_pos < ITEM_LABEL_LENGTH ) g_strlcpy ( label_str + name_pos , trunc_str , ITEM_LABEL_LENGTH - name_pos ) ;
 }