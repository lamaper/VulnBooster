int get_netbios_name ( tvbuff_t * tvb , int offset , char * name_ret , int name_ret_len ) {
 return process_netbios_name ( tvb_get_ptr ( tvb , offset , NETBIOS_NAME_LEN ) , name_ret , name_ret_len ) ;
 }