WRITE_CLASS_ENCODER ( ExpiringCryptoKey ) static inline ostream & operator << ( ostream & out , const ExpiringCryptoKey & c ) {
 return out << c . key << " expires " << c . expiration ;
 }