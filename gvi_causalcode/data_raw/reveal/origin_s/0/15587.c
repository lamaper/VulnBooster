hb_language_t hb_ot_tag_to_language ( hb_tag_t tag ) {
 unsigned int i ;
 if ( tag == HB_OT_TAG_DEFAULT_LANGUAGE ) return NULL ;
 for ( i = 0 ;
 i < ARRAY_LENGTH ( ot_languages ) ;
 i ++ ) if ( ot_languages [ i ] . tag == tag ) return hb_language_from_string ( ot_languages [ i ] . language , - 1 ) ;
 if ( ( tag & 0xFFFF0000u ) == 0x5A480000u ) {
 switch ( tag ) {
 case HB_TAG ( 'Z' , 'H' , 'H' , ' ' ) : return hb_language_from_string ( "zh-hk" , - 1 ) ;
 case HB_TAG ( 'Z' , 'H' , 'S' , ' ' ) : return hb_language_from_string ( "zh-Hans" , - 1 ) ;
 case HB_TAG ( 'Z' , 'H' , 'T' , ' ' ) : return hb_language_from_string ( "zh-Hant" , - 1 ) ;
 default : break ;
 }
 }
 {
 unsigned char buf [ 11 ] = "x-hbot" ;
 buf [ 6 ] = tag >> 24 ;
 buf [ 7 ] = ( tag >> 16 ) & 0xFF ;
 buf [ 8 ] = ( tag >> 8 ) & 0xFF ;
 buf [ 9 ] = tag & 0xFF ;
 if ( buf [ 9 ] == 0x20 ) buf [ 9 ] = '\0' ;
 buf [ 10 ] = '\0' ;
 return hb_language_from_string ( ( char * ) buf , - 1 ) ;
 }
 }