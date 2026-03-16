static gint get_record ( k12_t * file_data , FILE_T fh , gint64 file_offset , gboolean is_random , int * err , gchar * * err_info ) {
 guint8 * buffer = is_random ? file_data -> rand_read_buff : file_data -> seq_read_buff ;
 guint buffer_len = is_random ? file_data -> rand_read_buff_len : file_data -> seq_read_buff_len ;
 guint total_read = 0 ;
 guint left ;
 guint8 * writep ;


 K12_DBG ( 6 , ( "get_record: ENTER: junky_offset=%" G_GINT64_MODIFIER "d, file_offset=%" G_GINT64_MODIFIER "d" , junky_offset , file_offset ) ) ;
 if ( buffer == NULL ) {
 buffer = ( guint8 * ) g_malloc ( 8192 ) ;
 buffer_len = 8192 ;
 if ( is_random ) {
 file_data -> rand_read_buff = buffer ;
 file_data -> rand_read_buff_len = buffer_len ;
 }
 else {
 file_data -> seq_read_buff = buffer ;
 file_data -> seq_read_buff_len = buffer_len ;
 }
 }
 if ( junky_offset == 8192 ) {
 if ( ! file_skip ( fh , K12_FILE_BLOB_LEN , err ) ) return - 1 ;
 total_read += K12_FILE_BLOB_LEN ;
 }
 if ( ! wtap_read_bytes ( fh , buffer , 4 , err , err_info ) ) return - 1 ;
 total_read += 4 ;
 left = pntoh32 ( buffer + K12_RECORD_LEN ) ;


 K12_DBG ( 5 , ( "get_record: GET length=%u" , left ) ) ;
 if ( left < 8 ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup_printf ( "k12: Record length %u is less than 8 bytes long" , left ) ;
 return - 1 ;
 }
 if ( left > WTAP_MAX_PACKET_SIZE ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup_printf ( "k12: Record length %u is greater than the maximum %u" , left , WTAP_MAX_PACKET_SIZE ) ;
 return - 1 ;
 }
 while ( left > buffer_len ) {
 buffer = ( guint8 * ) g_realloc ( buffer , buffer_len *= 2 ) ;
 if ( is_random ) {
 file_data -> rand_read_buff = buffer ;
 file_data -> rand_read_buff_len = buffer_len ;
 }
 else {
 file_data -> seq_read_buff = buffer ;
 file_data -> seq_read_buff_len = buffer_len ;
 }
 }
 writep = buffer + 4 ;
 left -= 4 ;
 do {
 K12_DBG ( 6 , ( "get_record: looping left=%d junky_offset=%" G_GINT64_MODIFIER "d" , left , junky_offset ) ) ;
 if ( junky_offset > left ) {
 if ( ! wtap_read_bytes ( fh , writep , left , err , err_info ) ) return - 1 ;
 total_read += left ;
 break ;
 }
 else {
 if ( ! wtap_read_bytes ( fh , writep , junky_offset , err , err_info ) ) return - 1 ;
 total_read += junky_offset ;
 writep += junky_offset ;
 if ( ! file_skip ( fh , K12_FILE_BLOB_LEN , err ) ) return - 1 ;
 total_read += K12_FILE_BLOB_LEN ;
 left -= junky_offset ;
 junky_offset = 8192 ;
 }
 }
 while ( left ) ;
 K12_HEX_ASCII_DUMP ( 5 , file_offset , "GOT record" , buffer , actual_len ) ;
 return total_read ;
 }