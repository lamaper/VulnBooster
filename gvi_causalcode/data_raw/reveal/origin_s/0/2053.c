static uint32_t get_le32 ( void * addr ) {
 return le32_to_cpu ( * ( ( uint32_t * ) addr ) ) ;
 }