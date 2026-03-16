static gint check_diameter ( tvbuff_t * tvb ) {
 guint32 diam_len ;
 guint8 flags ;
 if ( tvb_captured_length ( tvb ) < 5 ) return NOT_ENOUGH_DATA ;
 if ( tvb_get_guint8 ( tvb , 0 ) != 1 ) return NOT_DIAMETER ;
 diam_len = tvb_get_ntoh24 ( tvb , 1 ) ;
 if ( diam_len > 65534 ) return NOT_DIAMETER ;
 if ( diam_len < 36 ) return NOT_DIAMETER ;
 flags = tvb_get_guint8 ( tvb , 4 ) ;
 if ( flags & 0x0f ) return NOT_DIAMETER ;
 if ( ( flags & DIAM_FLAGS_R ) && ( flags & DIAM_FLAGS_E ) ) return NOT_DIAMETER ;
 return IS_DIAMETER ;
 }