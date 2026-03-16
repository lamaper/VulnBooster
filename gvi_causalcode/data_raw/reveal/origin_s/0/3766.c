wtap_open_return_val k12_open ( wtap * wth , int * err , gchar * * err_info ) {
 k12_src_desc_t * rec ;
 guint8 header_buffer [ K12_FILE_HDR_LEN ] ;
 guint8 * read_buffer ;
 guint32 type ;
 long offset ;
 long len ;
 guint port_type ;
 guint32 rec_len ;
 guint32 hwpart_len ;
 guint32 name_len ;
 guint32 stack_len ;
 guint i ;
 k12_t * file_data ;

 env_file = getenv ( "K12_DEBUG_FILENAME" ) ;
 if ( env_file ) {
 dbg_out = ws_fopen ( env_file , "w" ) ;
 if ( dbg_out == NULL ) {
 dbg_out = stderr ;
 K12_DBG ( 1 , ( "unable to open K12 DEBUG FILENAME for writing! Logging to standard error" ) ) ;
 }
 }
 else dbg_out = stderr ;
 if ( env_level ) debug_level = ( unsigned int ) strtoul ( env_level , NULL , 10 ) ;
 K12_DBG ( 1 , ( "k12_open: ENTER debug_level=%u" , debug_level ) ) ;

 K12_DBG ( 1 , ( "k12_open: FILE HEADER TOO SHORT OR READ ERROR" ) ) ;
 if ( * err != WTAP_ERR_SHORT_READ ) {
 return WTAP_OPEN_ERROR ;
 }
 return WTAP_OPEN_NOT_MINE ;
 }
 if ( memcmp ( header_buffer , k12_file_magic , 8 ) != 0 ) {
 K12_DBG ( 1 , ( "k12_open: BAD MAGIC" ) ) ;
 return WTAP_OPEN_NOT_MINE ;
 }
 offset = K12_FILE_HDR_LEN ;
 file_data = new_k12_file_data ( ) ;
 file_data -> file_len = pntoh32 ( header_buffer + 0x8 ) ;
 if ( memiszero ( header_buffer + 0x10 , K12_FILE_HDR_LEN - 0x10 ) ) {
 file_data -> num_of_records = pntoh32 ( header_buffer + 0x0C ) ;
 }
 else {
 file_data -> num_of_records = pntoh32 ( header_buffer + K12_FILE_HDR_RECORD_COUNT_1 ) ;
 if ( file_data -> num_of_records != pntoh32 ( header_buffer + K12_FILE_HDR_RECORD_COUNT_2 ) ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup_printf ( "k12: two different record counts, %u at 0x%02x and %u at 0x%02x" , file_data -> num_of_records , K12_FILE_HDR_RECORD_COUNT_1 , pntoh32 ( header_buffer + K12_FILE_HDR_RECORD_COUNT_2 ) , K12_FILE_HDR_RECORD_COUNT_2 ) ;
 return WTAP_OPEN_ERROR ;
 }
 }
 K12_DBG ( 5 , ( "k12_open: FILE_HEADER OK: offset=%x file_len=%i records=%i" , offset , file_data -> file_len , file_data -> num_of_records ) ) ;
 do {
 if ( file_data -> num_of_records == 0 ) {
 * err = WTAP_ERR_SHORT_READ ;
 destroy_k12_file_data ( file_data ) ;
 return WTAP_OPEN_ERROR ;
 }
 len = get_record ( file_data , wth -> fh , offset , FALSE , err , err_info ) ;
 if ( len < 0 ) {
 K12_DBG ( 1 , ( "k12_open: BAD HEADER RECORD" , len ) ) ;
 destroy_k12_file_data ( file_data ) ;
 return WTAP_OPEN_ERROR ;
 }
 if ( len == 0 ) {
 K12_DBG ( 1 , ( "k12_open: BAD HEADER RECORD" , len ) ) ;
 * err = WTAP_ERR_SHORT_READ ;
 destroy_k12_file_data ( file_data ) ;
 return WTAP_OPEN_ERROR ;
 }
 read_buffer = file_data -> seq_read_buff ;
 rec_len = pntoh32 ( read_buffer + K12_RECORD_LEN ) ;
 if ( rec_len < K12_RECORD_TYPE + 4 ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup_printf ( "k12_open: record length %u < %u" , rec_len , K12_RECORD_TYPE + 4 ) ;
 return WTAP_OPEN_ERROR ;
 }
 type = pntoh32 ( read_buffer + K12_RECORD_TYPE ) ;
 if ( ( type & K12_MASK_PACKET ) == K12_REC_PACKET || ( type & K12_MASK_PACKET ) == K12_REC_D0020 ) {
 if ( file_seek ( wth -> fh , offset , SEEK_SET , err ) == - 1 ) {
 destroy_k12_file_data ( file_data ) ;
 return WTAP_OPEN_ERROR ;
 }
 K12_DBG ( 5 , ( "k12_open: FIRST PACKET offset=%x" , offset ) ) ;
 break ;
 }
 switch ( type ) {
 case K12_REC_SRCDSC : case K12_REC_SRCDSC2 : rec = g_new0 ( k12_src_desc_t , 1 ) ;
 if ( rec_len < K12_SRCDESC_HWPART ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup_printf ( "k12_open: source descriptor record length %u < %u" , rec_len , K12_SRCDESC_HWPART ) ;
 destroy_k12_file_data ( file_data ) ;
 g_free ( rec ) ;
 return WTAP_OPEN_ERROR ;
 }
 port_type = read_buffer [ K12_SRCDESC_PORT_TYPE ] ;
 hwpart_len = pntoh16 ( read_buffer + K12_SRCDESC_HWPARTLEN ) ;
 name_len = pntoh16 ( read_buffer + K12_SRCDESC_NAMELEN ) ;
 stack_len = pntoh16 ( read_buffer + K12_SRCDESC_STACKLEN ) ;
 rec -> input = pntoh32 ( read_buffer + K12_RECORD_SRC_ID ) ;
 K12_DBG ( 5 , ( "k12_open: INTERFACE RECORD offset=%x interface=%x" , offset , rec -> input ) ) ;
 if ( name_len == 0 ) {
 K12_DBG ( 5 , ( "k12_open: failed (name_len == 0 in source description" ) ) ;
 destroy_k12_file_data ( file_data ) ;
 g_free ( rec ) ;
 return WTAP_OPEN_NOT_MINE ;
 }
 if ( stack_len == 0 ) {
 K12_DBG ( 5 , ( "k12_open: failed (stack_len == 0 in source description" ) ) ;
 destroy_k12_file_data ( file_data ) ;
 g_free ( rec ) ;
 return WTAP_OPEN_NOT_MINE ;
 }
 if ( rec_len < K12_SRCDESC_HWPART + hwpart_len + name_len + stack_len ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup_printf ( "k12_open: source descriptor record length %u < %u (%u + %u + %u + %u)" , rec_len , K12_SRCDESC_HWPART + hwpart_len + name_len + stack_len , K12_SRCDESC_HWPART , hwpart_len , name_len , stack_len ) ;
 destroy_k12_file_data ( file_data ) ;
 g_free ( rec ) ;
 return WTAP_OPEN_ERROR ;
 }
 if ( hwpart_len ) {
 if ( hwpart_len < 4 ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup_printf ( "k12_open: source descriptor hardware part length %u < 4" , hwpart_len ) ;
 destroy_k12_file_data ( file_data ) ;
 g_free ( rec ) ;
 return WTAP_OPEN_ERROR ;
 }
 switch ( ( rec -> input_type = pntoh32 ( read_buffer + K12_SRCDESC_HWPART + K12_SRCDESC_HWPARTTYPE ) ) ) {
 case K12_PORT_DS0S : rec -> input_info . ds0mask = 0x00000000 ;
 if ( hwpart_len > K12_SRCDESC_DS0_MASK ) {
 for ( i = 0 ;
 i < hwpart_len - K12_SRCDESC_DS0_MASK ;
 i ++ ) {
 rec -> input_info . ds0mask |= ( * ( read_buffer + K12_SRCDESC_HWPART + K12_SRCDESC_DS0_MASK + i ) == 0xff ) ? 1U << ( 31 - i ) : 0x0 ;
 }
 }
 break ;
 case K12_PORT_ATMPVC : if ( hwpart_len < K12_SRCDESC_ATM_VCI + 2 ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup_printf ( "k12_open: source descriptor hardware part length %u < %u" , hwpart_len , K12_SRCDESC_ATM_VCI + 2 ) ;
 destroy_k12_file_data ( file_data ) ;
 g_free ( rec ) ;
 return WTAP_OPEN_ERROR ;
 }
 rec -> input_info . atm . vp = pntoh16 ( read_buffer + K12_SRCDESC_HWPART + K12_SRCDESC_ATM_VPI ) ;
 rec -> input_info . atm . vc = pntoh16 ( read_buffer + K12_SRCDESC_HWPART + K12_SRCDESC_ATM_VCI ) ;
 break ;
 default : break ;
 }
 }
 else {
 if ( port_type >= 0x14 && port_type <= 0x17 ) {
 rec -> input_type = K12_PORT_ATMPVC ;
 rec -> input_info . atm . vp = 0 ;
 rec -> input_info . atm . vc = 0 ;
 }
 }
 if ( read_buffer [ K12_SRCDESC_HWPART + hwpart_len + name_len - 1 ] != '\0' ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup ( "k12_open: source descriptor record contains non-null-terminated link-layer name" ) ;
 destroy_k12_file_data ( file_data ) ;
 g_free ( rec ) ;
 return WTAP_OPEN_ERROR ;
 }
 if ( read_buffer [ K12_SRCDESC_HWPART + hwpart_len + name_len + stack_len - 1 ] != '\0' ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup ( "k12_open: source descriptor record contains non-null-terminated stack path" ) ;
 destroy_k12_file_data ( file_data ) ;
 g_free ( rec ) ;
 return WTAP_OPEN_ERROR ;
 }
 rec -> input_name = ( gchar * ) g_memdup ( read_buffer + K12_SRCDESC_HWPART + hwpart_len , name_len ) ;
 rec -> stack_file = ( gchar * ) g_memdup ( read_buffer + K12_SRCDESC_HWPART + hwpart_len + name_len , stack_len ) ;
 ascii_strdown_inplace ( rec -> stack_file ) ;
 g_hash_table_insert ( file_data -> src_by_id , GUINT_TO_POINTER ( rec -> input ) , rec ) ;
 g_hash_table_insert ( file_data -> src_by_name , rec -> stack_file , rec ) ;
 break ;
 case K12_REC_STK_FILE : K12_DBG ( 1 , ( "k12_open: K12_REC_STK_FILE" ) ) ;
 K12_DBG ( 1 , ( "Field 1: 0x%08x" , pntoh32 ( read_buffer + 0x08 ) ) ) ;
 K12_DBG ( 1 , ( "Field 2: 0x%08x" , pntoh32 ( read_buffer + 0x0c ) ) ) ;
 K12_ASCII_DUMP ( 1 , read_buffer , rec_len , 16 ) ;
 break ;
 default : K12_DBG ( 1 , ( "k12_open: RECORD TYPE 0x%08x" , type ) ) ;
 break ;
 }
 offset += len ;
 file_data -> num_of_records -- ;
 }
 while ( 1 ) ;
 wth -> file_type_subtype = WTAP_FILE_TYPE_SUBTYPE_K12 ;
 wth -> file_encap = WTAP_ENCAP_K12 ;
 wth -> snapshot_length = 0 ;
 wth -> subtype_read = k12_read ;
 wth -> subtype_seek_read = k12_seek_read ;
 wth -> subtype_close = k12_close ;
 wth -> priv = ( void * ) file_data ;
 wth -> file_tsprec = WTAP_TSPREC_NSEC ;
 return WTAP_OPEN_MINE ;
 }