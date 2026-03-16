static gboolean k12_read ( wtap * wth , int * err , gchar * * err_info , gint64 * data_offset ) {
 k12_t * k12 = ( k12_t * ) wth -> priv ;
 k12_src_desc_t * src_desc ;
 guint8 * buffer ;
 gint64 offset ;
 gint len ;
 guint32 type ;
 guint32 src_id ;
 offset = file_tell ( wth -> fh ) ;
 do {
 if ( k12 -> num_of_records == 0 ) {
 * err = 0 ;
 return FALSE ;
 }
 K12_DBG ( 5 , ( "k12_read: offset=%i" , offset ) ) ;
 * data_offset = offset ;
 len = get_record ( k12 , wth -> fh , offset , FALSE , err , err_info ) ;
 if ( len < 0 ) {
 return FALSE ;
 }
 else if ( len == 0 ) {
 * err = WTAP_ERR_SHORT_READ ;
 return FALSE ;
 }
 else if ( len < K12_RECORD_SRC_ID + 4 ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup_printf ( "data record length %d too short" , len ) ;
 return FALSE ;
 }
 k12 -> num_of_records -- ;
 buffer = k12 -> seq_read_buff ;
 type = pntoh32 ( buffer + K12_RECORD_TYPE ) ;
 src_id = pntoh32 ( buffer + K12_RECORD_SRC_ID ) ;
 if ( ! ( src_desc = ( k12_src_desc_t * ) g_hash_table_lookup ( k12 -> src_by_id , GUINT_TO_POINTER ( src_id ) ) ) ) {
 src_desc = ( k12_src_desc_t * ) g_hash_table_lookup ( k12 -> src_by_id , GUINT_TO_POINTER ( src_id & K12_RECORD_SRC_ID_MASK ) ) ;
 }
 K12_DBG ( 5 , ( "k12_read: record type=%x src_id=%x" , type , src_id ) ) ;
 offset += len ;
 }
 while ( ( ( type & K12_MASK_PACKET ) != K12_REC_PACKET && ( type & K12_MASK_PACKET ) != K12_REC_D0020 ) || ! src_id || ! src_desc ) ;
 process_packet_data ( & wth -> phdr , wth -> frame_buffer , buffer , len , k12 ) ;
 return TRUE ;
 }