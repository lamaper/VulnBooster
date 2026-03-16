static gint rtmpt_basic_header_length ( gint id ) {
 switch ( id & 0x3f ) {
 case 0 : return 2 ;
 case 1 : return 3 ;
 default : return 1 ;
 }
 }