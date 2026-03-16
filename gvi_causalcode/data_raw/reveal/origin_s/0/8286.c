static void get_time_value ( tvbuff_t * tvb , const gint start , const gint length , const guint encoding , nstime_t * time_stamp , const gboolean is_relative ) {
 guint32 tmpsecs ;
 guint64 todsecs ;
 if ( is_relative && ( encoding != ( ENC_TIME_TIMESPEC | ENC_BIG_ENDIAN ) ) && ( encoding != ( ENC_TIME_TIMESPEC | ENC_LITTLE_ENDIAN ) ) ) {
 return ;
 }
 switch ( encoding ) {
 case ENC_TIME_TIMESPEC | ENC_BIG_ENDIAN : time_stamp -> secs = ( time_t ) tvb_get_ntohl ( tvb , start ) ;
 if ( length == 8 ) time_stamp -> nsecs = tvb_get_ntohl ( tvb , start + 4 ) ;
 else time_stamp -> nsecs = 0 ;
 break ;
 case ENC_TIME_TIMESPEC | ENC_LITTLE_ENDIAN : time_stamp -> secs = ( time_t ) tvb_get_letohl ( tvb , start ) ;
 if ( length == 8 ) time_stamp -> nsecs = tvb_get_letohl ( tvb , start + 4 ) ;
 else time_stamp -> nsecs = 0 ;
 break ;
 case ENC_TIME_TOD | ENC_BIG_ENDIAN : # define TOD_BASETIME G_GUINT64_CONSTANT ( 2208988800 ) todsecs = tvb_get_ntoh64 ( tvb , start ) >> 12 ;
 time_stamp -> secs = ( time_t ) ( ( todsecs / 1000000 ) - TOD_BASETIME ) ;
 time_stamp -> nsecs = ( int ) ( ( todsecs % 1000000 ) * 1000 ) ;
 break ;
 case ENC_TIME_TOD | ENC_LITTLE_ENDIAN : todsecs = tvb_get_letoh64 ( tvb , start ) >> 12 ;
 time_stamp -> secs = ( time_t ) ( ( todsecs / 1000000 ) - TOD_BASETIME ) ;
 time_stamp -> nsecs = ( int ) ( ( todsecs % 1000000 ) * 1000 ) ;
 break ;
 case ENC_TIME_NTP | ENC_BIG_ENDIAN : # define NTP_BASETIME G_GUINT64_CONSTANT ( 2208988800 ) tmpsecs = tvb_get_ntohl ( tvb , start ) ;
 if ( tmpsecs ) time_stamp -> secs = ( time_t ) ( tmpsecs - ( guint32 ) NTP_BASETIME ) ;
 else time_stamp -> secs = tmpsecs ;
 if ( length == 8 ) {
 time_stamp -> nsecs = ( int ) ( 1000000 * ( tvb_get_ntohl ( tvb , start + 4 ) / 4294967296.0 ) ) ;
 time_stamp -> nsecs *= 1000 ;
 }
 else {
 time_stamp -> nsecs = 0 ;
 }
 break ;
 case ENC_TIME_NTP | ENC_LITTLE_ENDIAN : tmpsecs = tvb_get_letohl ( tvb , start ) ;
 if ( tmpsecs ) time_stamp -> secs = ( time_t ) ( tmpsecs - ( guint32 ) NTP_BASETIME ) ;
 else time_stamp -> secs = tmpsecs ;
 if ( length == 8 ) {
 time_stamp -> nsecs = ( int ) ( 1000000 * ( tvb_get_letohl ( tvb , start + 4 ) / 4294967296.0 ) ) ;
 time_stamp -> nsecs *= 1000 ;
 }
 else {
 time_stamp -> nsecs = 0 ;
 }
 break ;
 case ENC_TIME_NTP_BASE_ZERO | ENC_BIG_ENDIAN : # define NTP_BASETIME_ZERO G_GUINT64_CONSTANT ( 0 ) tmpsecs = tvb_get_ntohl ( tvb , start ) ;
 if ( tmpsecs ) time_stamp -> secs = ( time_t ) ( tmpsecs - ( guint32 ) NTP_BASETIME_ZERO ) ;
 else time_stamp -> secs = tmpsecs ;
 if ( length == 8 ) {
 time_stamp -> nsecs = ( int ) ( 1000000 * ( tvb_get_ntohl ( tvb , start + 4 ) / 4294967296.0 ) ) ;
 time_stamp -> nsecs *= 1000 ;
 }
 else {
 time_stamp -> nsecs = 0 ;
 }
 break ;
 case ENC_TIME_NTP_BASE_ZERO | ENC_LITTLE_ENDIAN : tmpsecs = tvb_get_letohl ( tvb , start ) ;
 if ( tmpsecs ) time_stamp -> secs = ( time_t ) ( tmpsecs - ( guint32 ) NTP_BASETIME_ZERO ) ;
 else time_stamp -> secs = tmpsecs ;
 time_stamp -> secs = ( time_t ) tvb_get_letohl ( tvb , start ) ;
 if ( length == 8 ) {
 time_stamp -> nsecs = ( int ) ( 1000000 * ( tvb_get_letohl ( tvb , start + 4 ) / 4294967296.0 ) ) ;
 time_stamp -> nsecs *= 1000 ;
 }
 else {
 time_stamp -> nsecs = 0 ;
 }
 break ;
 default : DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 break ;
 }
 }