static void nvram_init ( M48t59State * nvram , uint8_t * macaddr , const char * cmdline , const char * boot_devices , ram_addr_t RAM_size , uint32_t kernel_size , int width , int height , int depth , int nvram_machine_id , const char * arch ) {
 unsigned int i ;
 uint32_t start , end ;
 uint8_t image [ 0x1ff0 ] ;
 struct OpenBIOS_nvpart_v1 * part_header ;
 memset ( image , '\0' , sizeof ( image ) ) ;
 start = 0 ;
 part_header = ( struct OpenBIOS_nvpart_v1 * ) & image [ start ] ;
 part_header -> signature = OPENBIOS_PART_SYSTEM ;
 pstrcpy ( part_header -> name , sizeof ( part_header -> name ) , "system" ) ;
 end = start + sizeof ( struct OpenBIOS_nvpart_v1 ) ;
 for ( i = 0 ;
 i < nb_prom_envs ;
 i ++ ) end = OpenBIOS_set_var ( image , end , prom_envs [ i ] ) ;
 image [ end ++ ] = '\0' ;
 end = start + ( ( end - start + 15 ) & ~ 15 ) ;
 OpenBIOS_finish_partition ( part_header , end - start ) ;
 start = end ;
 part_header = ( struct OpenBIOS_nvpart_v1 * ) & image [ start ] ;
 part_header -> signature = OPENBIOS_PART_FREE ;
 pstrcpy ( part_header -> name , sizeof ( part_header -> name ) , "free" ) ;
 end = 0x1fd0 ;
 OpenBIOS_finish_partition ( part_header , end - start ) ;
 Sun_init_header ( ( struct Sun_nvram * ) & image [ 0x1fd8 ] , macaddr , nvram_machine_id ) ;
 for ( i = 0 ;
 i < sizeof ( image ) ;
 i ++ ) m48t59_write ( nvram , i , image [ i ] ) ;
 }