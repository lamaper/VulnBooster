static inline unsigned update_map_generation ( MotionEstContext * c ) {
 c -> map_generation += 1 << ( ME_MAP_MV_BITS * 2 ) ;
 if ( c -> map_generation == 0 ) {
 c -> map_generation = 1 << ( ME_MAP_MV_BITS * 2 ) ;
 memset ( c -> map , 0 , sizeof ( uint32_t ) * ME_MAP_SIZE ) ;
 }
 return c -> map_generation ;
 }