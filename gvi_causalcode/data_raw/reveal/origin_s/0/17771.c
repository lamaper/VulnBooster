static proto_item * ber_proto_tree_add_item ( packet_info * pinfo , proto_tree * tree , const int hfindex , tvbuff_t * tvb , const gint start , gint length , const guint encoding ) {
 header_field_info * hfinfo ;
 hfinfo = proto_registrar_get_nth ( ( guint ) hfindex ) ;
 if ( hfinfo != NULL ) {
 switch ( hfinfo -> type ) {
 case FT_BOOLEAN : case FT_UINT8 : case FT_UINT16 : case FT_UINT24 : case FT_UINT32 : case FT_INT8 : case FT_INT16 : case FT_INT24 : case FT_INT32 : if ( ( length != 1 ) && ( length != 2 ) && ( length != 3 ) && ( length != 4 ) ) return ber_add_bad_length_error ( pinfo , tree , hfinfo -> name , tvb , start , length ) ;
 break ;
 case FT_IPv4 : if ( length != FT_IPv4_LEN ) return ber_add_bad_length_error ( pinfo , tree , hfinfo -> name , tvb , start , length ) ;
 break ;
 case FT_IPXNET : if ( length != FT_IPXNET_LEN ) return ber_add_bad_length_error ( pinfo , tree , hfinfo -> name , tvb , start , length ) ;
 break ;
 case FT_IPv6 : if ( ( length < 0 ) || ( length > FT_IPv6_LEN ) ) return ber_add_bad_length_error ( pinfo , tree , hfinfo -> name , tvb , start , length ) ;
 break ;
 case FT_ETHER : if ( length != FT_ETHER_LEN ) return ber_add_bad_length_error ( pinfo , tree , hfinfo -> name , tvb , start , length ) ;
 break ;
 case FT_GUID : if ( length != FT_GUID_LEN ) return ber_add_bad_length_error ( pinfo , tree , hfinfo -> name , tvb , start , length ) ;
 break ;
 case FT_FLOAT : if ( length != 4 ) return ber_add_bad_length_error ( pinfo , tree , hfinfo -> name , tvb , start , length ) ;
 break ;
 case FT_DOUBLE : if ( length != 8 ) return ber_add_bad_length_error ( pinfo , tree , hfinfo -> name , tvb , start , length ) ;
 break ;
 case FT_ABSOLUTE_TIME : case FT_RELATIVE_TIME : if ( ( length != 4 ) && ( length != 8 ) ) return ber_add_bad_length_error ( pinfo , tree , hfinfo -> name , tvb , start , length ) ;
 break ;
 default : break ;
 }
 }
 return proto_tree_add_item ( tree , hfindex , tvb , start , length , encoding ) ;
 }