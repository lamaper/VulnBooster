static inline void get_limits ( MpegEncContext * s , int x , int y ) {
 MotionEstContext * const c = & s -> me ;
 int range = c -> avctx -> me_range >> ( 1 + ! ! ( c -> flags & FLAG_QPEL ) ) ;
 if ( s -> unrestricted_mv ) {
 c -> xmin = - x - 16 ;
 c -> ymin = - y - 16 ;
 c -> xmax = - x + s -> mb_width * 16 ;
 c -> ymax = - y + s -> mb_height * 16 ;
 }
 else if ( s -> out_format == FMT_H261 ) {
 c -> xmin = ( x > 15 ) ? - 15 : 0 ;
 c -> ymin = ( y > 15 ) ? - 15 : 0 ;
 c -> xmax = ( x < s -> mb_width * 16 - 16 ) ? 15 : 0 ;
 c -> ymax = ( y < s -> mb_height * 16 - 16 ) ? 15 : 0 ;
 }
 else {
 c -> xmin = - x ;
 c -> ymin = - y ;
 c -> xmax = - x + s -> mb_width * 16 - 16 ;
 c -> ymax = - y + s -> mb_height * 16 - 16 ;
 }
 if ( range ) {
 c -> xmin = FFMAX ( c -> xmin , - range ) ;
 c -> xmax = FFMIN ( c -> xmax , range ) ;
 c -> ymin = FFMAX ( c -> ymin , - range ) ;
 c -> ymax = FFMIN ( c -> ymax , range ) ;
 }
 }