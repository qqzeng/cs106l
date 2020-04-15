//
// Created by GEORGE-pc on 2020/3/9.
//

//#ifndef CHAPTER_02_UNITS_H
//#define CHAPTER_02_UNITS_H
//
//#endif //CHAPTER_02_UNITS_H





// Solution of Exercise-12.
#ifndef  DEFINE_UNIT
#error "Must define macro DEFINE_UNIT before including this header file."
#else
DEFINE_UNIT(Meter, 1.0, m, Metric)
DEFINE_UNIT(Centimeter, 0.01, cm, Metric)
DEFINE_UNIT(Kilometer, 1000.0, km, Metric)
DEFINE_UNIT(Foot, 0.3048, ft, English)
DEFINE_UNIT(Inch, 0.0254, in, English)
DEFINE_UNIT(Mile, 1609.344, mi, English)
DEFINE_UNIT(Astronomical Unit, 1.496e+11, AU, Astronomical)
DEFINE_UNIT(Light Year, 9.461e+15, ly, Astronomical)
DEFINE_UNIT(Cubit, 0.55, cubit, Archaic)
#endif