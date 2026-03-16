static void dissect_field_value ( tvbuff_t * tvb , int offset , proto_tree * tree , guint16 field_type , int field_length , int encoding ) {
 switch ( field_type ) {
 case PDM_TYPE_BOOLEAN : proto_tree_add_item ( tree , hf_lbmpdm_field_value_boolean , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_INT8 : proto_tree_add_item ( tree , hf_lbmpdm_field_value_int8 , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_UINT8 : proto_tree_add_item ( tree , hf_lbmpdm_field_value_uint8 , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_INT16 : proto_tree_add_item ( tree , hf_lbmpdm_field_value_int16 , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_UINT16 : proto_tree_add_item ( tree , hf_lbmpdm_field_value_uint16 , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_INT32 : proto_tree_add_item ( tree , hf_lbmpdm_field_value_int32 , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_UINT32 : proto_tree_add_item ( tree , hf_lbmpdm_field_value_uint32 , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_INT64 : proto_tree_add_item ( tree , hf_lbmpdm_field_value_int64 , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_UINT64 : proto_tree_add_item ( tree , hf_lbmpdm_field_value_uint64 , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_FLOAT : proto_tree_add_item ( tree , hf_lbmpdm_field_value_float , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_DOUBLE : proto_tree_add_item ( tree , hf_lbmpdm_field_value_double , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_DECIMAL : {
 gint64 mantissa ;
 gint8 exponent ;
 gint64 whole = 0 ;
 guint64 fraction = 0 ;
 gint8 shift_count ;
 exponent = ( gint8 ) tvb_get_guint8 ( tvb , offset ) ;
 mantissa = ( gint64 ) lbmpdm_fetch_uint64_encoded ( tvb , offset + 1 , encoding ) ;
 if ( exponent >= 0 ) {
 whole = mantissa ;
 shift_count = exponent ;
 while ( shift_count > 0 ) {
 whole *= 10 ;
 shift_count -- ;
 }
 proto_tree_add_none_format ( tree , hf_lbmpdm_field_value_decimal , tvb , offset , field_length , "DECIMAL Value: %" G_GINT64_FORMAT " (%" G_GINT64_FORMAT "e%d)" , whole , mantissa , exponent ) ;
 }
 else {
 guint64 divisor = 1 ;
 int decimal_digits = - exponent ;
 shift_count = decimal_digits ;
 while ( shift_count > 0 ) {
 divisor *= 10 ;
 shift_count -- ;
 }
 if ( mantissa < 0 ) {
 whole = - mantissa ;
 }
 else {
 whole = mantissa ;
 }
 fraction = whole % divisor ;
 whole /= divisor ;
 if ( mantissa < 0 ) {
 whole *= - 1 ;
 }
 proto_tree_add_none_format ( tree , hf_lbmpdm_field_value_decimal , tvb , offset , field_length , "DECIMAL Value: %" G_GINT64_FORMAT ".%0*" G_GUINT64_FORMAT " (%" G_GINT64_FORMAT "e%d)" , whole , decimal_digits , fraction , mantissa , exponent ) ;
 }
 }
 break ;
 case PDM_TYPE_TIMESTAMP : {
 nstime_t timestamp ;
 timestamp . secs = ( time_t ) lbmpdm_fetch_uint32_encoded ( tvb , offset , encoding ) ;
 timestamp . nsecs = ( int ) ( lbmpdm_fetch_uint32_encoded ( tvb , offset + 4 , encoding ) * 1000 ) ;
 proto_tree_add_time ( tree , hf_lbmpdm_field_value_timestamp , tvb , offset , field_length , & timestamp ) ;
 }
 break ;
 case PDM_TYPE_FIX_STRING : proto_tree_add_item ( tree , hf_lbmpdm_field_value_fixed_string , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_STRING : proto_tree_add_item ( tree , hf_lbmpdm_field_value_string , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_FIX_UNICODE : proto_tree_add_item ( tree , hf_lbmpdm_field_value_fixed_unicode , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_UNICODE : proto_tree_add_item ( tree , hf_lbmpdm_field_value_unicode , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_BLOB : proto_tree_add_item ( tree , hf_lbmpdm_field_value_blob , tvb , offset , field_length , encoding ) ;
 break ;
 case PDM_TYPE_MESSAGE : proto_tree_add_item ( tree , hf_lbmpdm_field_value_message , tvb , offset , field_length , encoding ) ;
 break ;
 default : break ;
 }
 }