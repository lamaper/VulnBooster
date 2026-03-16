void get_privilege_desc ( char * to , uint max_length , ulong access ) {
 uint pos ;
 char * start = to ;
 DBUG_ASSERT ( max_length >= 30 ) ;
 if ( access ) {
 max_length -- ;
 for ( pos = 0 ;
 access ;
 pos ++ , access >>= 1 ) {
 if ( ( access & 1 ) && command_lengths [ pos ] + ( uint ) ( to - start ) < max_length ) {
 to = strmov ( to , command_array [ pos ] ) ;
 * to ++ = ',' ;
 }
 }
 to -- ;
 }
 * to = 0 ;
 }