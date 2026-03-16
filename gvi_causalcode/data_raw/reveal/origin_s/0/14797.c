int __glob_pattern_p ( pattern , quote ) const char * pattern ;
 int quote ;
 {
 return __glob_pattern_type ( pattern , quote ) == 1 ;
 }