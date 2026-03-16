int CalculateCrc ( const unsigned char * buf , int size ) {
 CrcGenerateTable ( ) ;
 unsigned int crc = 0xffffffffL ;
 crc = ~ CrcCalc ( buf , size ) ;
 return crc ;
 }