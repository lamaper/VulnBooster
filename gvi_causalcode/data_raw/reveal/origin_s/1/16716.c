void init_util ( void ) {
 filegen_register ( statsdir , "peerstats" , & peerstats ) ;
 filegen_register ( statsdir , "loopstats" , & loopstats ) ;
 filegen_register ( statsdir , "clockstats" , & clockstats ) ;
 filegen_register ( statsdir , "rawstats" , & rawstats ) ;
 filegen_register ( statsdir , "sysstats" , & sysstats ) ;
 filegen_register ( statsdir , "protostats" , & protostats ) ;




