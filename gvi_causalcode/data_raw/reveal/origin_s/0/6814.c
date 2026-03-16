static double exsltMathConstant ( xmlChar * name , double precision ) {
 xmlChar * str ;
 double ret ;
 if ( ( name == NULL ) || ( xmlXPathIsNaN ( precision ) ) || ( precision < 1.0 ) ) {
 return xmlXPathNAN ;
 }
 if ( xmlStrEqual ( name , BAD_CAST "PI" ) ) {
 int len = xmlStrlen ( EXSLT_PI ) ;
 if ( precision <= len ) len = ( int ) precision ;
 str = xmlStrsub ( EXSLT_PI , 0 , len ) ;
 }
 else if ( xmlStrEqual ( name , BAD_CAST "E" ) ) {
 int len = xmlStrlen ( EXSLT_E ) ;
 if ( precision <= len ) len = ( int ) precision ;
 str = xmlStrsub ( EXSLT_E , 0 , len ) ;
 }
 else if ( xmlStrEqual ( name , BAD_CAST "SQRRT2" ) ) {
 int len = xmlStrlen ( EXSLT_SQRRT2 ) ;
 if ( precision <= len ) len = ( int ) precision ;
 str = xmlStrsub ( EXSLT_SQRRT2 , 0 , len ) ;
 }
 else if ( xmlStrEqual ( name , BAD_CAST "LN2" ) ) {
 int len = xmlStrlen ( EXSLT_LN2 ) ;
 if ( precision <= len ) len = ( int ) precision ;
 str = xmlStrsub ( EXSLT_LN2 , 0 , len ) ;
 }
 else if ( xmlStrEqual ( name , BAD_CAST "LN10" ) ) {
 int len = xmlStrlen ( EXSLT_LN10 ) ;
 if ( precision <= len ) len = ( int ) precision ;
 str = xmlStrsub ( EXSLT_LN10 , 0 , len ) ;
 }
 else if ( xmlStrEqual ( name , BAD_CAST "LOG2E" ) ) {
 int len = xmlStrlen ( EXSLT_LOG2E ) ;
 if ( precision <= len ) len = ( int ) precision ;
 str = xmlStrsub ( EXSLT_LOG2E , 0 , len ) ;
 }
 else if ( xmlStrEqual ( name , BAD_CAST "SQRT1_2" ) ) {
 int len = xmlStrlen ( EXSLT_SQRT1_2 ) ;
 if ( precision <= len ) len = ( int ) precision ;
 str = xmlStrsub ( EXSLT_SQRT1_2 , 0 , len ) ;
 }
 else {
 str = NULL ;
 }
 if ( str == NULL ) return xmlXPathNAN ;
 ret = xmlXPathCastStringToNumber ( str ) ;
 xmlFree ( str ) ;
 return ret ;
 }