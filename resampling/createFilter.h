//
// File: createFilter.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 29-Mar-2023 00:10:34
//

#ifndef CREATEFILTER_H
#define CREATEFILTER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace signal {
namespace internal {
namespace resample {
void createFilter(double Lx, double p, double q, ::coder::array<double, 2U> &h,
                  ::coder::array<double, 2U> &ht, double *delay);

}
} // namespace internal
} // namespace signal
} // namespace coder

#endif
//
// File trailer for createFilter.h
//
// [EOF]
//
