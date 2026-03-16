static struct extcap_dumper extcap_dumper_open ( char * fifo , int encap ) {
 struct extcap_dumper extcap_dumper ;
 int encap_ext ;

 if ( encap == EXTCAP_ENCAP_BLUETOOTH_H4_WITH_PHDR ) encap_ext = DLT_BLUETOOTH_H4_WITH_PHDR ;
 else if ( encap == EXTCAP_ENCAP_WIRESHARK_UPPER_PDU ) encap_ext = DLT_WIRESHARK_UPPER_PDU ;
 else if ( encap == EXTCAP_ENCAP_ETHERNET ) encap_ext = DLT_EN10MB ;
 else {
 errmsg_print ( "ERROR: Unknown encapsulation" ) ;
 exit ( EXIT_CODE_UNKNOWN_ENCAPSULATION_LIBPCAP ) ;
 }
 pcap = pcap_open_dead_with_tstamp_precision ( encap_ext , PACKET_LENGTH , PCAP_TSTAMP_PRECISION_NANO ) ;
 extcap_dumper . dumper . pcap = pcap_dump_open ( pcap , fifo ) ;
 if ( ! extcap_dumper . dumper . pcap ) {
 errmsg_print ( "ERROR: Cannot save lipcap dump file" ) ;
 exit ( EXIT_CODE_CANNOT_SAVE_LIBPCAP_DUMP ) ;
 }
 extcap_dumper . encap = encap ;
 pcap_dump_flush ( extcap_dumper . dumper . pcap ) ;

 wtap_init ( ) ;


 else if ( encap == EXTCAP_ENCAP_WIRESHARK_UPPER_PDU ) encap_ext = WTAP_ENCAP_WIRESHARK_UPPER_PDU ;
 else if ( encap == EXTCAP_ENCAP_ETHERNET ) encap_ext = WTAP_ENCAP_ETHERNET ;
 else {
 errmsg_print ( "ERROR: Unknown Wiretap encapsulation" ) ;
 exit ( EXIT_CODE_UNKNOWN_ENCAPSULATION_WIRETAP ) ;
 }
 extcap_dumper . dumper . wtap = wtap_dump_open ( fifo , WTAP_FILE_TYPE_SUBTYPE_PCAP_NSEC , encap_ext , PACKET_LENGTH , FALSE , & err ) ;
 if ( ! extcap_dumper . dumper . wtap ) {
 errmsg_print ( "ERROR: Cannot save dump file" ) ;
 exit ( EXIT_CODE_CANNOT_SAVE_WIRETAP_DUMP ) ;
 }
 extcap_dumper . encap = encap ;
 wtap_dump_flush ( extcap_dumper . dumper . wtap ) ;

 }