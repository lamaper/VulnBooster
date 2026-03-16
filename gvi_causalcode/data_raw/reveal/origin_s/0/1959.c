tvbuff_t * tvb_child_uncompress ( tvbuff_t * parent , tvbuff_t * tvb , const int offset , int comprlen ) {
 tvbuff_t * new_tvb = tvb_uncompress ( tvb , offset , comprlen ) ;
 if ( new_tvb ) tvb_set_child_real_data_tvbuff ( parent , new_tvb ) ;
 return new_tvb ;
 }