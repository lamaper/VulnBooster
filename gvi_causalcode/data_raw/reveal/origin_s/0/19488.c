static const char * name ## _get_name ( void * ctx ) \ {
 return # name ;
 \ }
 static const AVClass name ## _class = {
 . class_name = # name , . item_name = name ## _get_name , . option = name ## _options \ }
 typedef struct DefaultContext {
 const AVClass * class ;
 int nokey ;
 int noprint_wrappers ;
 int nested_section [ SECTION_MAX_NB_LEVELS ] ;
 }
 DefaultContext ;

 {
 "noprint_wrappers" , "do not print headers and footers" , OFFSET ( noprint_wrappers ) , AV_OPT_TYPE_BOOL , {
 . i64 = 0 }
 , 0 , 1 }
 , {
 "nw" , "do not print headers and footers" , OFFSET ( noprint_wrappers ) , AV_OPT_TYPE_BOOL , {
 . i64 = 0 }
 , 0 , 1 }
 , {
 "nokey" , "force no key printing" , OFFSET ( nokey ) , AV_OPT_TYPE_BOOL , {
 . i64 = 0 }
 , 0 , 1 }
 , {
 "nk" , "force no key printing" , OFFSET ( nokey ) , AV_OPT_TYPE_BOOL , {
 . i64 = 0 }
 , 0 , 1 }
 , {
 NULL }
 , }
 ;
 DEFINE_WRITER_CLASS ( default )