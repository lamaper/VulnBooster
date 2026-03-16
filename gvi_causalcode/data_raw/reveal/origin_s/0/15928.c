static int opt_show_ ## section ( const char * opt , const char * arg ) {
 mark_section_show_entries ( SECTION_ID_ ## target_section_id , 1 , NULL ) ;
 return 0 ;
 }
 DEFINE_OPT_SHOW_SECTION ( chapters , CHAPTERS ) DEFINE_OPT_SHOW_SECTION ( error , ERROR ) DEFINE_OPT_SHOW_SECTION ( format , FORMAT ) DEFINE_OPT_SHOW_SECTION ( frames , FRAMES ) DEFINE_OPT_SHOW_SECTION ( library_versions , LIBRARY_VERSIONS ) DEFINE_OPT_SHOW_SECTION ( packets , PACKETS )