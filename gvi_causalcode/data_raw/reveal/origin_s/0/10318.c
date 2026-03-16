static int get_dns_name_type_class ( tvbuff_t * tvb , int offset , int dns_data_offset , const guchar * * name_ret , int * name_len_ret , int * type_ret , int * class_ret ) {
 int len ;
 int name_len ;
 int type ;
 int dns_class ;
 int start_offset = offset ;
 name_len = get_dns_name ( tvb , offset , 0 , dns_data_offset , name_ret ) ;
 offset += name_len ;
 type = tvb_get_ntohs ( tvb , offset ) ;
 offset += 2 ;
 dns_class = tvb_get_ntohs ( tvb , offset ) ;
 offset += 2 ;
 * type_ret = type ;
 * class_ret = dns_class ;
 * name_len_ret = name_len ;
 len = offset - start_offset ;
 return len ;
 }