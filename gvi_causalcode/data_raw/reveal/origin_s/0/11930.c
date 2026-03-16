wtap_open_return_val ngsniffer_open ( wtap * wth , int * err , gchar * * err_info ) {
 char magic [ sizeof ngsniffer_magic ] ;
 char record_type [ 2 ] ;
 char record_length [ 4 ] ;
 guint16 type ;
 struct vers_rec version ;
 guint16 maj_vers ;
 guint16 start_date ;


 WTAP_ENCAP_TOKEN_RING , WTAP_ENCAP_ETHERNET , WTAP_ENCAP_ARCNET , WTAP_ENCAP_UNKNOWN , WTAP_ENCAP_UNKNOWN , WTAP_ENCAP_UNKNOWN , WTAP_ENCAP_UNKNOWN , WTAP_ENCAP_PER_PACKET , WTAP_ENCAP_PER_PACKET , WTAP_ENCAP_FDDI_BITSWAPPED , WTAP_ENCAP_ATM_PDUS }
 ;

 gint64 current_offset ;
 ngsniffer_t * ngsniffer ;
 if ( ! wtap_read_bytes ( wth -> fh , magic , sizeof magic , err , err_info ) ) {
 if ( * err != WTAP_ERR_SHORT_READ ) return WTAP_OPEN_ERROR ;
 return WTAP_OPEN_NOT_MINE ;
 }
 if ( memcmp ( magic , ngsniffer_magic , sizeof ngsniffer_magic ) ) {
 return WTAP_OPEN_NOT_MINE ;
 }
 if ( ! wtap_read_bytes ( wth -> fh , record_type , 2 , err , err_info ) ) return WTAP_OPEN_ERROR ;
 if ( ! wtap_read_bytes ( wth -> fh , record_length , 4 , err , err_info ) ) return WTAP_OPEN_ERROR ;
 type = pletoh16 ( record_type ) ;
 if ( type != REC_VERS ) {
 * err = WTAP_ERR_BAD_FILE ;
 * err_info = g_strdup_printf ( "ngsniffer: Sniffer file doesn't start with a version record" ) ;
 return WTAP_OPEN_ERROR ;
 }
 if ( ! wtap_read_bytes ( wth -> fh , & version , sizeof version , err , err_info ) ) return WTAP_OPEN_ERROR ;
 if ( version . network >= NUM_NGSNIFF_ENCAPS || sniffer_encap [ version . network ] == WTAP_ENCAP_UNKNOWN ) {
 * err = WTAP_ERR_UNSUPPORTED ;
 * err_info = g_strdup_printf ( "ngsniffer: network type %u unknown or unsupported" , version . network ) ;
 return WTAP_OPEN_ERROR ;
 }
 if ( version . timeunit >= NUM_NGSNIFF_TIMEUNITS ) {
 * err = WTAP_ERR_UNSUPPORTED ;
 * err_info = g_strdup_printf ( "ngsniffer: Unknown timeunit %u" , version . timeunit ) ;
 return WTAP_OPEN_ERROR ;
 }
 if ( version . format != 1 ) {
 wth -> file_type_subtype = WTAP_FILE_TYPE_SUBTYPE_NGSNIFFER_COMPRESSED ;
 }
 else {
 wth -> file_type_subtype = WTAP_FILE_TYPE_SUBTYPE_NGSNIFFER_UNCOMPRESSED ;
 }
 wth -> file_encap = sniffer_encap [ version . network ] ;
 maj_vers = pletoh16 ( & version . maj_vers ) ;
 if ( process_header_records ( wth , err , err_info , maj_vers , version . network ) < 0 ) return WTAP_OPEN_ERROR ;
 if ( ( version . network == NETWORK_SYNCHRO || version . network == NETWORK_ASYNC ) && wth -> file_encap == WTAP_ENCAP_PER_PACKET ) {
 switch ( maj_vers ) {
 case 1 : switch ( pletoh16 ( & version . rsvd [ 0 ] ) ) {
 case 1 : case 2 : wth -> file_encap = WTAP_ENCAP_ISDN ;
 break ;
 }
 break ;
 case 3 : wth -> file_encap = WTAP_ENCAP_FRELAY_WITH_PHDR ;
 break ;
 }
 }
 current_offset = file_tell ( wth -> fh ) ;
 if ( wth -> random_fh != NULL ) {
 if ( file_seek ( wth -> random_fh , current_offset , SEEK_SET , err ) == - 1 ) return WTAP_OPEN_ERROR ;
 }
 ngsniffer = ( ngsniffer_t * ) g_malloc ( sizeof ( ngsniffer_t ) ) ;
 wth -> priv = ( void * ) ngsniffer ;
 ngsniffer -> maj_vers = maj_vers ;
 ngsniffer -> min_vers = pletoh16 ( & version . min_vers ) ;
 ngsniffer -> seq . buf = NULL ;
 ngsniffer -> seq . nbytes = 0 ;
 ngsniffer -> seq . nextout = 0 ;
 ngsniffer -> rand . buf = NULL ;
 ngsniffer -> rand . nbytes = 0 ;
 ngsniffer -> rand . nextout = 0 ;
 ngsniffer -> seq . uncomp_offset = current_offset ;
 ngsniffer -> seq . comp_offset = current_offset ;
 ngsniffer -> rand . uncomp_offset = current_offset ;
 ngsniffer -> rand . comp_offset = current_offset ;
 ngsniffer -> first_blob = NULL ;
 ngsniffer -> last_blob = NULL ;
 ngsniffer -> current_blob = NULL ;
 wth -> subtype_read = ngsniffer_read ;
 wth -> subtype_seek_read = ngsniffer_seek_read ;
 wth -> subtype_sequential_close = ngsniffer_sequential_close ;
 wth -> subtype_close = ngsniffer_close ;
 wth -> snapshot_length = 0 ;
 ngsniffer -> timeunit = Psec [ version . timeunit ] ;
 ngsniffer -> network = version . network ;
 start_date = pletoh16 ( & version . date ) ;
 tm . tm_year = ( ( start_date & DOS_YEAR_MASK ) >> DOS_YEAR_SHIFT ) + DOS_YEAR_OFFSET ;
 tm . tm_mon = ( ( start_date & DOS_MONTH_MASK ) >> DOS_MONTH_SHIFT ) + DOS_MONTH_OFFSET ;
 tm . tm_mday = ( ( start_date & DOS_DAY_MASK ) >> DOS_DAY_SHIFT ) ;

 tm . tm_hour = ( start_time & 0xf800 ) >> 11 ;
 tm . tm_min = ( start_time & 0x7e0 ) >> 5 ;
 tm . tm_sec = ( start_time & 0x1f ) << 1 ;

 tm . tm_min = 0 ;
 tm . tm_sec = 0 ;
 tm . tm_isdst = - 1 ;
 ngsniffer -> start = mktime ( & tm ) ;
 wth -> file_tsprec = WTAP_TSPREC_NSEC ;
 return WTAP_OPEN_MINE ;
 }