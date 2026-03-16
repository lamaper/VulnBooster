static int PSAddImagemask ( EntityChar * ec , struct psstack * stack , int sp , real transform [ 6 ] , Color fillcol ) {
 uint8 * data ;
 int datalen , width , height , polarity ;
 real trans [ 6 ] ;
 struct _GImage * base ;
 GImage * gi ;
 Entity * ent ;
 int i , j ;
 if ( sp < 5 || ( stack [ sp - 1 ] . type != ps_instr && stack [ sp - 1 ] . type != ps_string ) ) {
 LogError ( _ ( "FontForge does not support dictionary based imagemask operators.\n" ) ) ;
 return ( sp - 1 ) ;
 }
 if ( stack [ sp - 2 ] . type != ps_array || stack [ sp - 2 ] . u . dict . cnt != 6 ) {
 LogError ( _ ( "Fourth argument of imagemask must be a 6-element transformation matrix.\n" ) ) ;
 return ( sp - 5 ) ;
 }
 if ( stack [ sp - 3 ] . type != ps_bool ) {
 LogError ( _ ( "Third argument of imagemask must be a boolean.\n" ) ) ;
 return ( sp - 5 ) ;
 }
 polarity = stack [ sp - 3 ] . u . tf ;
 if ( stack [ sp - 4 ] . type != ps_num || stack [ sp - 5 ] . type != ps_num ) {
 LogError ( _ ( "First and second arguments of imagemask must be integers.\n" ) ) ;
 return ( sp - 5 ) ;
 }
 height = stack [ sp - 4 ] . u . val ;
 width = stack [ sp - 5 ] . u . val ;
 data = StringToBytes ( & stack [ sp - 1 ] , & datalen ) ;
 if ( width <= 0 || height <= 0 || ( ( width + 7 ) / 8 ) * height > datalen ) {
 LogError ( _ ( "Width or height arguments to imagemask contain invalid values\n(either negative or they require more data than provided).\n" ) ) ;
 free ( data ) ;
 return ( sp - 5 ) ;
 }
 trans [ 0 ] = stack [ sp - 2 ] . u . dict . entries [ 0 ] . u . val ;
 trans [ 1 ] = stack [ sp - 2 ] . u . dict . entries [ 1 ] . u . val ;
 trans [ 2 ] = stack [ sp - 2 ] . u . dict . entries [ 2 ] . u . val ;
 trans [ 3 ] = stack [ sp - 2 ] . u . dict . entries [ 3 ] . u . val ;
 trans [ 4 ] = stack [ sp - 2 ] . u . dict . entries [ 4 ] . u . val ;
 trans [ 5 ] = stack [ sp - 2 ] . u . dict . entries [ 5 ] . u . val ;
 gi = GImageCreate ( it_mono , width , height ) ;
 base = gi -> u . image ;
 base -> trans = 1 ;
 if ( polarity ) {
 for ( i = 0 ;
 i < datalen ;
 ++ i ) data [ i ] ^= 0xff ;
 }
 if ( trans [ 0 ] > 0 && trans [ 3 ] < 0 ) memcpy ( base -> data , data , datalen ) ;
 else if ( trans [ 0 ] > 0 && trans [ 3 ] > 0 ) {
 for ( i = 0 ;
 i < height ;
 ++ i ) memcpy ( base -> data + i * base -> bytes_per_line , data + ( height - i ) * base -> bytes_per_line , base -> bytes_per_line ) ;
 }
 else if ( trans [ 0 ] < 0 && trans [ 3 ] < 0 ) {
 for ( i = 0 ;
 i < height ;
 ++ i ) for ( j = 0 ;
 j < width ;
 ++ j ) {
 if ( data [ i * base -> bytes_per_line + ( j >> 3 ) ] & ( 0x80 >> ( j & 7 ) ) ) base -> data [ i * base -> bytes_per_line + ( ( width - j - 1 ) >> 3 ) ] |= ( 0x80 >> ( ( width - j - 1 ) & 7 ) ) ;
 }
 }
 else {
 for ( i = 0 ;
 i < height ;
 ++ i ) for ( j = 0 ;
 j < width ;
 ++ j ) {
 if ( data [ i * base -> bytes_per_line + ( j >> 3 ) ] & ( 0x80 >> ( j & 7 ) ) ) base -> data [ ( height - i - 1 ) * base -> bytes_per_line + ( ( width - j - 1 ) >> 3 ) ] |= ( 0x80 >> ( ( width - j - 1 ) & 7 ) ) ;
 }
 }
 free ( data ) ;
 ent = calloc ( 1 , sizeof ( Entity ) ) ;
 ent -> type = et_image ;
 ent -> u . image . image = gi ;
 memcpy ( ent -> u . image . transform , transform , sizeof ( real [ 6 ] ) ) ;
 ent -> u . image . transform [ 0 ] /= width ;
 ent -> u . image . transform [ 3 ] /= height ;
 ent -> u . image . transform [ 5 ] += height ;
 ent -> u . image . col = fillcol ;
 ent -> next = ec -> splines ;
 ec -> splines = ent ;
 return ( sp - 5 ) ;
 }