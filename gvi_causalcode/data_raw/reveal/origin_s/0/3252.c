gx_color_index mem_mapped_map_rgb_color ( gx_device * dev , const gx_color_value cv [ ] ) {
 gx_device_memory * const mdev = ( gx_device_memory * ) dev ;
 byte br = gx_color_value_to_byte ( cv [ 0 ] ) ;
 register const byte * pptr = mdev -> palette . data ;
 int cnt = mdev -> palette . size ;
 const byte * which = 0 ;
 int best = 256 * 3 ;
 if ( mdev -> color_info . num_components != 1 ) {
 byte bg = gx_color_value_to_byte ( cv [ 1 ] ) ;
 byte bb = gx_color_value_to_byte ( cv [ 2 ] ) ;
 while ( ( cnt -= 3 ) >= 0 ) {
 register int diff = * pptr - br ;
 if ( diff < 0 ) diff = - diff ;
 if ( diff < best ) {
 int dg = pptr [ 1 ] - bg ;
 if ( dg < 0 ) dg = - dg ;
 if ( ( diff += dg ) < best ) {
 int db = pptr [ 2 ] - bb ;
 if ( db < 0 ) db = - db ;
 if ( ( diff += db ) < best ) which = pptr , best = diff ;
 }
 }
 if ( diff == 0 ) break ;
 pptr += 3 ;
 }
 }
 else {
 while ( ( cnt -= 3 ) >= 0 ) {
 register int diff = * pptr - br ;
 if ( diff < 0 ) diff = - diff ;
 if ( diff < best ) {
 which = pptr , best = diff ;
 }
 if ( diff == 0 ) break ;
 pptr += 3 ;
 }
 }
 return ( gx_color_index ) ( ( which - mdev -> palette . data ) / 3 ) ;
 }