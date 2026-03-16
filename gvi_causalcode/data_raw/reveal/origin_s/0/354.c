static void free_deregistered_field ( gpointer data , gpointer user_data _U_ ) {
 header_field_info * hfi = ( header_field_info * ) data ;
 gint hf_id = hfi -> id ;
 g_free ( ( char * ) hfi -> name ) ;
 g_free ( ( char * ) hfi -> abbrev ) ;
 g_free ( ( char * ) hfi -> blurb ) ;
 if ( hfi -> strings ) {
 switch ( hfi -> type ) {
 case FT_FRAMENUM : break ;
 case FT_PROTOCOL : {
 protocol_t * protocol = ( protocol_t * ) hfi -> strings ;
 g_free ( ( gchar * ) protocol -> short_name ) ;
 break ;
 }
 case FT_BOOLEAN : {
 true_false_string * tf = ( true_false_string * ) hfi -> strings ;
 g_free ( ( gchar * ) tf -> true_string ) ;
 g_free ( ( gchar * ) tf -> false_string ) ;
 break ;
 }
 case FT_UINT64 : case FT_INT64 : {
 val64_string * vs64 = ( val64_string * ) hfi -> strings ;
 while ( vs64 -> strptr ) {
 g_free ( ( gchar * ) vs64 -> strptr ) ;
 vs64 ++ ;
 }
 break ;
 }
 default : {
 value_string * vs = ( value_string * ) hfi -> strings ;
 while ( vs -> strptr ) {
 g_free ( ( gchar * ) vs -> strptr ) ;
 vs ++ ;
 }
 break ;
 }
 }
 if ( hfi -> type != FT_FRAMENUM ) {
 g_free ( ( void * ) hfi -> strings ) ;
 }
 }
 if ( hfi -> parent == - 1 ) g_slice_free ( header_field_info , hfi ) ;
 gpa_hfinfo . hfi [ hf_id ] = NULL ;
 }