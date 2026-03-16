static void * set_bootinfo_tag ( void * addr , uint32_t tag , uint32_t size , void * data ) {
 char * pos = addr ;
 put_long ( pos , tag ) ;
 pos += 4 ;
 put_long ( pos , size + 8 ) ;
 pos += 4 ;
 memcpy ( pos , data , size ) ;
 pos += size ;
 return pos ;
 }