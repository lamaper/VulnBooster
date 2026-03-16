static size_t write_dns_nameenc ( char * buf , size_t buflen , char * data , int datalen , char downenc ) {
 static int td1 = 0 ;
 static int td2 = 0 ;
 size_t space ;
 char * b ;
 td1 += 3 ;
 td2 += 7 ;
 if ( td1 >= 26 ) td1 -= 26 ;
 if ( td2 >= 25 ) td2 -= 25 ;
 space = MIN ( 0xFF , buflen ) - 4 - 2 ;
 memset ( buf , 0 , buflen ) ;
 if ( downenc == 'S' ) {
 buf [ 0 ] = 'i' ;
 if ( ! b64 -> places_dots ( ) ) space -= ( space / 57 ) ;
 b64 -> encode ( buf + 1 , & space , data , datalen ) ;
 if ( ! b64 -> places_dots ( ) ) inline_dotify ( buf , buflen ) ;
 }
 else if ( downenc == 'U' ) {
 buf [ 0 ] = 'j' ;
 if ( ! b64u -> places_dots ( ) ) space -= ( space / 57 ) ;
 b64u -> encode ( buf + 1 , & space , data , datalen ) ;
 if ( ! b64u -> places_dots ( ) ) inline_dotify ( buf , buflen ) ;
 }
 else if ( downenc == 'V' ) {
 buf [ 0 ] = 'k' ;
 if ( ! b128 -> places_dots ( ) ) space -= ( space / 57 ) ;
 b128 -> encode ( buf + 1 , & space , data , datalen ) ;
 if ( ! b128 -> places_dots ( ) ) inline_dotify ( buf , buflen ) ;
 }
 else {
 buf [ 0 ] = 'h' ;
 if ( ! b32 -> places_dots ( ) ) space -= ( space / 57 ) ;
 b32 -> encode ( buf + 1 , & space , data , datalen ) ;
 if ( ! b32 -> places_dots ( ) ) inline_dotify ( buf , buflen ) ;
 }
 b = buf ;
 b += strlen ( buf ) - 1 ;
 if ( * b != '.' ) * ++ b = '.' ;
 b ++ ;
 * b = 'a' + td1 ;
 b ++ ;
 * b = 'a' + td2 ;
 b ++ ;
 * b = '\0' ;
 return space ;
 }