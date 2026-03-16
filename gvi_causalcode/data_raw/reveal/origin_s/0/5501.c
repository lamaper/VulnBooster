static inline Quantum ClampPixel ( const MagickRealType value ) {


 if ( value >= ( MagickRealType ) QuantumRange ) return ( ( Quantum ) QuantumRange ) ;
 return ( ( Quantum ) value ) ;
