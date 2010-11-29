
#ifndef __UNIT_CONVERSIONS_H__
#define __UNIT_CONVERSIONS_H__

struct UnitConversions
{  
  static double MMToInch(const double& mm)
  {
    return (mm/25.2);
  }   
};

#endif // __UNIT_CONVERSIONS_H__
