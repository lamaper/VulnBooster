static int dissect_diameter_subscription_id_data ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 guint32 str_len ;
 switch ( subscription_id_type ) {
 case SUBSCRIPTION_ID_TYPE_IMSI : str_len = tvb_reported_length ( tvb ) ;
 dissect_e212_utf8_imsi ( tvb , pinfo , tree , 0 , str_len ) ;
 return str_len ;
 case SUBSCRIPTION_ID_TYPE_E164 : str_len = tvb_reported_length ( tvb ) ;
 dissect_e164_msisdn ( tvb , tree , 0 , str_len , E164_ENC_UTF8 ) ;
 return str_len ;
 break ;
 }
 return 0 ;
 }