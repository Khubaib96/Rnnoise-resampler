//
// File: ipermute.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 29-Mar-2023 00:10:34
//

// Include Files
#include "ipermute.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &b
//                ::coder::array<double, 1U> &a
// Return Type  : void
//
namespace coder {
void ipermute(const ::coder::array<double, 1U> &b,
              ::coder::array<double, 1U> &a)
{
  int i;
  int k;
  int plast;
  boolean_T b_b;
  b_b = true;
  if (b.size(0) != 0) {
    boolean_T exitg1;
    plast = 0;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 2)) {
      if (k + 1 <= 1) {
        i = b.size(0);
      } else {
        i = 1;
      }
      if (i != 1) {
        if (plast > k + 1) {
          b_b = false;
          exitg1 = true;
        } else {
          plast = k + 1;
          k++;
        }
      } else {
        k++;
      }
    }
  }
  if (b_b) {
    a.set_size(b.size(0));
    plast = b.size(0);
    for (i = 0; i < plast; i++) {
      a[i] = b[i];
    }
  } else {
    a.set_size(b.size(0));
    i = b.size(0);
    for (k = 0; k < i; k++) {
      a[k] = b[k];
    }
  }
}

} // namespace coder

//
// File trailer for ipermute.cpp
//
// [EOF]
//
