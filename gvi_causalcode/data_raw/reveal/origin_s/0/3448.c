static char * checkpe ( char * dst , uint32_t dsize , char * pehdr , uint32_t * valign , unsigned int * sectcnt ) {
 char * sections ;
 if ( ! CLI_ISCONTAINED ( dst , dsize , pehdr , 0xf8 ) ) return NULL ;
 if ( cli_readint32 ( pehdr ) != 0x4550 ) return NULL ;
 if ( ! ( * valign = cli_readint32 ( pehdr + 0x38 ) ) ) return NULL ;
 sections = pehdr + 0xf8 ;
 if ( ! ( * sectcnt = ( unsigned char ) pehdr [ 6 ] + ( unsigned char ) pehdr [ 7 ] * 256 ) ) return NULL ;
 if ( ! CLI_ISCONTAINED ( dst , dsize , sections , * sectcnt * 0x28 ) ) return NULL ;
 return sections ;
 }