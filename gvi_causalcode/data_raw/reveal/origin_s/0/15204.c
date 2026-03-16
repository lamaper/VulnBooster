void init_util ( void ) {
 filegen_register ( statsdir , "peerstats" , & peerstats ) ;
 filegen_register ( statsdir , "loopstats" , & loopstats ) ;
 filegen_register ( statsdir , "clockstats" , & clockstats ) ;
 filegen_register ( statsdir , "rawstats" , & rawstats ) ;
 filegen_register ( statsdir , "sysstats" , & sysstats ) ;
 filegen_register ( statsdir , "protostats" , & protostats ) ;
 filegen_register ( statsdir , "cryptostats" , & cryptostats ) ;
 filegen_register ( statsdir , "timingstats" , & timingstats ) ;
 step_callback = & ntpd_time_stepped ;

