static guint32 amf_get_u29 ( tvbuff_t * tvb , int offset , guint * lenp ) {
 guint len = 0 ;
 guint8 iByte ;
 guint32 iValue ;
 iByte = tvb_get_guint8 ( tvb , offset ) ;
 iValue = ( iByte & 0x7F ) ;
 offset ++ ;
 len ++ ;
 if ( ! ( iByte & 0x80 ) ) {
 * lenp = len ;
 return iValue ;
 }
 iByte = tvb_get_guint8 ( tvb , offset ) ;
 iValue = ( iValue << 7 ) | ( iByte & 0x7F ) ;
 offset ++ ;
 len ++ ;
 if ( ! ( iByte & 0x80 ) ) {
 * lenp = len ;
 return iValue ;
 }
 iByte = tvb_get_guint8 ( tvb , offset ) ;
 iValue = ( iValue << 7 ) | ( iByte & 0x7F ) ;
 offset ++ ;
 len ++ ;
 if ( ! ( iByte & 0x80 ) ) {
 * lenp = len ;
 return iValue ;
 }
 iByte = tvb_get_guint8 ( tvb , offset ) ;
 iValue = ( iValue << 8 ) | iByte ;
 len ++ ;
 * lenp = len ;
 return iValue ;
 }