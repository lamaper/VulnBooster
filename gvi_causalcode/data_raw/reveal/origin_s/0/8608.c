static gboolean extcap_dumper_dump ( struct extcap_dumper extcap_dumper , char * buffer , gssize captured_length , gssize reported_length , time_t seconds , int nanoseconds ) {

 pcap_header . caplen = ( bpf_u_int32 ) captured_length ;
 pcap_header . len = ( bpf_u_int32 ) reported_length ;
 pcap_header . ts . tv_sec = seconds ;
 pcap_header . ts . tv_usec = nanoseconds / 1000 ;
 pcap_dump ( ( u_char * ) extcap_dumper . dumper . pcap , & pcap_header , buffer ) ;
 pcap_dump_flush ( extcap_dumper . dumper . pcap ) ;

 char * err_info ;
 struct wtap_pkthdr hdr ;
 hdr . presence_flags = WTAP_HAS_TS ;
 hdr . caplen = ( guint32 ) captured_length ;
 hdr . len = ( guint32 ) reported_length ;
 hdr . ts . secs = seconds ;
 hdr . ts . nsecs = ( int ) nanoseconds ;
 hdr . opt_comment = 0 ;
 hdr . opt_comment = NULL ;
 hdr . drop_count = 0 ;
 hdr . pack_flags = 0 ;
 hdr . rec_type = REC_TYPE_PACKET ;
 if ( extcap_dumper . encap == EXTCAP_ENCAP_BLUETOOTH_H4_WITH_PHDR ) {
 uint32_t * direction ;
 SET_DATA ( direction , value_u32 , buffer ) hdr . pseudo_header . bthci . sent = GINT32_FROM_BE ( * direction ) ? 0 : 1 ;
 hdr . len -= ( guint32 ) sizeof ( own_pcap_bluetooth_h4_header ) ;
 hdr . caplen -= ( guint32 ) sizeof ( own_pcap_bluetooth_h4_header ) ;
 buffer += sizeof ( own_pcap_bluetooth_h4_header ) ;
 hdr . pkt_encap = WTAP_ENCAP_BLUETOOTH_H4_WITH_PHDR ;
 }
 else if ( extcap_dumper . encap == EXTCAP_ENCAP_ETHERNET ) {
 hdr . pkt_encap = WTAP_ENCAP_ETHERNET ;
 }
 else {
 hdr . pkt_encap = WTAP_ENCAP_WIRESHARK_UPPER_PDU ;
 }
 if ( ! wtap_dump ( extcap_dumper . dumper . wtap , & hdr , ( const guint8 * ) buffer , & err , & err_info ) ) {
 errmsg_print ( "ERROR: Cannot dump: %s" , err_info ) ;
 return FALSE ;
 }
 wtap_dump_flush ( extcap_dumper . dumper . wtap ) ;

 }