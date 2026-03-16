static void set_pseudo_header_frame6 ( wtap * wth , union wtap_pseudo_header * pseudo_header , struct frame6_rec * frame6 _U_ ) {
 switch ( wth -> file_encap ) {
 case WTAP_ENCAP_ETHERNET : pseudo_header -> eth . fcs_len = - 1 ;
 break ;
 }
 }