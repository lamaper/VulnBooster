static gboolean ngsniffer_dump ( wtap_dumper * wdh , const struct wtap_pkthdr * phdr , const guint8 * pd , int * err , gchar * * err_info _U_ ) {
 const union wtap_pseudo_header * pseudo_header = & phdr -> pseudo_header ;
 ngsniffer_dump_t * ngsniffer = ( ngsniffer_dump_t * ) wdh -> priv ;
 struct frame2_rec rec_hdr ;
 char buf [ 6 ] ;
 time_t tsecs ;
 guint64 t ;
 guint16 t_low , t_med ;
 guint8 t_high ;
 struct vers_rec version ;
 gint16 maj_vers , min_vers ;
 guint16 start_date ;
 struct tm * tm ;
 if ( phdr -> rec_type != REC_TYPE_PACKET ) {
 * err = WTAP_ERR_UNWRITABLE_REC_TYPE ;
 return FALSE ;
 }
 if ( phdr -> caplen > 65535 ) {
 * err = WTAP_ERR_PACKET_TOO_LARGE ;
 return FALSE ;
 }
 if ( ngsniffer -> first_frame ) {
 ngsniffer -> first_frame = FALSE ;
 tm = localtime ( & phdr -> ts . secs ) ;
 if ( tm != NULL && tm -> tm_year >= DOS_YEAR_OFFSET ) {
 start_date = ( tm -> tm_year - DOS_YEAR_OFFSET ) << DOS_YEAR_SHIFT ;
 start_date |= ( tm -> tm_mon - DOS_MONTH_OFFSET ) << DOS_MONTH_SHIFT ;
 start_date |= tm -> tm_mday << DOS_DAY_SHIFT ;
 ngsniffer -> start = phdr -> ts . secs - ( 3600 * tm -> tm_hour + 60 * tm -> tm_min + tm -> tm_sec ) ;
 }
 else {
 start_date = 0 ;
 ngsniffer -> start = 0 ;
 }
 maj_vers = 4 ;
 min_vers = 0 ;
 version . maj_vers = GUINT16_TO_LE ( maj_vers ) ;
 version . min_vers = GUINT16_TO_LE ( min_vers ) ;
 version . time = 0 ;
 version . date = GUINT16_TO_LE ( start_date ) ;
 version . type = 4 ;
 version . network = wtap_encap [ wdh -> encap ] ;
 version . format = 1 ;
 version . timeunit = 1 ;
 version . cmprs_vers = 0 ;
 version . cmprs_level = 0 ;
 version . rsvd [ 0 ] = 0 ;
 version . rsvd [ 1 ] = 0 ;
 if ( ! wtap_dump_file_write ( wdh , & version , sizeof version , err ) ) return FALSE ;
 }
 buf [ 0 ] = REC_FRAME2 ;
 buf [ 1 ] = 0x00 ;
 buf [ 2 ] = ( char ) ( ( phdr -> caplen + sizeof ( struct frame2_rec ) ) % 256 ) ;
 buf [ 3 ] = ( char ) ( ( phdr -> caplen + sizeof ( struct frame2_rec ) ) / 256 ) ;
 buf [ 4 ] = 0x00 ;
 buf [ 5 ] = 0x00 ;
 if ( ! wtap_dump_file_write ( wdh , buf , 6 , err ) ) return FALSE ;
 tsecs = phdr -> ts . secs - ngsniffer -> start ;
 rec_hdr . time_day = ( guint8 ) ( tsecs / 86400 ) ;
 tsecs -= rec_hdr . time_day * 86400 ;
 t = tsecs * G_GUINT64_CONSTANT ( 1000000000000 ) + phdr -> ts . nsecs * G_GUINT64_CONSTANT ( 1000 ) ;
 t /= Psec [ 1 ] ;
 t_low = ( guint16 ) ( ( t >> 0 ) & 0xFFFF ) ;
 t_med = ( guint16 ) ( ( t >> 16 ) & 0xFFFF ) ;
 t_high = ( guint8 ) ( ( t >> 32 ) & 0xFF ) ;
 rec_hdr . time_low = GUINT16_TO_LE ( t_low ) ;
 rec_hdr . time_med = GUINT16_TO_LE ( t_med ) ;
 rec_hdr . time_high = t_high ;
 rec_hdr . size = GUINT16_TO_LE ( phdr -> caplen ) ;
 switch ( wdh -> encap ) {
 case WTAP_ENCAP_LAPB : case WTAP_ENCAP_FRELAY_WITH_PHDR : rec_hdr . fs = ( pseudo_header -> x25 . flags & FROM_DCE ) ? 0x00 : FS_WAN_DTE ;
 break ;
 case WTAP_ENCAP_PPP_WITH_PHDR : case WTAP_ENCAP_SDLC : rec_hdr . fs = pseudo_header -> p2p . sent ? 0x00 : FS_WAN_DTE ;
 break ;
 case WTAP_ENCAP_ISDN : rec_hdr . fs = pseudo_header -> isdn . uton ? FS_WAN_DTE : 0x00 ;
 switch ( pseudo_header -> isdn . channel ) {
 case 0 : rec_hdr . fs |= FS_ISDN_CHAN_D ;
 break ;
 case 1 : rec_hdr . fs |= FS_ISDN_CHAN_B1 ;
 break ;
 case 2 : rec_hdr . fs |= FS_ISDN_CHAN_B2 ;
 break ;
 }
 break ;
 default : rec_hdr . fs = 0 ;
 break ;
 }
 rec_hdr . flags = 0 ;
 rec_hdr . true_size = phdr -> len != phdr -> caplen ? GUINT16_TO_LE ( phdr -> len ) : 0 ;
 rec_hdr . rsvd = 0 ;
 if ( ! wtap_dump_file_write ( wdh , & rec_hdr , sizeof rec_hdr , err ) ) return FALSE ;
 if ( ! wtap_dump_file_write ( wdh , pd , phdr -> caplen , err ) ) return FALSE ;
 return TRUE ;
 }