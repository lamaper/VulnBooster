static inline void modify_pred ( const int8_t * mod_table , int * mode ) {
 * mode = mod_table [ * mode ] ;
 if ( * mode < 0 ) {
 av_log ( NULL , AV_LOG_ERROR , "Illegal intra prediction mode\n" ) ;
 * mode = 0 ;
 }
 }