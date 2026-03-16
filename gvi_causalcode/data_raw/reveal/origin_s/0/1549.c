static FILE * _Gen816Enc ( SplineFont * sf , int * tlen , EncMap * map ) {
 int i , j , complained , pos , k , subheadindex , jj , isbig5 = false ;
 uint16 table [ 256 ] ;
 struct subhead subheads [ 128 ] ;
 uint16 * glyphs ;
 uint16 tempglyphs [ 256 ] ;
 int base , lbase , basebound , subheadcnt , planesize , plane0size ;
 int base2 , base2bound ;
 FILE * sub ;
 const char * encname = map -> enc -> iconv_name != NULL ? map -> enc -> iconv_name : map -> enc -> enc_name ;
 * tlen = 0 ;
 base2 = - 1 ;
 base2bound = - 2 ;
 if ( map -> enc -> is_tradchinese && strstrmatch ( encname , "hkscs" ) != NULL ) {
 base = 0x81 ;
 basebound = 0xfe ;
 subheadcnt = basebound - base + 1 ;
 lbase = 0x40 ;
 planesize = 191 ;
 }
 else if ( map -> enc -> is_tradchinese || sf -> uni_interp == ui_trad_chinese ) {
 base = 0xa1 ;
 basebound = 0xf9 ;
 subheadcnt = basebound - base + 1 ;
 lbase = 0x40 ;
 planesize = 191 ;
 isbig5 = true ;
 }
 else if ( strstrmatch ( encname , "euc" ) != NULL ) {
 base = 0xa1 ;
 basebound = 0xfd ;
 lbase = 0xa1 ;
 subheadcnt = basebound - base + 1 ;
 planesize = 0xfe - lbase + 1 ;
 }
 else if ( strstrmatch ( encname , "johab" ) != NULL ) {
 base = 0x84 ;
 basebound = 0xf9 ;
 lbase = 0x31 ;
 subheadcnt = basebound - base + 1 ;
 planesize = 0xfe - 0x31 + 1 ;
 }
 else if ( strstrmatch ( encname , "sjis" ) != NULL || strstrmatch ( encname , "cp932" ) != NULL ) {
 base = 129 ;
 basebound = 159 ;
 lbase = 64 ;
 planesize = 252 - lbase + 1 ;
 base2 = 0xe0 ;
 for ( base2bound = 0xfc00 ;
 base2bound > 0xefff ;
 -- base2bound ) if ( base2bound < map -> enccount && map -> map [ base2bound ] != - 1 && SCWorthOutputting ( sf -> glyphs [ map -> map [ base2bound ] ] ) ) break ;
 base2bound >>= 8 ;
 subheadcnt = basebound - base + 1 + base2bound - base2 + 1 ;
 }
 else {
 IError ( "Unsupported 8/16 encoding %s\n" , map -> enc -> enc_name ) ;
 return ( NULL ) ;
 }
 plane0size = base2 == - 1 ? base : base2 ;
 i = 0 ;
 if ( base2 != - 1 ) {
 for ( i = basebound ;
 i < base2 && i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] == - 1 ) continue ;
 else if ( SCWorthOutputting ( sf -> glyphs [ map -> map [ i ] ] ) ) break ;
 if ( i == base2 || i == map -> enccount ) i = 0 ;
 }
 if ( i == 0 ) {
 for ( i = 0 ;
 i < base && i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] == - 1 ) continue ;
 else if ( SCWorthOutputting ( sf -> glyphs [ map -> map [ i ] ] ) ) break ;
 }
 if ( base2 != - 1 ) {
 for ( i = base ;
 i <= basebound && i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] != - 1 && SCWorthOutputting ( sf -> glyphs [ map -> map [ i ] ] ) ) {
 ff_post_error ( _ ( "Bad Encoding" ) , _ ( "There is a single byte character (%d) using one of the slots needed for double byte characters" ) , i ) ;
 break ;
 }
 if ( i == basebound + 1 ) for ( i = base2 ;
 i < 256 && i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] != - 1 && SCWorthOutputting ( sf -> glyphs [ map -> map [ i ] ] ) ) {
 ff_post_error ( _ ( "Bad Encoding" ) , _ ( "There is a single byte character (%d) using one of the slots needed for double byte characters" ) , i ) ;
 break ;
 }
 }
 else {
 for ( i = base ;
 i <= 256 && i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] != - 1 && SCWorthOutputting ( sf -> glyphs [ map -> map [ i ] ] ) ) {
 ff_post_error ( _ ( "Bad Encoding" ) , _ ( "There is a single byte character (%d) using one of the slots needed for double byte characters" ) , i ) ;
 break ;
 }
 }
 for ( i = 256 ;
 i < ( base << 8 ) && i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] != - 1 && SCWorthOutputting ( sf -> glyphs [ map -> map [ i ] ] ) ) {
 ff_post_error ( _ ( "Bad Encoding" ) , _ ( "There is a character (%d) which cannot be encoded" ) , i ) ;
 break ;
 }
 if ( i == ( base << 8 ) && base2 == - 1 ) for ( i = ( ( basebound + 1 ) << 8 ) ;
 i < 0x10000 && i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] != - 1 && SCWorthOutputting ( sf -> glyphs [ map -> map [ i ] ] ) ) {
 ff_post_error ( _ ( "Bad Encoding" ) , _ ( "There is a character (%d) which cannot be encoded" ) , i ) ;
 break ;
 }
 memset ( table , '\0' , sizeof ( table ) ) ;
 for ( i = base ;
 i <= basebound ;
 ++ i ) table [ i ] = 8 * ( i - base + 1 ) ;
 for ( i = base2 ;
 i <= base2bound ;
 ++ i ) table [ i ] = 8 * ( i - base2 + basebound - base + 1 + 1 ) ;
 memset ( subheads , '\0' , sizeof ( subheads ) ) ;
 subheads [ 0 ] . first = 0 ;
 subheads [ 0 ] . cnt = plane0size ;
 for ( i = 1 ;
 i < subheadcnt + 1 ;
 ++ i ) {
 subheads [ i ] . first = lbase ;
 subheads [ i ] . cnt = planesize ;
 }
 glyphs = calloc ( subheadcnt * planesize + plane0size , sizeof ( uint16 ) ) ;
 subheads [ 0 ] . rangeoff = 0 ;
 for ( i = 0 ;
 i < plane0size && i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] != - 1 && sf -> glyphs [ map -> map [ i ] ] != NULL && sf -> glyphs [ map -> map [ i ] ] -> ttf_glyph != - 1 ) glyphs [ i ] = sf -> glyphs [ map -> map [ i ] ] -> ttf_glyph ;
 pos = 1 ;
 complained = false ;
 subheadindex = 1 ;
 for ( jj = 0 ;
 jj < 2 || ( base2 == - 1 && jj < 1 ) ;
 ++ jj ) for ( j = ( ( jj == 0 ? base : base2 ) << 8 ) ;
 j <= ( ( jj == 0 ? basebound : base2bound ) << 8 ) ;
 j += 0x100 ) {
 for ( i = 0 ;
 i < lbase ;
 ++ i ) if ( ! complained && map -> map [ i + j ] != - 1 && SCWorthOutputting ( sf -> glyphs [ map -> map [ i + j ] ] ) ) {
 ff_post_error ( _ ( "Bad Encoding" ) , _ ( "There is a character (%d) which is not normally in the encoding" ) , i + j ) ;
 complained = true ;
 }
 if ( isbig5 ) {
 for ( i = 0x7f ;
 i < 0xa1 ;
 ++ i ) if ( ! complained && map -> map [ i + j ] != - 1 && SCWorthOutputting ( sf -> glyphs [ map -> map [ i + j ] ] ) ) {
 ff_post_error ( _ ( "Bad Encoding" ) , _ ( "There is a character (%d) which is not normally in the encoding" ) , i + j ) ;
 complained = true ;
 }
 }
 memset ( tempglyphs , 0 , sizeof ( tempglyphs ) ) ;
 for ( i = 0 ;
 i < planesize ;
 ++ i ) if ( map -> map [ j + lbase + i ] != - 1 && sf -> glyphs [ map -> map [ j + lbase + i ] ] != NULL && sf -> glyphs [ map -> map [ j + lbase + i ] ] -> ttf_glyph != - 1 ) tempglyphs [ i ] = sf -> glyphs [ map -> map [ j + lbase + i ] ] -> ttf_glyph ;
 for ( i = 1 ;
 i < pos ;
 ++ i ) {
 int delta = 0 ;
 for ( k = 0 ;
 k < planesize ;
 ++ k ) if ( tempglyphs [ k ] == 0 && glyphs [ plane0size + ( i - 1 ) * planesize + k ] == 0 ) ;
 else if ( tempglyphs [ k ] == 0 || glyphs [ plane0size + ( i - 1 ) * planesize + k ] == 0 ) break ;
 else if ( delta == 0 ) delta = ( uint16 ) ( tempglyphs [ k ] - glyphs [ plane0size + ( i - 1 ) * planesize + k ] ) ;
 else if ( tempglyphs [ k ] == ( uint16 ) ( glyphs [ plane0size + ( i - 1 ) * planesize + k ] + delta ) ) ;
 else break ;
 if ( k == planesize ) {
 subheads [ subheadindex ] . delta = delta ;
 subheads [ subheadindex ] . rangeoff = plane0size + ( i - 1 ) * planesize ;
 break ;
 }
 }
 if ( subheads [ subheadindex ] . rangeoff == 0 ) {
 memcpy ( glyphs + ( pos - 1 ) * planesize + plane0size , tempglyphs , planesize * sizeof ( uint16 ) ) ;
 subheads [ subheadindex ] . rangeoff = plane0size + ( pos ++ - 1 ) * planesize ;
 }
 ++ subheadindex ;
 }
 for ( i = 0 ;
 i < subheadcnt + 1 ;
 ++ i ) subheads [ i ] . rangeoff = subheads [ i ] . rangeoff * sizeof ( uint16 ) + ( subheadcnt - i ) * sizeof ( struct subhead ) + sizeof ( uint16 ) ;
 sub = tmpfile ( ) ;
 if ( sub == NULL ) return ( NULL ) ;
 putshort ( sub , 2 ) ;
 putshort ( sub , 0 ) ;
 putshort ( sub , 0 ) ;
 for ( i = 0 ;
 i < 256 ;
 ++ i ) putshort ( sub , table [ i ] ) ;
 for ( i = 0 ;
 i < subheadcnt + 1 ;
 ++ i ) {
 putshort ( sub , subheads [ i ] . first ) ;
 putshort ( sub , subheads [ i ] . cnt ) ;
 putshort ( sub , subheads [ i ] . delta ) ;
 putshort ( sub , subheads [ i ] . rangeoff ) ;
 }
 for ( i = 0 ;
 i < ( pos - 1 ) * planesize + plane0size ;
 ++ i ) putshort ( sub , glyphs [ i ] ) ;
 free ( glyphs ) ;
 * tlen = ftell ( sub ) ;
 fseek ( sub , 2 , SEEK_SET ) ;
 putshort ( sub , * tlen ) ;
 rewind ( sub ) ;
 return ( sub ) ;
 }