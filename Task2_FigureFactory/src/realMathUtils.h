#define _USE_MATH_DEFINES

#include <cmath>

//Mathematical utilities for real numbers
namespace Mur
{
#define DEFAULT_TOLERANCE 1.0E-12

  inline bool isEqual(double left, double right, double tol = DEFAULT_TOLERANCE)
  {
    return fabs(left - right) < tol;
  }

  inline bool isZero(double val, double tol = DEFAULT_TOLERANCE)
  {
    return isEqual(val, 0.0, tol);
  }

  inline bool isNegative(double val, double tol = DEFAULT_TOLERANCE)
  {
    return val < -tol;
  }
}