static int64_t ogg_calc_pts ( AVFormatContext * s , int idx , int64_t * dts ) {
 struct ogg * ogg = s -> priv_data ;
 struct ogg_stream * os = ogg -> streams + idx ;
 int64_t pts = AV_NOPTS_VALUE ;
 if ( dts ) * dts = AV_NOPTS_VALUE ;
 if ( os -> lastpts != AV_NOPTS_VALUE ) {
 pts = os -> lastpts ;
 os -> lastpts = AV_NOPTS_VALUE ;
 }
 if ( os -> lastdts != AV_NOPTS_VALUE ) {
 if ( dts ) * dts = os -> lastdts ;
 os -> lastdts = AV_NOPTS_VALUE ;
 }
 if ( os -> page_end ) {
 if ( os -> granule != - 1LL ) {
 if ( os -> codec && os -> codec -> granule_is_start ) pts = ogg_gptopts ( s , idx , os -> granule , dts ) ;
 else os -> lastpts = ogg_gptopts ( s , idx , os -> granule , & os -> lastdts ) ;
 os -> granule = - 1LL ;
 }
 }
 return pts ;
 }