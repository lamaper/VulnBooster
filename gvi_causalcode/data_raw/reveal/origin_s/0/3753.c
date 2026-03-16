void dissect_geographical_description ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree ) {
 proto_item * lat_item , * long_item , * major_item , * minor_item , * alt_item , * uncer_item ;
 guint8 type_of_shape ;
 int offset = 0 ;
 int length ;
 guint8 value ;
 guint32 uvalue32 ;
 gint32 svalue32 ;
 length = tvb_reported_length_remaining ( tvb , 0 ) ;
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_type_of_shape , tvb , 0 , 1 , ENC_BIG_ENDIAN ) ;
 if ( length < 2 ) return ;
 type_of_shape = tvb_get_guint8 ( tvb , offset ) >> 4 ;
 switch ( type_of_shape ) {
 case ELLIPSOID_POINT : case ELLIPSOID_POINT_WITH_UNCERT_CIRC : case ELLIPSOID_POINT_WITH_UNCERT_ELLIPSE : case ELLIPSOID_POINT_WITH_ALT : case ELLIPSOID_POINT_WITH_ALT_AND_UNCERT_ELLIPSOID : case ELLIPSOID_ARC : offset ++ ;
 if ( length < 4 ) return ;
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_sign_of_lat , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 uvalue32 = tvb_get_ntoh24 ( tvb , offset ) ;
 lat_item = proto_tree_add_item ( tree , hf_gsm_a_geo_loc_deg_of_lat , tvb , offset , 3 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( lat_item , " (%s%.5f degrees)" , ( uvalue32 & 0x00800000 ) ? "-" : "" , ( ( double ) ( uvalue32 & 0x7fffff ) / 8388607.0 ) * 90 ) ;
 if ( length < 7 ) return ;
 offset = offset + 3 ;
 svalue32 = tvb_get_ntoh24 ( tvb , offset ) ;
 svalue32 |= ( svalue32 & 0x800000 ) ? 0xff000000 : 0x00000000 ;
 long_item = proto_tree_add_item ( tree , hf_gsm_a_geo_loc_deg_of_long , tvb , offset , 3 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( long_item , " (%.5f degrees)" , ( ( double ) svalue32 / 16777215.0 ) * 360 ) ;
 offset = offset + 3 ;
 if ( type_of_shape == ELLIPSOID_POINT_WITH_UNCERT_CIRC ) {
 if ( length < 8 ) return ;
 value = tvb_get_guint8 ( tvb , offset ) & 0x7f ;
 uncer_item = proto_tree_add_item ( tree , hf_gsm_a_geo_loc_uncertainty_code , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( uncer_item , " (%.1f m)" , 10 * ( pow ( 1.1 , ( double ) value ) - 1 ) ) ;
 }
 else if ( type_of_shape == ELLIPSOID_POINT_WITH_UNCERT_ELLIPSE ) {
 value = tvb_get_guint8 ( tvb , offset ) & 0x7f ;
 major_item = proto_tree_add_item ( tree , hf_gsm_a_geo_loc_uncertainty_semi_major , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( major_item , " (%.1f m)" , 10 * ( pow ( 1.1 , ( double ) value ) - 1 ) ) ;
 offset ++ ;
 value = tvb_get_guint8 ( tvb , offset ) & 0x7f ;
 minor_item = proto_tree_add_item ( tree , hf_gsm_a_geo_loc_uncertainty_semi_minor , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( minor_item , " (%.1f m)" , 10 * ( pow ( 1.1 , ( double ) value ) - 1 ) ) ;
 offset ++ ;
 value = tvb_get_guint8 ( tvb , offset ) & 0x7f ;
 proto_tree_add_uint ( tree , hf_gsm_a_geo_loc_orientation_of_major_axis , tvb , offset , 1 , value * 2 ) ;
 offset ++ ;
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_confidence , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 }
 else if ( type_of_shape == ELLIPSOID_POINT_WITH_ALT ) {
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_D , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_altitude , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 }
 else if ( type_of_shape == ELLIPSOID_POINT_WITH_ALT_AND_UNCERT_ELLIPSOID ) {
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_D , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_altitude , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset = offset + 2 ;
 value = tvb_get_guint8 ( tvb , offset ) & 0x7f ;
 major_item = proto_tree_add_item ( tree , hf_gsm_a_geo_loc_uncertainty_semi_major , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( major_item , " (%.1f m)" , 10 * ( pow ( 1.1 , ( double ) value ) - 1 ) ) ;
 offset ++ ;
 value = tvb_get_guint8 ( tvb , offset ) & 0x7f ;
 minor_item = proto_tree_add_item ( tree , hf_gsm_a_geo_loc_uncertainty_semi_minor , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( minor_item , " (%.1f m)" , 10 * ( pow ( 1.1 , ( double ) value ) - 1 ) ) ;
 offset ++ ;
 value = tvb_get_guint8 ( tvb , offset ) & 0x7f ;
 proto_tree_add_uint ( tree , hf_gsm_a_geo_loc_orientation_of_major_axis , tvb , offset , 1 , value * 2 ) ;
 offset ++ ;
 value = tvb_get_guint8 ( tvb , offset ) & 0x7f ;
 alt_item = proto_tree_add_item ( tree , hf_gsm_a_geo_loc_uncertainty_altitude , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( alt_item , " (%.1f m)" , 45 * ( pow ( 1.025 , ( double ) value ) - 1 ) ) ;
 offset ++ ;
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_confidence , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 }
 else if ( type_of_shape == ELLIPSOID_ARC ) {
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_inner_radius , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset = offset + 2 ;
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_uncertainty_radius , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_offset_angle , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_included_angle , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( tree , hf_gsm_a_geo_loc_confidence , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 }
 break ;
 case POLYGON : proto_tree_add_item ( tree , hf_gsm_a_geo_loc_no_of_points , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;

 while ( no_of_points > 0 ) {
 offset ++ ;
 no_of_points -- ;
 }

 default : break ;
 }
 }