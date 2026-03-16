void append_salt_to_key ( uint8_t * key , unsigned int bytes_in_key , uint8_t * salt , unsigned int bytes_in_salt ) {
 memcpy ( key + bytes_in_key , salt , bytes_in_salt ) ;
 }