static int doubledl ( char * * scur , uint8_t * mydlptr , char * buffer , uint32_t buffersize ) {
 unsigned char mydl = * mydlptr ;
 unsigned char olddl = mydl ;
 mydl *= 2 ;
 if ( ! ( olddl & 0x7f ) ) {
 if ( * scur < buffer || * scur >= buffer + buffersize - 1 ) return - 1 ;
 olddl = * * scur ;
 mydl = olddl * 2 + 1 ;
 * scur = * scur + 1 ;
 }
 * mydlptr = mydl ;
 return ( olddl >> 7 ) & 1 ;
 }