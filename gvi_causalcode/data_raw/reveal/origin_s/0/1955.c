static const char * file_type_to_string ( enum VideoFileType t ) {
 switch ( t ) {
 case FILE_TYPE_RAW : return "RAW" ;
 case FILE_TYPE_Y4M : return "Y4M" ;
 default : return "Other" ;
 }
 }