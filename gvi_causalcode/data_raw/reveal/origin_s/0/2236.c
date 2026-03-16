static inline RV34VLC * choose_vlc_set ( int quant , int mod , int type ) {
 if ( mod == 2 && quant < 19 ) quant += 10 ;
 else if ( mod && quant < 26 ) quant += 5 ;
 return type ? & inter_vlcs [ rv34_quant_to_vlc_set [ 1 ] [ av_clip ( quant , 0 , 30 ) ] ] : & intra_vlcs [ rv34_quant_to_vlc_set [ 0 ] [ av_clip ( quant , 0 , 30 ) ] ] ;
 }