static void pcnet_bcr_writew ( PCNetState * s , uint32_t rap , uint32_t val ) {
 rap &= 127 ;


 case BCR_SWS : if ( ! ( CSR_STOP ( s ) || CSR_SPND ( s ) ) ) return ;
 val &= ~ 0x0300 ;
 switch ( val & 0x00ff ) {
 case 0 : val |= 0x0200 ;
 break ;
 case 1 : val |= 0x0100 ;
 break ;
 case 2 : case 3 : val |= 0x0300 ;
 break ;
 default : printf ( "Bad SWSTYLE=0x%02x\n" , val & 0xff ) ;
 val = 0x0200 ;
 break ;
 }


 break ;
 default : break ;
 }
 }