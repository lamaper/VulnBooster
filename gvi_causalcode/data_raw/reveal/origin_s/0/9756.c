static guint32 dissect_trunkpacket ( tvbuff_t * tvb , guint32 offset , guint16 scallno_param _U_ , packet_info * pinfo , proto_tree * iax2_tree , proto_tree * main_tree _U_ ) {
 guint8 cmddata , trunkts ;
 guint nframes = 0 , ncalls = 0 ;
 proto_item * cd , * nc = NULL ;
 proto_tree * field_tree = NULL ;
 call_list * calls = NULL ;
 cmddata = tvb_get_guint8 ( tvb , offset + 1 ) ;
 trunkts = cmddata & IAX2_TRUNK_TS ;
 if ( iax2_tree ) {
 proto_tree_add_item ( iax2_tree , hf_iax2_trunk_metacmd , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 cd = proto_tree_add_uint ( iax2_tree , hf_iax2_trunk_cmddata , tvb , offset + 1 , 1 , cmddata ) ;
 field_tree = proto_item_add_subtree ( cd , ett_iax2_trunk_cmddata ) ;
 if ( trunkts ) proto_item_append_text ( cd , " (trunk timestamps)" ) ;
 proto_tree_add_boolean ( field_tree , hf_iax2_trunk_cmddata_ts , tvb , offset + 1 , 1 , cmddata ) ;
 proto_tree_add_item ( iax2_tree , hf_iax2_trunk_ts , tvb , offset + 2 , 4 , ENC_BIG_ENDIAN ) ;
 }
 offset += 6 ;
 if ( trunkts ) {
 while ( tvb_captured_length_remaining ( tvb , offset ) >= 6 ) {
 guint16 scallno ;
 offset = dissect_trunkcall_ts ( tvb , offset , iax2_tree , & scallno ) ;
 if ( ! call_list_find ( calls , scallno ) ) {
 calls = call_list_append ( calls , scallno ) ;
 }
 nframes ++ ;
 }
 }
 else {
 while ( tvb_captured_length_remaining ( tvb , offset ) >= 4 ) {
 guint16 scallno ;
 offset = dissect_trunkcall_nots ( tvb , offset , iax2_tree , & scallno ) ;
 if ( ! call_list_find ( calls , scallno ) ) {
 calls = call_list_append ( calls , scallno ) ;
 }
 nframes ++ ;
 }
 }
 ncalls = call_list_length ( calls ) ;
 if ( iax2_tree ) {
 nc = proto_tree_add_uint ( iax2_tree , hf_iax2_trunk_ncalls , NULL , 0 , 0 , ncalls ) ;
 PROTO_ITEM_SET_GENERATED ( nc ) ;
 }
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "Trunk packet with %d media frame%s for %d call%s" , nframes , plurality ( nframes , "" , "s" ) , ncalls , plurality ( ncalls , "" , "s" ) ) ;
 return offset ;
 }