static bool equivalent_locale ( int category , const char * loca , const char * locb ) {
 const char * chara ;
 const char * charb ;
 char * canona ;
 char * canonb ;
 int lena ;
 int lenb ;
 if ( pg_strcasecmp ( loca , locb ) == 0 ) return true ;
 canona = get_canonical_locale_name ( category , loca ) ;
 chara = strrchr ( canona , '.' ) ;
 lena = chara ? ( chara - canona ) : strlen ( canona ) ;
 canonb = get_canonical_locale_name ( category , locb ) ;
 charb = strrchr ( canonb , '.' ) ;
 lenb = charb ? ( charb - canonb ) : strlen ( canonb ) ;
 if ( lena == lenb && pg_strncasecmp ( canona , canonb , lena ) == 0 ) {
 pg_free ( canona ) ;
 pg_free ( canonb ) ;
 return true ;
 }
 pg_free ( canona ) ;
 pg_free ( canonb ) ;
 return false ;
 }