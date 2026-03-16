static void set_pseudo_header_frame2 ( wtap * wth , union wtap_pseudo_header * pseudo_header , struct frame2_rec * frame2 ) {
 switch ( wth -> file_encap ) {
 case WTAP_ENCAP_ETHERNET : pseudo_header -> eth . fcs_len = 0 ;
 break ;
 case WTAP_ENCAP_PPP_WITH_PHDR : case WTAP_ENCAP_SDLC : pseudo_header -> p2p . sent = ( frame2 -> fs & FS_WAN_DTE ) ? TRUE : FALSE ;
 break ;
 case WTAP_ENCAP_LAPB : case WTAP_ENCAP_FRELAY_WITH_PHDR : case WTAP_ENCAP_PER_PACKET : pseudo_header -> x25 . flags = ( frame2 -> fs & FS_WAN_DTE ) ? 0x00 : FROM_DCE ;
 break ;
 case WTAP_ENCAP_ISDN : pseudo_header -> isdn . uton = ( frame2 -> fs & FS_WAN_DTE ) ? FALSE : TRUE ;
 switch ( frame2 -> fs & FS_ISDN_CHAN_MASK ) {
 case FS_ISDN_CHAN_D : pseudo_header -> isdn . channel = 0 ;
 break ;
 case FS_ISDN_CHAN_B1 : pseudo_header -> isdn . channel = 1 ;
 break ;
 case FS_ISDN_CHAN_B2 : pseudo_header -> isdn . channel = 2 ;
 break ;
 default : pseudo_header -> isdn . channel = 30 ;
 break ;
 }
 }
 }