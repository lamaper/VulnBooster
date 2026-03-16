static int get_nick_length ( void * data ) {
 return string_width ( ( ( NICK_REC * ) data ) -> nick , - 1 ) ;
 }