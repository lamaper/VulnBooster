static bool ModuleSort ( const ModuleEnumerator : : Module & a , const ModuleEnumerator : : Module & b ) {
 if ( a . status != b . status ) return a . status > b . status ;
 if ( a . location == b . location ) return a . name < b . name ;
 return a . location < b . location ;
 }