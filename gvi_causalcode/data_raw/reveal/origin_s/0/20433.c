static FILE * Needs816Enc ( SplineFont * sf , int * tlen , EncMap * map , FILE * * apple , int * appletlen ) {
 FILE * sub ;
 const char * encname = map -> enc -> iconv_name != NULL ? map -> enc -> iconv_name : map -> enc -> enc_name ;
 EncMap * oldmap = map ;
 EncMap * applemap = NULL ;
 Encoding * enc ;
 * tlen = 0 ;
 if ( apple != NULL ) {
 * apple = NULL ;
 * appletlen = 0 ;
 }
 if ( sf -> cidmaster != NULL || sf -> subfontcnt != 0 ) return ( NULL ) ;
 if ( ( strstrmatch ( encname , "big" ) != NULL && strchr ( encname , '5' ) != NULL ) || strstrmatch ( encname , "johab" ) != NULL || strstrmatch ( encname , "sjis" ) != NULL || strstrmatch ( encname , "cp932" ) != NULL || strstrmatch ( encname , "euc-kr" ) != NULL || strstrmatch ( encname , "euc-cn" ) != NULL ) ;
 else if ( strstrmatch ( encname , "2022" ) != NULL && ( strstrmatch ( encname , "JP2" ) != NULL || strstrmatch ( encname , "JP-2" ) != NULL || strstrmatch ( encname , "JP-3" ) != NULL ) ) return ( NULL ) ;
 else if ( sf -> uni_interp >= ui_japanese && sf -> uni_interp <= ui_korean ) {
 enc = FindOrMakeEncoding ( sf -> uni_interp == ui_japanese ? "sjis" : sf -> uni_interp == ui_trad_chinese ? "big5" : sf -> uni_interp == ui_simp_chinese ? "euc-cn" : "euc-kr" ) ;
 if ( map -> enc != enc ) {
 map = EncMapFromEncoding ( sf , enc ) ;
 encname = map -> enc -> iconv_name != NULL ? map -> enc -> iconv_name : map -> enc -> enc_name ;
 }
 }
 else return ( NULL ) ;
 if ( strstrmatch ( encname , "sjis" ) != NULL ) {
 enc = FindOrMakeEncoding ( "cp932" ) ;
 if ( enc != NULL ) {
 applemap = map ;
 map = EncMapFromEncoding ( sf , enc ) ;
 }
 }
 else if ( strstrmatch ( encname , "cp932" ) != NULL ) applemap = EncMapFromEncoding ( sf , FindOrMakeEncoding ( "sjis" ) ) ;
 if ( applemap != NULL ) * apple = _Gen816Enc ( sf , appletlen , applemap ) ;
 sub = _Gen816Enc ( sf , tlen , map ) ;
 if ( applemap != NULL && applemap != oldmap ) EncMapFree ( applemap ) ;
 if ( map != oldmap ) EncMapFree ( map ) ;
 return ( sub ) ;
 }