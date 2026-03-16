static int chk_index_down ( MI_CHECK * param , MI_INFO * info , MI_KEYDEF * keyinfo , my_off_t page , uchar * buff , ha_rows * keys , ha_checksum * key_checksum , uint level ) {
 char llbuff [ 22 ] , llbuff2 [ 22 ] ;
 DBUG_ENTER ( "chk_index_down" ) ;
 if ( page + keyinfo -> block_length > info -> state -> key_file_length ) {
 my_off_t max_length = mysql_file_seek ( info -> s -> kfile , 0L , MY_SEEK_END , MYF ( MY_THREADSAFE ) ) ;
 mi_check_print_error ( param , "Invalid key block position: %s " "key block size: %u file_length: %s" , llstr ( page , llbuff ) , keyinfo -> block_length , llstr ( info -> state -> key_file_length , llbuff2 ) ) ;
 if ( page + keyinfo -> block_length > max_length ) goto err ;
 info -> state -> key_file_length = ( max_length & ~ ( my_off_t ) ( keyinfo -> block_length - 1 ) ) ;
 }
 if ( page & ( MI_MIN_KEY_BLOCK_LENGTH - 1 ) ) {
 mi_check_print_error ( param , "Mis-aligned key block: %s " "minimum key block length: %u" , llstr ( page , llbuff ) , MI_MIN_KEY_BLOCK_LENGTH ) ;
 goto err ;
 }
 if ( ! _mi_fetch_keypage ( info , keyinfo , page , DFLT_INIT_HITS , buff , 0 ) ) {
 mi_check_print_error ( param , "Can't read key from filepos: %s" , llstr ( page , llbuff ) ) ;
 goto err ;
 }
 param -> key_file_blocks += keyinfo -> block_length ;
 if ( chk_index ( param , info , keyinfo , page , buff , keys , key_checksum , level ) ) goto err ;
 DBUG_RETURN ( 0 ) ;
 err : DBUG_RETURN ( 1 ) ;
 }