static void display_sorted_nicks ( CHANNEL_REC * channel , GSList * nicklist ) {
 WINDOW_REC * window ;
 TEXT_DEST_REC dest ;
 GString * str ;
 GSList * tmp ;
 char * format , * stripped , * prefix_format ;
 char * aligned_nick , nickmode [ 2 ] = {
 0 , 0 }
 ;
 int * columns , cols , rows , last_col_rows , col , row , max_width ;
 int item_extra , formatnum ;
 window = window_find_closest ( channel -> server , channel -> visible_name , MSGLEVEL_CLIENTCRAP ) ;
 max_width = window -> width ;
 format = format_get_text ( MODULE_NAME , NULL , channel -> server , channel -> visible_name , TXT_NAMES_NICK , " " , "" ) ;
 stripped = strip_codes ( format ) ;
 item_extra = strlen ( stripped ) ;
 g_free ( stripped ) ;
 g_free ( format ) ;
 if ( settings_get_int ( "names_max_width" ) > 0 && settings_get_int ( "names_max_width" ) < max_width ) max_width = settings_get_int ( "names_max_width" ) ;
 format_create_dest ( & dest , channel -> server , channel -> visible_name , MSGLEVEL_CLIENTCRAP , NULL ) ;
 format = format_get_line_start ( current_theme , & dest , time ( NULL ) ) ;
 if ( format != NULL ) {
 stripped = strip_codes ( format ) ;
 max_width -= strlen ( stripped ) ;
 g_free ( stripped ) ;
 g_free ( format ) ;
 }
 prefix_format = format_get_text ( MODULE_NAME , NULL , channel -> server , channel -> visible_name , TXT_NAMES_PREFIX , channel -> visible_name ) ;
 if ( prefix_format != NULL ) {
 stripped = strip_codes ( prefix_format ) ;
 max_width -= strlen ( stripped ) ;
 g_free ( stripped ) ;
 }
 if ( max_width <= 0 ) {
 max_width = 10 ;
 }
 cols = get_max_column_count ( nicklist , get_nick_length , max_width , settings_get_int ( "names_max_columns" ) , item_extra , 3 , & columns , & rows ) ;
 nicklist = columns_sort_list ( nicklist , rows ) ;
 last_col_rows = rows - ( cols * rows - g_slist_length ( nicklist ) ) ;
 if ( last_col_rows == 0 ) last_col_rows = rows ;
 str = g_string_new ( prefix_format ) ;
 col = 0 ;
 row = 0 ;
 for ( tmp = nicklist ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 NICK_REC * rec = tmp -> data ;
 if ( rec -> prefixes [ 0 ] ) nickmode [ 0 ] = rec -> prefixes [ 0 ] ;
 else nickmode [ 0 ] = ' ' ;
 aligned_nick = get_alignment ( rec -> nick , columns [ col ] - item_extra , ALIGN_PAD , ' ' ) ;
 formatnum = rec -> op ? TXT_NAMES_NICK_OP : rec -> halfop ? TXT_NAMES_NICK_HALFOP : rec -> voice ? TXT_NAMES_NICK_VOICE : TXT_NAMES_NICK ;
 format = format_get_text ( MODULE_NAME , NULL , channel -> server , channel -> visible_name , formatnum , nickmode , aligned_nick ) ;
 g_string_append ( str , format ) ;
 g_free ( aligned_nick ) ;
 g_free ( format ) ;
 if ( ++ col == cols ) {
 printtext ( channel -> server , channel -> visible_name , MSGLEVEL_CLIENTCRAP , "%s" , str -> str ) ;
 g_string_truncate ( str , 0 ) ;
 if ( prefix_format != NULL ) g_string_assign ( str , prefix_format ) ;
 col = 0 ;
 row ++ ;
 if ( row == last_col_rows ) cols -- ;
 }
 }
 if ( prefix_format != NULL && str -> len > strlen ( prefix_format ) ) {
 printtext ( channel -> server , channel -> visible_name , MSGLEVEL_CLIENTCRAP , "%s" , str -> str ) ;
 }
 g_slist_free ( nicklist ) ;
 g_string_free ( str , TRUE ) ;
 g_free_not_null ( columns ) ;
 g_free_not_null ( prefix_format ) ;
 }