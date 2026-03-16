static FT_Error cid_parse_dict ( CID_Face face , CID_Loader * loader , FT_Byte * base , FT_Long size ) {
 CID_Parser * parser = & loader -> parser ;
 parser -> root . cursor = base ;
 parser -> root . limit = base + size ;
 parser -> root . error = FT_Err_Ok ;
 {
 FT_Byte * cur = base ;
 FT_Byte * limit = cur + size ;
 for ( ;
 ;
 ) {
 FT_Byte * newlimit ;
 parser -> root . cursor = cur ;
 cid_parser_skip_spaces ( parser ) ;
 if ( parser -> root . cursor >= limit ) newlimit = limit - 1 - 17 ;
 else newlimit = parser -> root . cursor - 17 ;
 for ( ;
 cur < newlimit ;
 cur ++ ) {
 if ( * cur == '%' && ft_strncmp ( ( char * ) cur , "%ADOBeginFontDict" , 17 ) == 0 ) {
 if ( face -> cid . num_dicts > 0 ) parser -> num_dict ++ ;
 }
 }
 cur = parser -> root . cursor ;
 if ( cur >= limit ) break ;
 cid_parser_skip_PS_token ( parser ) ;
 if ( parser -> root . cursor >= limit || parser -> root . error ) break ;
 if ( * cur == '/' && cur + 2 < limit ) {
 FT_PtrDist len ;
 cur ++ ;
 len = parser -> root . cursor - cur ;
 if ( len > 0 && len < 22 ) {
 T1_Field keyword = ( T1_Field ) cid_field_records ;
 for ( ;
 ;
 ) {
 FT_Byte * name ;
 name = ( FT_Byte * ) keyword -> ident ;
 if ( ! name ) break ;
 if ( cur [ 0 ] == name [ 0 ] && len == ( FT_PtrDist ) ft_strlen ( ( const char * ) name ) ) {
 FT_PtrDist n ;
 for ( n = 1 ;
 n < len ;
 n ++ ) if ( cur [ n ] != name [ n ] ) break ;
 if ( n >= len ) {
 parser -> root . error = cid_load_keyword ( face , loader , keyword ) ;
 if ( parser -> root . error ) return parser -> root . error ;
 break ;
 }
 }
 keyword ++ ;
 }
 }
 }
 cur = parser -> root . cursor ;
 }
 }
 return parser -> root . error ;
 }