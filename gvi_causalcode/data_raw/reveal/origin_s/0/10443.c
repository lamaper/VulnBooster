static gint coap_get_opt_uint ( tvbuff_t * tvb , gint offset , gint length ) {
 switch ( length ) {
 case 0 : return 0 ;
 case 1 : return ( guint ) tvb_get_guint8 ( tvb , offset ) ;
 case 2 : return ( guint ) tvb_get_ntohs ( tvb , offset ) ;
 case 3 : return ( guint ) tvb_get_ntoh24 ( tvb , offset ) ;
 case 4 : return ( guint ) tvb_get_ntohl ( tvb , offset ) ;
 default : return - 1 ;
 }
 }