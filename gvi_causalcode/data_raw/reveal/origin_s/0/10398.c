static int dissect_diameter_user_name ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 diam_sub_dis_t * diam_sub_dis = ( diam_sub_dis_t * ) data ;
 guint32 application_id = 0 , str_len ;
 if ( diam_sub_dis ) {
 application_id = diam_sub_dis -> application_id ;
 }
 switch ( application_id ) {
 case DIAM_APPID_3GPP_S6A_S6D : case DIAM_APPID_3GPP_SLH : case DIAM_APPID_3GPP_S7A : str_len = tvb_reported_length ( tvb ) ;
 dissect_e212_utf8_imsi ( tvb , pinfo , tree , 0 , str_len ) ;
 return str_len ;
 }
 return 0 ;
 }