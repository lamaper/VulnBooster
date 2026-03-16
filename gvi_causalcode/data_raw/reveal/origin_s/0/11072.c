void proto_register_zbee_zcl_pwr_prof ( void ) {
 guint i , j ;
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_pwr_prof_tot_prof_num , {
 "Total Profile Number" , "zbee_zcl_general.pwrprof.attr.totprofnum" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_multiple_sched , {
 "Multiple Scheduling" , "zbee_zcl_general.pwrprof.attr.multiplesched" , FT_BOOLEAN , BASE_NONE , TFS ( & tfs_supported_not_supported ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_energy_format , {
 "Data" , "zbee_zcl_general.pwrprof.attr.energyformat" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_energy_format_rdigit , {
 "Number of Digits to the right of the Decimal Point" , "zbee_zcl_general.pwrprof.attr.energyformat.rdigit" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_OPT_PWRPROF_NUM_R_DIGIT , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_energy_format_ldigit , {
 "Number of Digits to the left of the Decimal Point" , "zbee_zcl_general.pwrprof.attr.energyformat.ldigit" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_OPT_PWRPROF_NUM_L_DIGIT , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_energy_format_noleadingzero , {
 "Suppress leading zeros." , "zbee_zcl_general.pwrprof.attr.energyformat.noleadingzero" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , ZBEE_ZCL_OPT_PWRPROF_NO_LEADING_ZERO , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_energy_remote , {
 "Energy Remote" , "zbee_zcl_general.pwrprof.attr.energyremote" , FT_BOOLEAN , BASE_NONE , TFS ( & tfs_enabled_disabled ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_sched_mode , {
 "Schedule Mode" , "zbee_zcl_general.pwrprof.attr.schedmode" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_sched_mode_cheapest , {
 "Schedule Mode Cheapest" , "zbee_zcl_general.pwrprof.attr.schedmode.cheapest" , FT_BOOLEAN , 8 , TFS ( & tfs_active_inactive ) , ZBEE_ZCL_OPT_PWRPROF_SCHED_CHEAPEST , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_sched_mode_greenest , {
 "Schedule Mode Greenest" , "zbee_zcl_general.pwrprof.attr.schedmode.greenest" , FT_BOOLEAN , 8 , TFS ( & tfs_active_inactive ) , ZBEE_ZCL_OPT_PWRPROF_SCHED_GREENEST , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_sched_mode_reserved , {
 "Schedule Mode Reserved" , "zbee_zcl_general.pwrprof.attr.schedmode.reserved" , FT_UINT8 , BASE_HEX , NULL , ZBEE_ZCL_OPT_PWRPROF_SCHED_RESERVED , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_attr_id , {
 "Attribute" , "zbee_zcl_general.pwrprof.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_pwr_prof_attr_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_srv_tx_cmd_id , {
 "Command" , "zbee_zcl_general.pwrprof.cmd.srv_tx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_pwr_prof_srv_tx_cmd_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_srv_rx_cmd_id , {
 "Command" , "zbee_zcl_general.pwrprof.cmd.srv_rx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_pwr_prof_srv_rx_cmd_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_pwr_prof_id , {
 "Power Profile ID" , "zbee_zcl_general.pwrprof.pwrprofid" , FT_UINT8 , BASE_CUSTOM , CF_FUNC ( decode_power_profile_id ) , 0x00 , "Identifier of the specific profile" , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_currency , {
 "Currency" , "zbee_zcl_general.pwrprof.currency" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_currecy_names ) , 0x0 , "Local unit of currency (ISO 4217) used in the price field." , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_price , {
 "Price" , "zbee_zcl_general.pwrprof.price" , FT_UINT32 , BASE_CUSTOM , CF_FUNC ( decode_price_in_cents ) , 0x0 , "Price of the energy of a specific Power Profile." , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_price_trailing_digit , {
 "Price Trailing Digit" , "zbee_zcl_general.pwrprof.pricetrailingdigit" , FT_UINT8 , BASE_DEC , NULL , 0x0 , "Number of digits to the right of the decimal point." , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_num_of_sched_phases , {
 "Number of Scheduled Phases" , "zbee_zcl_general.pwrprof.numofschedphases" , FT_UINT8 , BASE_DEC , NULL , 0x0 , "Total number of the energy phases of the Power Profile that need to be scheduled." , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_energy_phase_id , {
 "Energy Phase ID" , "zbee_zcl_general.pwrprof.energyphaseid" , FT_UINT8 , BASE_DEC , NULL , 0x0 , "Identifier of the specific phase." , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_scheduled_time , {
 "Scheduled Time" , "zbee_zcl_general.pwrprof.scheduledtime" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_minutes ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_macro_phase_id , {
 "Macro Phase ID" , "zbee_zcl_general.pwrprof.macrophaseid" , FT_UINT8 , BASE_DEC , NULL , 0x0 , "Identifier of the specific energy phase." , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_expect_duration , {
 "Expected Duration" , "zbee_zcl_general.pwrprof.expecduration" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_minutes ) , 0x0 , "The estimated duration of the specific phase." , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_num_of_trans_phases , {
 "Number of Transferred Phases" , "zbee_zcl_general.pwrprof.numoftransphases" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_peak_power , {
 "Peak Power" , "zbee_zcl_general.pwrprof.peakpower" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_power_in_watt ) , 0x0 , "The estimated power for the specific phase." , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_energy , {
 "Energy" , "zbee_zcl_general.pwrprof.energy" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_energy ) , 0x0 , "The estimated energy consumption for the accounted phase." , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_max_active_delay , {
 "Max Activation Delay" , "zbee_zcl_general.pwrprof.maxactivdelay" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( func_decode_delayinminute ) , 0x0 , "The maximum interruption time between the end of the previous phase and the beginning of the specific phase." , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_pwr_prof_count , {
 "Power Profile Count" , "zbee_zcl_general.pwrprof.pwrprofcount" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_pwr_prof_rem_ctrl , {
 "Power Profile Remote Control" , "zbee_zcl_general.pwrprof.pwrprofremctrl" , FT_BOOLEAN , BASE_NONE , TFS ( & tfs_enabled_disabled ) , 0x00 , "It indicates if the PowerProfile is currently remotely controllable or not." , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_pwr_prof_state , {
 "Power Profile State" , "zbee_zcl_general.pwrprof.pwrprofstate" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_pwr_prof_state_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_start_after , {
 "Start After" , "zbee_zcl_general.pwrprof.startafter" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_minutes ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_stop_before , {
 "Stop Before" , "zbee_zcl_general.pwrprof.stopbefore" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_minutes ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_options , {
 "Options" , "zbee_zcl_general.pwrprof.options" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_options_01 , {
 "PowerProfileStartTime Field Present" , "zbee_zcl_general.pwrprof.options.01" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , ZBEE_ZCL_OPT_PWRPROF_STIME_PRESENT , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_options_res , {
 "Reserved" , "zbee_zcl_general.pwrprof.options.reserved" , FT_UINT8 , BASE_HEX , NULL , ZBEE_ZCL_OPT_PWRPROF_RESERVED , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_pwr_prof_pwr_prof_stime , {
 "Power Profile Start Time" , "zbee_zcl_general.pwrprof.pwrprofstime" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_minutes ) , 0x0 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ZBEE_ZCL_PWR_PROF_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_pwr_prof ;
 ett [ 1 ] = & ett_zbee_zcl_pwr_prof_options ;
 ett [ 2 ] = & ett_zbee_zcl_pwr_prof_en_format ;
 ett [ 3 ] = & ett_zbee_zcl_pwr_prof_sched_mode ;
 for ( i = 0 , j = ZBEE_ZCL_PWR_PROF_NUM_GENERIC_ETT ;
 i < ZBEE_ZCL_PWR_PROF_NUM_PWR_PROF_ETT ;
 i ++ , j ++ ) {
 ett_zbee_zcl_pwr_prof_pwrprofiles [ i ] = - 1 ;
 ett [ j ] = & ett_zbee_zcl_pwr_prof_pwrprofiles [ i ] ;
 }
 for ( i = 0 ;
 i < ZBEE_ZCL_PWR_PROF_NUM_EN_PHS_ETT ;
 i ++ , j ++ ) {
 ett_zbee_zcl_pwr_prof_enphases [ i ] = - 1 ;
 ett [ j ] = & ett_zbee_zcl_pwr_prof_enphases [ i ] ;
 }
 proto_zbee_zcl_pwr_prof = proto_register_protocol ( "ZigBee ZCL Power Profile" , "ZCL Power Profile" , ZBEE_PROTOABBREV_ZCL_PWRPROF ) ;
 proto_register_field_array ( proto_zbee_zcl_pwr_prof , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_PWRPROF , dissect_zbee_zcl_pwr_prof , proto_zbee_zcl_pwr_prof ) ;
 }