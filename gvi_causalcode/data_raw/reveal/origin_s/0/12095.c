static gboolean k12_dump ( wtap_dumper * wdh , const struct wtap_pkthdr * phdr , const guint8 * pd , int * err , gchar * * err_info _U_ ) {
 const union wtap_pseudo_header * pseudo_header = & phdr -> pseudo_header ;
 k12_dump_t * k12 = ( k12_dump_t * ) wdh -> priv ;
 guint32 len ;
 union {
 guint8 buffer [ 8192 ] ;
 struct {
 guint32 len ;
 guint32 type ;
 guint32 frame_len ;
 guint32 input ;
 guint32 datum_1 ;
 guint32 datum_2 ;
 guint64 ts ;
 guint8 frame [ 0x1fc0 ] ;
 }
 record ;
 }
 obj ;
 if ( phdr -> rec_type != REC_TYPE_PACKET ) {
 * err = WTAP_ERR_UNWRITABLE_REC_TYPE ;
 return FALSE ;
 }
 if ( k12 -> num_of_records == 0 ) {
 k12_t * file_data = ( k12_t * ) pseudo_header -> k12 . stuff ;
 g_hash_table_foreach ( file_data -> src_by_id , k12_dump_src_setting , wdh ) ;
 }
 obj . record . len = 0x20 + phdr -> caplen ;
 obj . record . len += ( obj . record . len % 4 ) ? 4 - obj . record . len % 4 : 0 ;
 len = obj . record . len ;
 obj . record . len = g_htonl ( obj . record . len ) ;
 obj . record . type = g_htonl ( K12_REC_PACKET ) ;
 obj . record . frame_len = g_htonl ( phdr -> caplen ) ;
 obj . record . input = g_htonl ( pseudo_header -> k12 . input ) ;
 obj . record . ts = GUINT64_TO_BE ( ( ( ( guint64 ) phdr -> ts . secs - 631152000 ) * 2000000 ) + ( phdr -> ts . nsecs / 1000 * 2 ) ) ;
 memcpy ( obj . record . frame , pd , phdr -> caplen ) ;
 return k12_dump_record ( wdh , len , obj . buffer , err ) ;
 }