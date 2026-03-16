static char * ts_format ( netdissect_options * ndo # ifndef HAVE_PCAP_SET_TSTAMP_PRECISION _U_ # endif , int sec , int usec , char * buf ) {
 const char * format ;

 case PCAP_TSTAMP_PRECISION_MICRO : format = "%02d:%02d:%02d.%06u" ;
 break ;
 case PCAP_TSTAMP_PRECISION_NANO : format = "%02d:%02d:%02d.%09u" ;
 break ;
 default : format = "%02d:%02d:%02d.{
unknown}
" ;
 break ;
 }


 return buf ;
 }