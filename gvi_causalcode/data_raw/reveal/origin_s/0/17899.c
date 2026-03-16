static const char * name ## _get_name ( void * ctx ) \ {
 return # name ;
 \ }
 static const AVClass name ## _class = {
 . class_name = # name , . item_name = name ## _get_name , . option = name ## _options \ }
 typedef struct DefaultContext {
 const AVClass * class ;
 int nokey ;
 int noprint_wrappers ;
 int nested_section [ SECTION_MAX_NB_LEVELS ] ;
 }
 DefaultContext ;

 {
 "noprint_wrappers" , "do not print headers and footers" , OFFSET ( noprint_wrappers ) , AV_OPT_TYPE_BOOL , {
 . i64 = 0 }
 , 0 , 1 }
 , {
 "nw" , "do not print headers and footers" , OFFSET ( noprint_wrappers ) , AV_OPT_TYPE_BOOL , {
 . i64 = 0 }
 , 0 , 1 }
 , {
 "nokey" , "force no key printing" , OFFSET ( nokey ) , AV_OPT_TYPE_BOOL , {
 . i64 = 0 }
 , 0 , 1 }
 , {
 "nk" , "force no key printing" , OFFSET ( nokey ) , AV_OPT_TYPE_BOOL , {
 . i64 = 0 }
 , 0 , 1 }
 , {
 NULL }
 , }
 ;
 DEFINE_WRITER_CLASS ( default ) ;
 static inline char * upcase_string ( char * dst , size_t dst_size , const char * src ) {
 int i ;
 for ( i = 0 ;
 src [ i ] && i < dst_size - 1 ;
 i ++ ) dst [ i ] = av_toupper ( src [ i ] ) ;
 dst [ i ] = 0 ;
 return dst ;
 }
 static void default_print_section_header ( WriterContext * wctx ) {
 DefaultContext * def = wctx -> priv ;
 char buf [ 32 ] ;
 const struct section * section = wctx -> section [ wctx -> level ] ;
 const struct section * parent_section = wctx -> level ? wctx -> section [ wctx -> level - 1 ] : NULL ;
 av_bprint_clear ( & wctx -> section_pbuf [ wctx -> level ] ) ;
 if ( parent_section && ! ( parent_section -> flags & ( SECTION_FLAG_IS_WRAPPER | SECTION_FLAG_IS_ARRAY ) ) ) {
 def -> nested_section [ wctx -> level ] = 1 ;
 av_bprintf ( & wctx -> section_pbuf [ wctx -> level ] , "%s%s:" , wctx -> section_pbuf [ wctx -> level - 1 ] . str , upcase_string ( buf , sizeof ( buf ) , av_x_if_null ( section -> element_name , section -> name ) ) ) ;
 }
 if ( def -> noprint_wrappers || def -> nested_section [ wctx -> level ] ) return ;
 if ( ! ( section -> flags & ( SECTION_FLAG_IS_WRAPPER | SECTION_FLAG_IS_ARRAY ) ) ) printf ( "[%s]\n" , upcase_string ( buf , sizeof ( buf ) , section -> name ) ) ;
 }
 static void default_print_section_footer ( WriterContext * wctx ) {
 DefaultContext * def = wctx -> priv ;
 const struct section * section = wctx -> section [ wctx -> level ] ;
 char buf [ 32 ] ;
 if ( def -> noprint_wrappers || def -> nested_section [ wctx -> level ] ) return ;
 if ( ! ( section -> flags & ( SECTION_FLAG_IS_WRAPPER | SECTION_FLAG_IS_ARRAY ) ) ) printf ( "[/%s]\n" , upcase_string ( buf , sizeof ( buf ) , section -> name ) ) ;
 }
 static void default_print_str ( WriterContext * wctx , const char * key , const char * value ) {
 DefaultContext * def = wctx -> priv ;
 if ( ! def -> nokey ) printf ( "%s%s=" , wctx -> section_pbuf [ wctx -> level ] . str , key ) ;
 printf ( "%s\n" , value ) ;
 }
 static void default_print_int ( WriterContext * wctx , const char * key , long long int value ) {
 DefaultContext * def = wctx -> priv ;
 if ( ! def -> nokey ) printf ( "%s%s=" , wctx -> section_pbuf [ wctx -> level ] . str , key ) ;
 printf ( "%lld\n" , value ) ;
 }
 static const Writer default_writer = {
 . name = "default" , . priv_size = sizeof ( DefaultContext ) , . print_section_header = default_print_section_header , . print_section_footer = default_print_section_footer , . print_integer = default_print_int , . print_string = default_print_str , . flags = WRITER_FLAG_DISPLAY_OPTIONAL_FIELDS , . priv_class = & default_class , }
 ;
 static const char * c_escape_str ( AVBPrint * dst , const char * src , const char sep , void * log_ctx ) {
 const char * p ;
 for ( p = src ;
 * p ;
 p ++ ) {
 switch ( * p ) {
 case '\b' : av_bprintf ( dst , "%s" , "\\b" ) ;
 break ;
 case '\f' : av_bprintf ( dst , "%s" , "\\f" ) ;
 break ;
 case '\n' : av_bprintf ( dst , "%s" , "\\n" ) ;
 break ;
 case '\r' : av_bprintf ( dst , "%s" , "\\r" ) ;
 break ;
 case '\\' : av_bprintf ( dst , "%s" , "\\\\" ) ;
 break ;
 default : if ( * p == sep ) av_bprint_chars ( dst , '\\' , 1 ) ;
 av_bprint_chars ( dst , * p , 1 ) ;
 }
 }
 return dst -> str ;
 }
 static const char * csv_escape_str ( AVBPrint * dst , const char * src , const char sep , void * log_ctx ) {
 char meta_chars [ ] = {
 sep , '"' , '\n' , '\r' , '\0' }
 ;
 int needs_quoting = ! ! src [ strcspn ( src , meta_chars ) ] ;
 if ( needs_quoting ) av_bprint_chars ( dst , '"' , 1 ) ;
 for ( ;
 * src ;
 src ++ ) {
 if ( * src == '"' ) av_bprint_chars ( dst , '"' , 1 ) ;
 av_bprint_chars ( dst , * src , 1 ) ;
 }
 if ( needs_quoting ) av_bprint_chars ( dst , '"' , 1 ) ;
 return dst -> str ;
 }
 static const char * none_escape_str ( AVBPrint * dst , const char * src , const char sep , void * log_ctx ) {
 return src ;
 }
 typedef struct CompactContext {
 const AVClass * class ;
 char * item_sep_str ;
 char item_sep ;
 int nokey ;
 int print_section ;
 char * escape_mode_str ;
 const char * ( * escape_str ) ( AVBPrint * dst , const char * src , const char sep , void * log_ctx ) ;
 int nested_section [ SECTION_MAX_NB_LEVELS ] ;
 int has_nested_elems [ SECTION_MAX_NB_LEVELS ] ;
 int terminate_line [ SECTION_MAX_NB_LEVELS ] ;
 }
 CompactContext ;

 {
 "item_sep" , "set item separator" , OFFSET ( item_sep_str ) , AV_OPT_TYPE_STRING , {
 . str = "|" }
 , CHAR_MIN , CHAR_MAX }
 , {
 "s" , "set item separator" , OFFSET ( item_sep_str ) , AV_OPT_TYPE_STRING , {
 . str = "|" }
 , CHAR_MIN , CHAR_MAX }
 , {
 "nokey" , "force no key printing" , OFFSET ( nokey ) , AV_OPT_TYPE_BOOL , {
 . i64 = 0 }
 , 0 , 1 }
 , {
 "nk" , "force no key printing" , OFFSET ( nokey ) , AV_OPT_TYPE_BOOL , {
 . i64 = 0 }
 , 0 , 1 }
 , {
 "escape" , "set escape mode" , OFFSET ( escape_mode_str ) , AV_OPT_TYPE_STRING , {
 . str = "c" }
 , CHAR_MIN , CHAR_MAX }
 , {
 "e" , "set escape mode" , OFFSET ( escape_mode_str ) , AV_OPT_TYPE_STRING , {
 . str = "c" }
 , CHAR_MIN , CHAR_MAX }
 , {
 "print_section" , "print section name" , OFFSET ( print_section ) , AV_OPT_TYPE_BOOL , {
 . i64 = 1 }
 , 0 , 1 }
 , {
 "p" , "print section name" , OFFSET ( print_section ) , AV_OPT_TYPE_BOOL , {
 . i64 = 1 }
 , 0 , 1 }
 , {
 NULL }
 , }
 ;
 DEFINE_WRITER_CLASS ( compact ) ;
 static av_cold int compact_init ( WriterContext * wctx ) {
 CompactContext * compact = wctx -> priv ;
 if ( strlen ( compact -> item_sep_str ) != 1 ) {
 av_log ( wctx , AV_LOG_ERROR , "Item separator '%s' specified, but must contain a single character\n" , compact -> item_sep_str ) ;
 return AVERROR ( EINVAL ) ;
 }
 compact -> item_sep = compact -> item_sep_str [ 0 ] ;
 if ( ! strcmp ( compact -> escape_mode_str , "none" ) ) compact -> escape_str = none_escape_str ;
 else if ( ! strcmp ( compact -> escape_mode_str , "c" ) ) compact -> escape_str = c_escape_str ;
 else if ( ! strcmp ( compact -> escape_mode_str , "csv" ) ) compact -> escape_str = csv_escape_str ;
 else {
 av_log ( wctx , AV_LOG_ERROR , "Unknown escape mode '%s'\n" , compact -> escape_mode_str ) ;
 return AVERROR ( EINVAL ) ;
 }
 return 0 ;
 }
 static void compact_print_section_header ( WriterContext * wctx ) {
 CompactContext * compact = wctx -> priv ;
 const struct section * section = wctx -> section [ wctx -> level ] ;
 const struct section * parent_section = wctx -> level ? wctx -> section [ wctx -> level - 1 ] : NULL ;
 compact -> terminate_line [ wctx -> level ] = 1 ;
 compact -> has_nested_elems [ wctx -> level ] = 0 ;
 av_bprint_clear ( & wctx -> section_pbuf [ wctx -> level ] ) ;
 if ( ! ( section -> flags & SECTION_FLAG_IS_ARRAY ) && parent_section && ! ( parent_section -> flags & ( SECTION_FLAG_IS_WRAPPER | SECTION_FLAG_IS_ARRAY ) ) ) {
 compact -> nested_section [ wctx -> level ] = 1 ;
 compact -> has_nested_elems [ wctx -> level - 1 ] = 1 ;
 av_bprintf ( & wctx -> section_pbuf [ wctx -> level ] , "%s%s:" , wctx -> section_pbuf [ wctx -> level - 1 ] . str , ( char * ) av_x_if_null ( section -> element_name , section -> name ) ) ;
 wctx -> nb_item [ wctx -> level ] = wctx -> nb_item [ wctx -> level - 1 ] ;
 }
 else {
 if ( parent_section && compact -> has_nested_elems [ wctx -> level - 1 ] && ( section -> flags & SECTION_FLAG_IS_ARRAY ) ) {
 compact -> terminate_line [ wctx -> level - 1 ] = 0 ;
 printf ( "\n" ) ;
 }
 if ( compact -> print_section && ! ( section -> flags & ( SECTION_FLAG_IS_WRAPPER | SECTION_FLAG_IS_ARRAY ) ) ) printf ( "%s%c" , section -> name , compact -> item_sep ) ;
 }
 }
 static void compact_print_section_footer ( WriterContext * wctx ) {
 CompactContext * compact = wctx -> priv ;
 if ( ! compact -> nested_section [ wctx -> level ] && compact -> terminate_line [ wctx -> level ] && ! ( wctx -> section [ wctx -> level ] -> flags & ( SECTION_FLAG_IS_WRAPPER | SECTION_FLAG_IS_ARRAY ) ) ) printf ( "\n" ) ;
 }
 static void compact_print_str ( WriterContext * wctx , const char * key , const char * value ) {
 CompactContext * compact = wctx -> priv ;
 AVBPrint buf ;
 if ( wctx -> nb_item [ wctx -> level ] ) printf ( "%c" , compact -> item_sep ) ;
 if ( ! compact -> nokey ) printf ( "%s%s=" , wctx -> section_pbuf [ wctx -> level ] . str , key ) ;
 av_bprint_init ( & buf , 1 , AV_BPRINT_SIZE_UNLIMITED ) ;
 printf ( "%s" , compact -> escape_str ( & buf , value , compact -> item_sep , wctx ) ) ;
 av_bprint_finalize ( & buf , NULL ) ;
 }
 static void compact_print_int ( WriterContext * wctx , const char * key , long long int value ) {
 CompactContext * compact = wctx -> priv ;
 if ( wctx -> nb_item [ wctx -> level ] ) printf ( "%c" , compact -> item_sep ) ;
 if ( ! compact -> nokey ) printf ( "%s%s=" , wctx -> section_pbuf [ wctx -> level ] . str , key ) ;
 printf ( "%lld" , value ) ;
 }
 static const Writer compact_writer = {
 . name = "compact" , . priv_size = sizeof ( CompactContext ) , . init = compact_init , . print_section_header = compact_print_section_header , . print_section_footer = compact_print_section_footer , . print_integer = compact_print_int , . print_string = compact_print_str , . flags = WRITER_FLAG_DISPLAY_OPTIONAL_FIELDS , . priv_class = & compact_class , }
 ;

 {
 "item_sep" , "set item separator" , OFFSET ( item_sep_str ) , AV_OPT_TYPE_STRING , {
 . str = "," }
 , CHAR_MIN , CHAR_MAX }
 , {
 "s" , "set item separator" , OFFSET ( item_sep_str ) , AV_OPT_TYPE_STRING , {
 . str = "," }
 , CHAR_MIN , CHAR_MAX }
 , {
 "nokey" , "force no key printing" , OFFSET ( nokey ) , AV_OPT_TYPE_BOOL , {
 . i64 = 1 }
 , 0 , 1 }
 , {
 "nk" , "force no key printing" , OFFSET ( nokey ) , AV_OPT_TYPE_BOOL , {
 . i64 = 1 }
 , 0 , 1 }
 , {
 "escape" , "set escape mode" , OFFSET ( escape_mode_str ) , AV_OPT_TYPE_STRING , {
 . str = "csv" }
 , CHAR_MIN , CHAR_MAX }
 , {
 "e" , "set escape mode" , OFFSET ( escape_mode_str ) , AV_OPT_TYPE_STRING , {
 . str = "csv" }
 , CHAR_MIN , CHAR_MAX }
 , {
 "print_section" , "print section name" , OFFSET ( print_section ) , AV_OPT_TYPE_BOOL , {
 . i64 = 1 }
 , 0 , 1 }
 , {
 "p" , "print section name" , OFFSET ( print_section ) , AV_OPT_TYPE_BOOL , {
 . i64 = 1 }
 , 0 , 1 }
 , {
 NULL }
 , }
 ;
 DEFINE_WRITER_CLASS ( csv ) ;
 static const Writer csv_writer = {
 . name = "csv" , . priv_size = sizeof ( CompactContext ) , . init = compact_init , . print_section_header = compact_print_section_header , . print_section_footer = compact_print_section_footer , . print_integer = compact_print_int , . print_string = compact_print_str , . flags = WRITER_FLAG_DISPLAY_OPTIONAL_FIELDS , . priv_class = & csv_class , }
 ;
 typedef struct FlatContext {
 const AVClass * class ;
 const char * sep_str ;
 char sep ;
 int hierarchical ;
 }
 FlatContext ;

 {
 "sep_char" , "set separator" , OFFSET ( sep_str ) , AV_OPT_TYPE_STRING , {
 . str = "." }
 , CHAR_MIN , CHAR_MAX }
 , {
 "s" , "set separator" , OFFSET ( sep_str ) , AV_OPT_TYPE_STRING , {
 . str = "." }
 , CHAR_MIN , CHAR_MAX }
 , {
 "hierarchical" , "specify if the section specification should be hierarchical" , OFFSET ( hierarchical ) , AV_OPT_TYPE_BOOL , {
 . i64 = 1 }
 , 0 , 1 }
 , {
 "h" , "specify if the section specification should be hierarchical" , OFFSET ( hierarchical ) , AV_OPT_TYPE_BOOL , {
 . i64 = 1 }
 , 0 , 1 }
 , {
 NULL }
 , }
 ;
 DEFINE_WRITER_CLASS ( flat )