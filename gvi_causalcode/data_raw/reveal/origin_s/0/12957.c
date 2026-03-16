int dissect_ber_GeneralString ( asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint hf_id , char * name_string , guint name_len ) {
 tvbuff_t * out_tvb = NULL ;
 gint tvb_len ;
 offset = dissect_ber_restricted_string ( FALSE , BER_UNI_TAG_GeneralString , actx , tree , tvb , offset , hf_id , ( name_string ) ? & out_tvb : NULL ) ;
 if ( name_string ) {
 if ( out_tvb ) {
 tvb_len = tvb_reported_length ( out_tvb ) ;
 if ( ( guint ) tvb_len >= name_len ) {
 tvb_memcpy ( out_tvb , ( guint8 * ) name_string , 0 , name_len - 1 ) ;
 name_string [ name_len - 1 ] = '\0' ;
 }
 else {
 tvb_memcpy ( out_tvb , ( guint8 * ) name_string , 0 , tvb_len ) ;
 name_string [ tvb_len ] = '\0' ;
 }
 }
 }
 return offset ;
 }