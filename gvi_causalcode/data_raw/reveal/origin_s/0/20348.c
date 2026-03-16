static char * ts_unix_format ( netdissect_options * ndo # ifndef HAVE_PCAP_SET_TSTAMP_PRECISION _U_ # endif , int sec , int usec , char * buf ) {
 const char * format ;

 case PCAP_TSTAMP_PRECISION_MICRO : format = "%u.%06u" ;
 break ;
 case PCAP_TSTAMP_PRECISION_NANO : format = "%u.%09u" ;
 break ;
 default : format = "%u.{
unknown}
" ;
 break ;
 }


 return buf ;
 }