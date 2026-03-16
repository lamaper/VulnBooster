int get_dns_name ( tvbuff_t * tvb , int offset , int max_len , int dns_data_offset , const guchar * * name ) {
 int len ;
 len = expand_dns_name ( tvb , offset , max_len , dns_data_offset , name ) ;
 if ( * * name == '\0' ) {
 * name = "<Root>" ;
 }
 return len ;
 }