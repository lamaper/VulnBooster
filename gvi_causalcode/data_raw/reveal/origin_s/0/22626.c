static const struct ogg_codec * ogg_find_codec ( uint8_t * buf , int size ) {
 int i ;
 for ( i = 0 ;
 ogg_codecs [ i ] ;
 i ++ ) if ( size >= ogg_codecs [ i ] -> magicsize && ! memcmp ( buf , ogg_codecs [ i ] -> magic , ogg_codecs [ i ] -> magicsize ) ) return ogg_codecs [ i ] ;
 return NULL ;
 }