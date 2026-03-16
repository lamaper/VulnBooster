static void register_rsvp_prefs ( void ) {
 module_t * rsvp_module ;
 rsvp_module = prefs_register_protocol ( proto_rsvp , NULL ) ;
 prefs_register_bool_preference ( rsvp_module , "process_bundle" , "Dissect sub-messages in BUNDLE message" , "Specifies whether Wireshark should decode and display sub-messages within BUNDLE messages" , & rsvp_bundle_dissect ) ;
 prefs_register_enum_preference ( rsvp_module , "generalized_label_options" , "Dissect generalized labels as" , "Specifies how Wireshark should dissect generalized labels" , ( gint * ) & rsvp_generalized_label_option , rsvp_generalized_label_options , FALSE ) ;
 }