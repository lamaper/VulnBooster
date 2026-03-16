static void h225_stat_init ( stat_tap_table_ui * new_stat , new_stat_tap_gui_init_cb gui_callback , void * gui_data ) {
 int num_fields = sizeof ( h225_stat_fields ) / sizeof ( stat_tap_table_item ) ;
 stat_tap_table * table = new_stat_tap_init_table ( "H.225 Messages and Message Reasons" , num_fields , 0 , NULL , gui_callback , gui_data ) ;
 int row_idx = 0 , msg_idx ;
 stat_tap_table_item_type items [ sizeof ( h225_stat_fields ) / sizeof ( stat_tap_table_item ) ] ;
 new_stat_tap_add_table ( new_stat , table ) ;
 items [ MESSAGE_TYPE_COLUMN ] . type = TABLE_ITEM_STRING ;
 items [ COUNT_COLUMN ] . type = TABLE_ITEM_UINT ;
 items [ COUNT_COLUMN ] . value . uint_value = 0 ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = h225_RasMessage_vals [ msg_idx ] . strptr ? h225_RasMessage_vals [ msg_idx ] . strptr : "Unknown RAS message" ;
 ras_msg_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( h225_RasMessage_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = T_h323_message_body_vals [ msg_idx ] . strptr ? T_h323_message_body_vals [ msg_idx ] . strptr : "Unknown CS message" ;
 cs_msg_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( T_h323_message_body_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = GatekeeperRejectReason_vals [ msg_idx ] . strptr ? GatekeeperRejectReason_vals [ msg_idx ] . strptr : "Unknown gatekeeper reject reason" ;
 grj_reason_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( GatekeeperRejectReason_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = RegistrationRejectReason_vals [ msg_idx ] . strptr ? RegistrationRejectReason_vals [ msg_idx ] . strptr : "Unknown registration reject reason" ;
 rrj_reason_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( RegistrationRejectReason_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = UnregRequestReason_vals [ msg_idx ] . strptr ? UnregRequestReason_vals [ msg_idx ] . strptr : "Unknown unregistration request reason" ;
 urq_reason_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( UnregRequestReason_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = UnregRejectReason_vals [ msg_idx ] . strptr ? UnregRejectReason_vals [ msg_idx ] . strptr : "Unknown unregistration reject reason" ;
 urj_reason_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( UnregRejectReason_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = AdmissionRejectReason_vals [ msg_idx ] . strptr ? AdmissionRejectReason_vals [ msg_idx ] . strptr : "Unknown admission reject reason" ;
 arj_reason_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( AdmissionRejectReason_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = BandRejectReason_vals [ msg_idx ] . strptr ? BandRejectReason_vals [ msg_idx ] . strptr : "Unknown band reject reason" ;
 brj_reason_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( BandRejectReason_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = DisengageReason_vals [ msg_idx ] . strptr ? DisengageReason_vals [ msg_idx ] . strptr : "Unknown disengage reason" ;
 drq_reason_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( DisengageReason_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = DisengageRejectReason_vals [ msg_idx ] . strptr ? DisengageRejectReason_vals [ msg_idx ] . strptr : "Unknown disengage reject reason" ;
 drj_reason_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( DisengageRejectReason_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = LocationRejectReason_vals [ msg_idx ] . strptr ? LocationRejectReason_vals [ msg_idx ] . strptr : "Unknown location reject reason" ;
 lrj_reason_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( LocationRejectReason_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = InfoRequestNakReason_vals [ msg_idx ] . strptr ? InfoRequestNakReason_vals [ msg_idx ] . strptr : "Unknown info request nak reason" ;
 irqnak_reason_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( InfoRequestNakReason_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = h225_ReleaseCompleteReason_vals [ msg_idx ] . strptr ? h225_ReleaseCompleteReason_vals [ msg_idx ] . strptr : "Unknown release complete reason" ;
 rel_cmp_reason_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( h225_ReleaseCompleteReason_vals [ msg_idx ] . strptr ) ;
 msg_idx = 0 ;
 do {
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = FacilityReason_vals [ msg_idx ] . strptr ? FacilityReason_vals [ msg_idx ] . strptr : "Unknown facility reason" ;
 facility_reason_idx [ msg_idx ] = row_idx ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 row_idx ++ ;
 msg_idx ++ ;
 }
 while ( FacilityReason_vals [ msg_idx ] . strptr ) ;
 items [ MESSAGE_TYPE_COLUMN ] . value . string_value = "Unknown H.225 message" ;
 new_stat_tap_init_table_row ( table , row_idx , num_fields , items ) ;
 other_idx = row_idx ;
 }