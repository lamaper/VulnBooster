static int archive_string_normalize_C ( struct archive_string * as , const void * _p , size_t len , struct archive_string_conv * sc ) {
 const char * s = ( const char * ) _p ;
 char * p , * endp ;
 uint32_t uc , uc2 ;
 size_t w ;
 int always_replace , n , n2 , ret = 0 , spair , ts , tm ;
 int ( * parse ) ( uint32_t * , const char * , size_t ) ;
 size_t ( * unparse ) ( char * , size_t , uint32_t ) ;
 always_replace = 1 ;
 ts = 1 ;
 if ( sc -> flag & SCONV_TO_UTF16BE ) {
 unparse = unicode_to_utf16be ;
 ts = 2 ;
 if ( sc -> flag & SCONV_FROM_UTF16BE ) always_replace = 0 ;
 }
 else if ( sc -> flag & SCONV_TO_UTF16LE ) {
 unparse = unicode_to_utf16le ;
 ts = 2 ;
 if ( sc -> flag & SCONV_FROM_UTF16LE ) always_replace = 0 ;
 }
 else if ( sc -> flag & SCONV_TO_UTF8 ) {
 unparse = unicode_to_utf8 ;
 if ( sc -> flag & SCONV_FROM_UTF8 ) always_replace = 0 ;
 }
 else {
 always_replace = 0 ;
 if ( sc -> flag & SCONV_FROM_UTF16BE ) {
 unparse = unicode_to_utf16be ;
 ts = 2 ;
 }
 else if ( sc -> flag & SCONV_FROM_UTF16LE ) {
 unparse = unicode_to_utf16le ;
 ts = 2 ;
 }
 else {
 unparse = unicode_to_utf8 ;
 }
 }
 if ( sc -> flag & SCONV_FROM_UTF16BE ) {
 parse = utf16be_to_unicode ;
 tm = 1 ;
 spair = 4 ;
 }
 else if ( sc -> flag & SCONV_FROM_UTF16LE ) {
 parse = utf16le_to_unicode ;
 tm = 1 ;
 spair = 4 ;
 }
 else {
 parse = cesu8_to_unicode ;
 tm = ts ;
 spair = 6 ;
 }
 if ( archive_string_ensure ( as , as -> length + len * tm + ts ) == NULL ) return ( - 1 ) ;
 p = as -> s + as -> length ;
 endp = as -> s + as -> buffer_length - ts ;
 while ( ( n = parse ( & uc , s , len ) ) != 0 ) {
 const char * ucptr , * uc2ptr ;
 if ( n < 0 ) {
 UNPARSE ( p , endp , uc ) ;
 s += n * - 1 ;
 len -= n * - 1 ;
 ret = - 1 ;
 continue ;
 }
 else if ( n == spair || always_replace ) ucptr = NULL ;
 else ucptr = s ;
 s += n ;
 len -= n ;
 while ( ( n2 = parse ( & uc2 , s , len ) ) > 0 ) {
 uint32_t ucx [ FDC_MAX ] ;
 int ccx [ FDC_MAX ] ;
 int cl , cx , i , nx , ucx_size ;
 int LIndex , SIndex ;
 uint32_t nfc ;
 if ( n2 == spair || always_replace ) uc2ptr = NULL ;
 else uc2ptr = s ;
 s += n2 ;
 len -= n2 ;
 if ( ! IS_DECOMPOSABLE_BLOCK ( uc2 ) ) {
 WRITE_UC ( ) ;
 REPLACE_UC_WITH_UC2 ( ) ;
 continue ;
 }
 if ( 0 <= ( LIndex = uc - HC_LBASE ) && LIndex < HC_LCOUNT ) {
 int VIndex = uc2 - HC_VBASE ;
 if ( 0 <= VIndex && VIndex < HC_VCOUNT ) {
 UPDATE_UC ( HC_SBASE + ( LIndex * HC_VCOUNT + VIndex ) * HC_TCOUNT ) ;
 }
 else {
 WRITE_UC ( ) ;
 REPLACE_UC_WITH_UC2 ( ) ;
 }
 continue ;
 }
 else if ( 0 <= ( SIndex = uc - HC_SBASE ) && SIndex < HC_SCOUNT && ( SIndex % HC_TCOUNT ) == 0 ) {
 int TIndex = uc2 - HC_TBASE ;
 if ( 0 < TIndex && TIndex < HC_TCOUNT ) {
 UPDATE_UC ( uc + TIndex ) ;
 }
 else {
 WRITE_UC ( ) ;
 REPLACE_UC_WITH_UC2 ( ) ;
 }
 continue ;
 }
 else if ( ( nfc = get_nfc ( uc , uc2 ) ) != 0 ) {
 UPDATE_UC ( nfc ) ;
 continue ;
 }
 else if ( ( cl = CCC ( uc2 ) ) == 0 ) {
 WRITE_UC ( ) ;
 REPLACE_UC_WITH_UC2 ( ) ;
 continue ;
 }
 cx = 0 ;
 ucx [ 0 ] = uc2 ;
 ccx [ 0 ] = cl ;
 COLLECT_CPS ( 1 ) ;
 i = 1 ;
 while ( i < ucx_size ) {
 int j ;
 if ( ( nfc = get_nfc ( uc , ucx [ i ] ) ) == 0 ) {
 i ++ ;
 continue ;
 }
 UPDATE_UC ( nfc ) ;
 for ( j = i ;
 j + 1 < ucx_size ;
 j ++ ) {
 ucx [ j ] = ucx [ j + 1 ] ;
 ccx [ j ] = ccx [ j + 1 ] ;
 }
 ucx_size -- ;
 if ( ucx_size > 0 && i == ucx_size && nx > 0 && cx == cl ) {
 cl = ccx [ ucx_size - 1 ] ;
 COLLECT_CPS ( ucx_size ) ;
 }
 i = 0 ;
 }
 WRITE_UC ( ) ;
 for ( i = 0 ;
 i < ucx_size ;
 i ++ ) UNPARSE ( p , endp , ucx [ i ] ) ;
 if ( nx > 0 && cx == cl && len > 0 ) {
 while ( ( nx = parse ( & ucx [ 0 ] , s , len ) ) > 0 ) {
 cx = CCC ( ucx [ 0 ] ) ;
 if ( cl > cx ) break ;
 s += nx ;
 len -= nx ;
 cl = cx ;
 UNPARSE ( p , endp , ucx [ 0 ] ) ;
 }
 }
 break ;
 }
 if ( n2 < 0 ) {
 WRITE_UC ( ) ;
 UNPARSE ( p , endp , uc2 ) ;
 s += n2 * - 1 ;
 len -= n2 * - 1 ;
 ret = - 1 ;
 continue ;
 }
 else if ( n2 == 0 ) {
 WRITE_UC ( ) ;
 break ;
 }
 }
 as -> length = p - as -> s ;
 as -> s [ as -> length ] = '\0' ;
 if ( ts == 2 ) as -> s [ as -> length + 1 ] = '\0' ;
 return ( ret ) ;
 }