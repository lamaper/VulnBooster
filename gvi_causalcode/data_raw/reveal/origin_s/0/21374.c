static void chomp3 ( ChannelData * chd , int16_t * output , uint8_t val , int tab_idx ) {
 int16_t current = read_table ( chd , val , tab_idx ) ;
 current = mace_broken_clip_int16 ( current + chd -> level ) ;
 chd -> level = current - ( current >> 3 ) ;
 * output = QT_8S_2_16S ( current ) ;
 }