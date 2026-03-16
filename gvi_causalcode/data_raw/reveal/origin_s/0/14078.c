static void dissect_glabel_lambda ( proto_tree * ti _U_ , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset ) {
 float freq = 0.0f ;
 guint32 wavelength = 0 ;
 float cs_thz = 0.0f ;
 proto_tree * wavelength_tree ;
 guint8 grid , cs ;
 gint16 n ;
 static const value_string grid1_cs_vals [ ] = {
 {
 1 , "100GHz" }
 , {
 2 , "50GHz" }
 , {
 3 , "25GHz" }
 , {
 4 , "12.5GHz" }
 , {
 0 , NULL }
 }
 ;
 static const value_string grid2_cs_vals [ ] = {
 {
 1 , "20nm" }
 , {
 0 , NULL }
 }
 ;
 wavelength_tree = proto_tree_add_subtree ( rsvp_object_tree , tvb , offset , 4 , TREE ( TT_WAVELENGTH ) , NULL , "Wavelength Label" ) ;
 proto_tree_add_item ( wavelength_tree , hf_rsvp_wavelength_grid , tvb , offset , 1 , ENC_NA ) ;
 grid = ( ( tvb_get_guint8 ( tvb , offset ) & 0xE0 ) >> 5 ) ;
 cs = ( ( tvb_get_guint8 ( tvb , offset ) & 0x1E ) >> 1 ) ;
 n = tvb_get_ntohs ( tvb , offset + 2 ) ;
 switch ( grid ) {
 case 1 : cs_thz = cs == 1 ? 0.1f : cs == 2 ? 0.05f : cs == 3 ? 0.025f : cs == 4 ? 0.0125f : 0.0f ;
 freq = 193.1f + ( n * cs_thz ) ;
 proto_tree_add_uint_format_value ( wavelength_tree , hf_rsvp_wavelength_channel_spacing , tvb , offset , 1 , tvb_get_guint8 ( tvb , offset ) , "%s" , val_to_str_const ( cs , grid1_cs_vals , "Unknown" ) ) ;
 proto_tree_add_item ( wavelength_tree , hf_rsvp_wavelength_n , tvb , offset + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_float_format_value ( wavelength_tree , hf_rsvp_wavelength_freq , tvb , offset , 4 , freq , "%.2fTHz" , freq ) ;
 proto_item_append_text ( ti , ": Wavelength: grid=DWDM, channel spacing=%s, n=%d, freq=%.2fTHz" , val_to_str_const ( cs , grid1_cs_vals , "Unknown" ) , n , freq ) ;
 break ;
 case 2 : wavelength = 1471 + ( n * 20 ) ;
 proto_tree_add_uint_format_value ( wavelength_tree , hf_rsvp_wavelength_channel_spacing , tvb , offset , 1 , tvb_get_guint8 ( tvb , offset ) , "%s" , val_to_str_const ( cs , grid2_cs_vals , "Unknown" ) ) ;
 proto_tree_add_item ( wavelength_tree , hf_rsvp_wavelength_n , tvb , offset + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint_format_value ( wavelength_tree , hf_rsvp_wavelength_wavelength , tvb , offset , 4 , wavelength , "%unm" , wavelength ) ;
 proto_item_append_text ( ti , ": Wavelength: grid=CWDM, channel spacing=%s, n=%d, wavelength=%unm" , val_to_str_const ( cs , grid2_cs_vals , "Unknown" ) , n , wavelength ) ;
 break ;
 default : proto_tree_add_item ( wavelength_tree , hf_rsvp_wavelength_channel_spacing , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( wavelength_tree , hf_rsvp_wavelength_n , tvb , offset + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , ": Wavelength: grid=%u, channel spacing=%u, n=%d" , grid , cs , n ) ;
 break ;
 }
 }