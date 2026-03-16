static inline int get_value ( BinkContext * c , int bundle ) {
 int ret ;
 if ( bundle < BINK_SRC_X_OFF || bundle == BINK_SRC_RUN ) return * c -> bundle [ bundle ] . cur_ptr ++ ;
 if ( bundle == BINK_SRC_X_OFF || bundle == BINK_SRC_Y_OFF ) return ( int8_t ) * c -> bundle [ bundle ] . cur_ptr ++ ;
 ret = * ( int16_t * ) c -> bundle [ bundle ] . cur_ptr ;
 c -> bundle [ bundle ] . cur_ptr += 2 ;
 return ret ;
 }