inline bool is_delimiter_command ( char * name , ulong len ) {
 return ( len >= DELIMITER_NAME_LEN && ! my_strnncoll ( charset_info , ( uchar * ) name , DELIMITER_NAME_LEN , ( uchar * ) DELIMITER_NAME , DELIMITER_NAME_LEN ) ) ;
 }