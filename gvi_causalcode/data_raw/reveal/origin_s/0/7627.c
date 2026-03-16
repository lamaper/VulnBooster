static __inline__ int TCM_SET ( void * msg , __u16 cmd , __u16 flags , void * data , __u16 data_len ) {
 struct tipc_cfg_msg_hdr * tcm_hdr ;
 int msg_len ;
 msg_len = TCM_LENGTH ( data_len ) ;
 tcm_hdr = ( struct tipc_cfg_msg_hdr * ) msg ;
 tcm_hdr -> tcm_len = htonl ( msg_len ) ;
 tcm_hdr -> tcm_type = htons ( cmd ) ;
 tcm_hdr -> tcm_flags = htons ( flags ) ;
 if ( data_len && data ) {
 memcpy ( TCM_DATA ( msg ) , data , data_len ) ;
 memset ( TCM_DATA ( msg ) + data_len , 0 , TCM_SPACE ( data_len ) - msg_len ) ;
 }
 return TCM_SPACE ( data_len ) ;
 }