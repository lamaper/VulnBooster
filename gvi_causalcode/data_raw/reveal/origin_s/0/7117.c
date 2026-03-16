int ngsniffer_dump_can_write_encap ( int encap ) {
 if ( encap == WTAP_ENCAP_PER_PACKET ) return WTAP_ERR_ENCAP_PER_PACKET_UNSUPPORTED ;
 if ( encap < 0 || ( unsigned ) encap >= NUM_WTAP_ENCAPS || wtap_encap [ encap ] == - 1 ) return WTAP_ERR_UNWRITABLE_ENCAP ;
 return 0 ;
 }