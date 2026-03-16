static float usec_to_fps ( uint64_t usec , unsigned int frames ) {
 return ( float ) ( usec > 0 ? frames * 1000000.0 / ( float ) usec : 0 ) ;
 }