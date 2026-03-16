WRITE_CLASS_ENCODER ( EntityAuth ) static inline ostream & operator << ( ostream & out , const EntityAuth & a ) {
 return out << "auth(auid = " << a . auid << " key=" << a . key << " with " << a . caps . size ( ) << " caps)" ;
 }