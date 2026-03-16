static void AddEncodedName ( NamTab * nt , char * utf8name , uint16 lang , uint16 strid ) {
 NameEntry * ne ;
 int maclang , macenc = - 1 , specific ;
 char * macname = NULL ;
 if ( strid == ttf_postscriptname && lang != 0x409 ) return ;
 if ( nt -> cur + 6 >= nt -> max ) {
 if ( nt -> cur == 0 ) nt -> entries = malloc ( ( nt -> max = 100 ) * sizeof ( NameEntry ) ) ;
 else nt -> entries = realloc ( nt -> entries , ( nt -> max += 100 ) * sizeof ( NameEntry ) ) ;
 }
 ne = nt -> entries + nt -> cur ;
 ne -> platform = 3 ;
 ne -> specific = 1 ;
 ne -> lang = lang ;
 ne -> strid = strid ;
 ne -> offset = ftell ( nt -> strings ) ;
 ne -> len = 2 * utf82u_strlen ( utf8name ) ;
 dumpustr ( nt -> strings , utf8name ) ;
 ++ ne ;
 if ( nt -> format == ff_ttfsym ) {
 * ne = ne [ - 1 ] ;
 ne -> specific = 0 ;
 ++ ne ;
 }
 maclang = WinLangToMac ( lang ) ;
 if ( ! nt -> applemode && lang != 0x409 ) maclang = 0xffff ;
 if ( maclang != 0xffff ) {

 * ne = ne [ - 1 ] ;
 ne -> platform = 0 ;
 ne -> specific = 0 ;
 ne -> lang = maclang ;
 ++ ne ;
 }

 macname = Utf8ToMacStr ( utf8name , macenc , maclang ) ;
 if ( macname != NULL ) {
 ne -> platform = 1 ;
 ne -> specific = macenc ;
 ne -> lang = maclang ;
 ne -> strid = strid ;
 ne -> offset = ftell ( nt -> strings ) ;
 ne -> len = strlen ( macname ) ;
 dumpstr ( nt -> strings , macname ) ;
 ++ ne ;
 free ( macname ) ;
 }
 }
 specific = nt -> encoding_name -> is_korean ? 5 : nt -> encoding_name -> is_japanese ? 2 : nt -> encoding_name -> is_simplechinese ? 3 : strmatch ( nt -> encoding_name -> enc_name , "EUC-GB12345" ) == 0 ? 3 : nt -> encoding_name -> is_tradchinese ? 4 : - 1 ;
 if ( specific != - 1 ) {
 ne -> platform = 3 ;
 ne -> specific = specific ;
 ne -> lang = lang ;
 ne -> strid = strid ;
 if ( macname != NULL && ( ( specific == 2 && macenc == 1 ) || ( specific == 3 && macenc == 25 ) || ( specific == 4 && macenc == 2 ) || ( specific == 5 && macenc == 3 ) ) ) {
 ne -> offset = ne [ - 1 ] . offset ;
 ne -> len = ne [ - 1 ] . len ;
 }
 else {
 char * space , * out ;
 const char * encname ;
 ICONV_CONST char * in ;
 Encoding * enc ;
 size_t inlen , outlen ;
 ne -> offset = ftell ( nt -> strings ) ;
 encname = nt -> encoding_name -> is_japanese ? "SJIS" : strmatch ( nt -> encoding_name -> enc_name , "JOHAB" ) == 0 ? "JOHAB" : nt -> encoding_name -> is_korean ? "EUC-KR" : nt -> encoding_name -> is_simplechinese ? "EUC-CN" : nt -> encoding_name -> enc_name ;
 enc = FindOrMakeEncoding ( encname ) ;
 if ( enc == NULL ) -- ne ;
 else {
 unichar_t * uin = utf82u_copy ( utf8name ) ;
 outlen = 3 * strlen ( utf8name ) + 10 ;
 out = space = malloc ( outlen + 2 ) ;
 in = ( char * ) uin ;
 inlen = 2 * u_strlen ( uin ) ;
 iconv ( enc -> fromunicode , NULL , NULL , NULL , NULL ) ;
 iconv ( enc -> fromunicode , & in , & inlen , & out , & outlen ) ;
 out [ 0 ] = '\0' ;
 out [ 1 ] = '\0' ;
 ne -> offset = ftell ( nt -> strings ) ;
 ne -> len = strlen ( space ) ;
 dumpstr ( nt -> strings , space ) ;
 free ( space ) ;
 free ( uin ) ;
 }
 }
 ++ ne ;
 }
 nt -> cur = ne - nt -> entries ;
 }