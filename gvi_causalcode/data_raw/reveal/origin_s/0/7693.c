static inline void save_to_qmem ( unsigned char * qmem_cmc , unsigned short * qmem_type , int qmem_len , int * qmem_lastfilled , unsigned char * cmc_to_add , unsigned short type_to_add ) {
 int fill ;
 fill = * qmem_lastfilled + 1 ;
 if ( fill >= qmem_len ) fill = 0 ;
 memcpy ( qmem_cmc + fill * 4 , cmc_to_add , 4 ) ;
 qmem_type [ fill ] = type_to_add ;
 * qmem_lastfilled = fill ;
 }