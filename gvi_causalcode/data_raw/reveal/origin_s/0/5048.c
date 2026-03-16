static gpointer btatt_handle_value ( packet_info * pinfo ) {
 guint16 * value_data ;
 value_data = ( guint16 * ) p_get_proto_data ( pinfo -> pool , pinfo , proto_btatt , PROTO_DATA_BTATT_HANDLE ) ;
 if ( value_data ) return GUINT_TO_POINTER ( ( gulong ) * value_data ) ;
 return NULL ;
 }