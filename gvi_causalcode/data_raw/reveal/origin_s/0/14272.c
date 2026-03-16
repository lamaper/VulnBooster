static gint rtmpt_message_header_length ( gint id ) {
 switch ( ( id >> 6 ) & 3 ) {
 case 0 : return 11 ;
 case 1 : return 7 ;
 case 2 : return 3 ;
 default : return 0 ;
 }
 }