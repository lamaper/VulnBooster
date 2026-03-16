static void dca_downmix ( float * * samples , int srcfmt , int downmix_coef [ DCA_PRIM_CHANNELS_MAX ] [ 2 ] , const int8_t * channel_mapping ) {
 int c , l , r , sl , sr , s ;
 int i ;
 float t , u , v ;
 float coef [ DCA_PRIM_CHANNELS_MAX ] [ 2 ] ;
 for ( i = 0 ;
 i < DCA_PRIM_CHANNELS_MAX ;
 i ++ ) {
 coef [ i ] [ 0 ] = dca_downmix_coeffs [ downmix_coef [ i ] [ 0 ] ] ;
 coef [ i ] [ 1 ] = dca_downmix_coeffs [ downmix_coef [ i ] [ 1 ] ] ;
 }
 switch ( srcfmt ) {
 case DCA_MONO : case DCA_CHANNEL : case DCA_STEREO_TOTAL : case DCA_STEREO_SUMDIFF : case DCA_4F2R : av_log ( NULL , 0 , "Not implemented!\n" ) ;
 break ;
 case DCA_STEREO : break ;
 case DCA_3F : c = channel_mapping [ 0 ] ;
 l = channel_mapping [ 1 ] ;
 r = channel_mapping [ 2 ] ;
 DOWNMIX_TO_STEREO ( MIX_FRONT3 ( samples , coef ) , ) ;
 break ;
 case DCA_2F1R : s = channel_mapping [ 2 ] ;
 DOWNMIX_TO_STEREO ( MIX_REAR1 ( samples , s , 2 , coef ) , ) ;
 break ;
 case DCA_3F1R : c = channel_mapping [ 0 ] ;
 l = channel_mapping [ 1 ] ;
 r = channel_mapping [ 2 ] ;
 s = channel_mapping [ 3 ] ;
 DOWNMIX_TO_STEREO ( MIX_FRONT3 ( samples , coef ) , MIX_REAR1 ( samples , s , 3 , coef ) ) ;
 break ;
 case DCA_2F2R : sl = channel_mapping [ 2 ] ;
 sr = channel_mapping [ 3 ] ;
 DOWNMIX_TO_STEREO ( MIX_REAR2 ( samples , sl , sr , 2 , coef ) , ) ;
 break ;
 case DCA_3F2R : c = channel_mapping [ 0 ] ;
 l = channel_mapping [ 1 ] ;
 r = channel_mapping [ 2 ] ;
 sl = channel_mapping [ 3 ] ;
 sr = channel_mapping [ 4 ] ;
 DOWNMIX_TO_STEREO ( MIX_FRONT3 ( samples , coef ) , MIX_REAR2 ( samples , sl , sr , 3 , coef ) ) ;
 break ;
 }
 }