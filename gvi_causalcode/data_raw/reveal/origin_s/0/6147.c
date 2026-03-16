int logcat_dump_can_write_encap ( int encap ) {
 if ( encap == WTAP_ENCAP_PER_PACKET ) return WTAP_ERR_ENCAP_PER_PACKET_UNSUPPORTED ;
 if ( encap != WTAP_ENCAP_LOGCAT ) return WTAP_ERR_UNSUPPORTED_ENCAP ;
 return 0 ;
 }