static int ngsniffer_process_record ( wtap * wth , gboolean is_random , guint * padding , struct wtap_pkthdr * phdr , Buffer * buf , int * err , gchar * * err_info ) {
 ngsniffer_t * ngsniffer ;
 char record_type [ 2 ] ;
 char record_length [ 4 ] ;
 guint16 type , length ;
 struct frame2_rec frame2 ;
 struct frame4_rec frame4 ;
 struct frame6_rec frame6 ;
 guint16 time_low , time_med , true_size , size ;
 guint8 time_high , time_day ;
 guint64 t , tsecs , tpsecs ;
 if ( ! ng_read_bytes_or_eof ( wth , record_type , 2 , is_random , err , err_info ) ) {
 if ( * err != 0 ) return - 1 ;
 return REC_EOF ;
 }
 if ( ! ng_read_bytes ( wth , record_length , 4 , is_random , err , err_info ) ) return - 1 ;
 type = pletoh16 ( record_type ) ;
 length = pletoh16 ( record_length ) ;
 ngsniffer = ( ngsniffer_t * ) wth -> priv ;
 switch ( type ) {
 case REC_FRAME2 : if ( ngsniffer -> network == NETWORK_ATM ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup ( "ngsniffer: REC_FRAME2 record in an ATM Sniffer file" ) ;
 return - 1 ;
 }
 if ( ! ng_read_bytes ( wth , & frame2 , ( unsigned int ) sizeof frame2 , is_random , err , err_info ) ) return - 1 ;
 time_low = pletoh16 ( & frame2 . time_low ) ;
 time_med = pletoh16 ( & frame2 . time_med ) ;
 time_high = frame2 . time_high ;
 time_day = frame2 . time_day ;
 size = pletoh16 ( & frame2 . size ) ;
 true_size = pletoh16 ( & frame2 . true_size ) ;
 length -= sizeof frame2 ;
 set_pseudo_header_frame2 ( wth , & phdr -> pseudo_header , & frame2 ) ;
 break ;
 case REC_FRAME4 : if ( ngsniffer -> network != NETWORK_ATM ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup ( "ngsniffer: REC_FRAME4 record in a non-ATM Sniffer file" ) ;
 return - 1 ;
 }
 if ( ! ng_read_bytes ( wth , & frame4 , ( unsigned int ) sizeof frame4 , is_random , err , err_info ) ) return - 1 ;
 time_low = pletoh16 ( & frame4 . time_low ) ;
 time_med = pletoh16 ( & frame4 . time_med ) ;
 time_high = frame4 . time_high ;
 time_day = frame4 . time_day ;
 size = pletoh16 ( & frame4 . size ) ;
 true_size = pletoh16 ( & frame4 . true_size ) ;
 if ( ngsniffer -> maj_vers >= 5 ) length -= sizeof frame4 ;
 else {
 if ( ngsniffer -> min_vers >= 95 ) length -= sizeof frame2 ;
 else length -= sizeof frame4 ;
 }
 set_pseudo_header_frame4 ( & phdr -> pseudo_header , & frame4 ) ;
 break ;
 case REC_FRAME6 : if ( ! ng_read_bytes ( wth , & frame6 , ( unsigned int ) sizeof frame6 , is_random , err , err_info ) ) return - 1 ;
 time_low = pletoh16 ( & frame6 . time_low ) ;
 time_med = pletoh16 ( & frame6 . time_med ) ;
 time_high = frame6 . time_high ;
 time_day = frame6 . time_day ;
 size = pletoh16 ( & frame6 . size ) ;
 true_size = pletoh16 ( & frame6 . true_size ) ;
 length -= sizeof frame6 ;
 set_pseudo_header_frame6 ( wth , & phdr -> pseudo_header , & frame6 ) ;
 break ;
 case REC_EOF : * err = 0 ;
 return REC_EOF ;
 default : if ( padding != NULL ) {
 * padding = length ;
 }
 return type ;
 }
 if ( size > length ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup ( "ngsniffer: Record length is less than packet size" ) ;
 return - 1 ;
 }
 if ( padding != NULL ) {
 * padding = length - size ;
 }
 phdr -> rec_type = REC_TYPE_PACKET ;
 phdr -> presence_flags = true_size ? WTAP_HAS_TS | WTAP_HAS_CAP_LEN : WTAP_HAS_TS ;
 phdr -> len = true_size ? true_size : size ;
 phdr -> caplen = size ;
 ws_buffer_assure_space ( buf , size ) ;
 if ( ! ng_read_bytes ( wth , ws_buffer_start_ptr ( buf ) , size , is_random , err , err_info ) ) return - 1 ;
 phdr -> pkt_encap = fix_pseudo_header ( wth -> file_encap , buf , length , & phdr -> pseudo_header ) ;
 t = ( ( ( guint64 ) time_high ) << 32 ) | ( ( ( guint64 ) time_med ) << 16 ) | time_low ;
 t *= ngsniffer -> timeunit ;
 tsecs = t / G_GUINT64_CONSTANT ( 1000000000000 ) ;
 tpsecs = t - tsecs * G_GUINT64_CONSTANT ( 1000000000000 ) ;
 tsecs += time_day * 86400 ;
 tsecs += ngsniffer -> start ;
 phdr -> ts . secs = ( time_t ) tsecs ;
 phdr -> ts . nsecs = ( int ) ( tpsecs / 1000 ) ;
 return type ;
 }