unsigned int TSConfigSet ( unsigned int id , void * data , TSConfigDestroyFunc funcp ) {
 INKConfigImpl * config = new INKConfigImpl ;
 config -> mdata = data ;
 config -> m_destroy_func = funcp ;
 return configProcessor . set ( id , config ) ;
 }