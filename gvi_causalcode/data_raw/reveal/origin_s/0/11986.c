static int file_exists ( const u_char * filename , unsigned int throttle_rate ) {
 return get_file_type ( filename , throttle_rate ) == FT_FILE ;
 }