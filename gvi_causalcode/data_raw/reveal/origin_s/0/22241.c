void dissect_cipsafety_ssn ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo _U_ , int offset , int hf_real_datetime , int hf_date , int hf_time ) {
 guint16 date ;
 date = tvb_get_letohs ( tvb , offset ) ;
 if ( ( date >= 11688 ) && ( date <= 65534 ) ) {
 dissect_cip_date_and_time ( tree , tvb , offset , hf_real_datetime ) ;
 }
 else {
 proto_tree_add_item ( tree , hf_date , tvb , offset , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_time , tvb , offset + 2 , 4 , ENC_LITTLE_ENDIAN ) ;
 }
 }