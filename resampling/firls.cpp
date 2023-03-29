//
// File: firls.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 29-Mar-2023 00:10:34
//

// Include Files
#include "firls.h"
#include "mldivide.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cfloat>
#include <cmath>

// Function Declarations
static void b_binary_expand_op(coder::array<double, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const coder::array<double, 2U> &in3,
                               const unsigned int in4[2]);

static void binary_expand_op(coder::array<double, 2U> &in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<double, 2U> &in3,
                             const unsigned int in4[2]);

static void binary_expand_op(coder::array<double, 1U> &in1, double in2,
                             const coder::array<double, 1U> &in3,
                             const coder::array<double, 1U> &in4,
                             const coder::array<double, 1U> &in5);

static void binary_expand_op(coder::array<double, 1U> &in1, double in2,
                             const coder::array<double, 1U> &in3, double in4,
                             const coder::array<double, 1U> &in5);

static void binary_expand_op(coder::array<double, 2U> &in1, double in2,
                             const coder::array<double, 2U> &in3,
                             const coder::array<double, 2U> &in4, double in5,
                             const coder::array<double, 2U> &in6,
                             const coder::array<double, 2U> &in7);

static int div_s32(int numerator, int denominator);

static double rt_remd_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
//                const unsigned int in4[2]
// Return Type  : void
//
static void b_binary_expand_op(coder::array<double, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const coder::array<double, 2U> &in3,
                               const unsigned int in4[2])
{
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int in4_idx_0;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_1;
  in4_idx_0 = static_cast<int>(in4[0]);
  if (in4_idx_0 == 1) {
    i = in2.size(0);
  } else {
    i = in4_idx_0;
  }
  if (in3.size(1) == 1) {
    i1 = in2.size(1);
  } else {
    i1 = in3.size(1);
  }
  in1.set_size(i, i1);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    if (in4_idx_0 == 1) {
      b_loop_ub = in2.size(0);
    } else {
      b_loop_ub = in4_idx_0;
    }
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] =
          in2[i1 * stride_0_0 + in2.size(0) * aux_0_1] + in3[aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
//                const unsigned int in4[2]
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<double, 2U> &in3,
                             const unsigned int in4[2])
{
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int in4_idx_0;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_1;
  in4_idx_0 = static_cast<int>(in4[0]);
  if (in4_idx_0 == 1) {
    i = in2.size(0);
  } else {
    i = in4_idx_0;
  }
  if (in3.size(1) == 1) {
    i1 = in2.size(1);
  } else {
    i1 = in3.size(1);
  }
  in1.set_size(i, i1);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    if (in4_idx_0 == 1) {
      b_loop_ub = in2.size(0);
    } else {
      b_loop_ub = in4_idx_0;
    }
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] =
          in2[i1 * stride_0_0 + in2.size(0) * aux_0_1] - in3[aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

//
// Arguments    : coder::array<double, 1U> &in1
//                double in2
//                const coder::array<double, 1U> &in3
//                const coder::array<double, 1U> &in4
//                const coder::array<double, 1U> &in5
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 1U> &in1, double in2,
                             const coder::array<double, 1U> &in3,
                             const coder::array<double, 1U> &in4,
                             const coder::array<double, 1U> &in5)
{
  coder::array<double, 1U> b_in1;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  int stride_3_0;
  if (in5.size(0) == 1) {
    if (in4.size(0) == 1) {
      i = in3.size(0);
    } else {
      i = in4.size(0);
    }
  } else {
    i = in5.size(0);
  }
  if (i == 1) {
    i = in1.size(0);
  } else if (in5.size(0) == 1) {
    if (in4.size(0) == 1) {
      i = in3.size(0);
    } else {
      i = in4.size(0);
    }
  } else {
    i = in5.size(0);
  }
  b_in1.set_size(i);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_2_0 = (in4.size(0) != 1);
  stride_3_0 = (in5.size(0) != 1);
  if (in5.size(0) == 1) {
    if (in4.size(0) == 1) {
      i = in3.size(0);
    } else {
      i = in4.size(0);
    }
  } else {
    i = in5.size(0);
  }
  if (i == 1) {
    loop_ub = in1.size(0);
  } else if (in5.size(0) == 1) {
    if (in4.size(0) == 1) {
      loop_ub = in3.size(0);
    } else {
      loop_ub = in4.size(0);
    }
  } else {
    loop_ub = in5.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    double in1_tmp;
    in1_tmp = in5[i * stride_3_0];
    b_in1[i] =
        in1[i * stride_0_0] +
        in2 * (in3[i * stride_1_0] - in4[i * stride_2_0]) / (in1_tmp * in1_tmp);
  }
  in1.set_size(b_in1.size(0));
  loop_ub = b_in1.size(0);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : coder::array<double, 1U> &in1
//                double in2
//                const coder::array<double, 1U> &in3
//                double in4
//                const coder::array<double, 1U> &in5
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 1U> &in1, double in2,
                             const coder::array<double, 1U> &in3, double in4,
                             const coder::array<double, 1U> &in5)
{
  coder::array<double, 1U> b_in1;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  if (in5.size(0) == 1) {
    i = in3.size(0);
  } else {
    i = in5.size(0);
  }
  if (i == 1) {
    i = in1.size(0);
  } else if (in5.size(0) == 1) {
    i = in3.size(0);
  } else {
    i = in5.size(0);
  }
  b_in1.set_size(i);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_2_0 = (in5.size(0) != 1);
  if (in5.size(0) == 1) {
    i = in3.size(0);
  } else {
    i = in5.size(0);
  }
  if (i == 1) {
    loop_ub = in1.size(0);
  } else if (in5.size(0) == 1) {
    loop_ub = in3.size(0);
  } else {
    loop_ub = in5.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    b_in1[i] = in1[i * stride_0_0] +
               (in2 * in3[i * stride_1_0] - in4 * in5[i * stride_2_0]);
  }
  in1.set_size(b_in1.size(0));
  loop_ub = b_in1.size(0);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                double in2
//                const coder::array<double, 2U> &in3
//                const coder::array<double, 2U> &in4
//                double in5
//                const coder::array<double, 2U> &in6
//                const coder::array<double, 2U> &in7
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1, double in2,
                             const coder::array<double, 2U> &in3,
                             const coder::array<double, 2U> &in4, double in5,
                             const coder::array<double, 2U> &in6,
                             const coder::array<double, 2U> &in7)
{
  coder::array<double, 2U> b_in1;
  int aux_0_1;
  int aux_1_1;
  int aux_2_1;
  int aux_3_1;
  int aux_4_1;
  int b_loop_ub;
  int i;
  int i1;
  int i2;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  int stride_2_0;
  int stride_2_1;
  int stride_3_0;
  int stride_3_1;
  int stride_4_0;
  int stride_4_1;
  if (in7.size(0) == 1) {
    i = in6.size(0);
  } else {
    i = in7.size(0);
  }
  if (i == 1) {
    if (in4.size(0) == 1) {
      i = in3.size(0);
    } else {
      i = in4.size(0);
    }
  } else if (in7.size(0) == 1) {
    i = in6.size(0);
  } else {
    i = in7.size(0);
  }
  if (in7.size(0) == 1) {
    i1 = in6.size(0);
  } else {
    i1 = in7.size(0);
  }
  if (i == 1) {
    i = in1.size(0);
  } else if (i1 == 1) {
    if (in4.size(0) == 1) {
      i = in3.size(0);
    } else {
      i = in4.size(0);
    }
  } else if (in7.size(0) == 1) {
    i = in6.size(0);
  } else {
    i = in7.size(0);
  }
  if (in7.size(1) == 1) {
    i1 = in6.size(1);
  } else {
    i1 = in7.size(1);
  }
  if (i1 == 1) {
    if (in4.size(1) == 1) {
      i1 = in3.size(1);
    } else {
      i1 = in4.size(1);
    }
  } else if (in7.size(1) == 1) {
    i1 = in6.size(1);
  } else {
    i1 = in7.size(1);
  }
  if (in7.size(1) == 1) {
    i2 = in6.size(1);
  } else {
    i2 = in7.size(1);
  }
  if (i1 == 1) {
    i1 = in1.size(1);
  } else if (i2 == 1) {
    if (in4.size(1) == 1) {
      i1 = in3.size(1);
    } else {
      i1 = in4.size(1);
    }
  } else if (in7.size(1) == 1) {
    i1 = in6.size(1);
  } else {
    i1 = in7.size(1);
  }
  b_in1.set_size(i, i1);
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  stride_2_0 = (in4.size(0) != 1);
  stride_2_1 = (in4.size(1) != 1);
  stride_3_0 = (in6.size(0) != 1);
  stride_3_1 = (in6.size(1) != 1);
  stride_4_0 = (in7.size(0) != 1);
  stride_4_1 = (in7.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  aux_3_1 = 0;
  aux_4_1 = 0;
  if (in7.size(1) == 1) {
    i = in6.size(1);
  } else {
    i = in7.size(1);
  }
  if (i == 1) {
    if (in4.size(1) == 1) {
      i = in3.size(1);
    } else {
      i = in4.size(1);
    }
  } else if (in7.size(1) == 1) {
    i = in6.size(1);
  } else {
    i = in7.size(1);
  }
  if (i == 1) {
    loop_ub = in1.size(1);
  } else {
    if (in7.size(1) == 1) {
      i = in6.size(1);
    } else {
      i = in7.size(1);
    }
    if (i == 1) {
      if (in4.size(1) == 1) {
        loop_ub = in3.size(1);
      } else {
        loop_ub = in4.size(1);
      }
    } else if (in7.size(1) == 1) {
      loop_ub = in6.size(1);
    } else {
      loop_ub = in7.size(1);
    }
  }
  for (i = 0; i < loop_ub; i++) {
    int i3;
    int i4;
    i1 = in7.size(0);
    b_loop_ub = in6.size(0);
    i2 = in4.size(0);
    i3 = in3.size(0);
    if (i1 == 1) {
      i4 = b_loop_ub;
    } else {
      i4 = i1;
    }
    if (i4 == 1) {
      if (i2 == 1) {
        i4 = i3;
      } else {
        i4 = i2;
      }
    } else if (i1 == 1) {
      i4 = b_loop_ub;
    } else {
      i4 = i1;
    }
    if (i4 == 1) {
      b_loop_ub = in1.size(0);
    } else {
      if (i1 == 1) {
        i4 = b_loop_ub;
      } else {
        i4 = i1;
      }
      if (i4 == 1) {
        if (i2 == 1) {
          b_loop_ub = i3;
        } else {
          b_loop_ub = i2;
        }
      } else if (i1 != 1) {
        b_loop_ub = i1;
      }
    }
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] =
          in1[i1 * stride_0_0 + in1.size(0) * aux_0_1] +
          (in2 * (in3[i1 * stride_1_0 + in3.size(0) * aux_1_1] +
                  in4[i1 * stride_2_0 + in4.size(0) * aux_2_1]) -
           in5 * (in6[i1 * stride_3_0 + in6.size(0) * aux_3_1] +
                  in7[i1 * stride_4_0 + in7.size(0) * aux_4_1]));
    }
    aux_4_1 += stride_4_1;
    aux_3_1 += stride_3_1;
    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  in1.set_size(b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
static int div_s32(int numerator, int denominator)
{
  int quotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    unsigned int tempAbsQuotient;
    unsigned int u;
    if (numerator < 0) {
      tempAbsQuotient = ~static_cast<unsigned int>(numerator) + 1U;
    } else {
      tempAbsQuotient = static_cast<unsigned int>(numerator);
    }
    if (denominator < 0) {
      u = ~static_cast<unsigned int>(denominator) + 1U;
    } else {
      u = static_cast<unsigned int>(denominator);
    }
    tempAbsQuotient /= u;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -static_cast<int>(tempAbsQuotient);
    } else {
      quotient = static_cast<int>(tempAbsQuotient);
    }
  }
  return quotient;
}

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_remd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1) || std::isinf(u0)) {
    y = rtNaN;
  } else if (std::isinf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
    double q;
    q = std::abs(u0 / u1);
    if (!(std::abs(q - std::floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = std::fmod(u0, u1);
    }
  } else {
    y = std::fmod(u0, u1);
  }
  return y;
}

//
// Arguments    : double varargin_1
//                const double varargin_2[4]
//                ::coder::array<double, 2U> &h
// Return Type  : void
//
namespace coder {
void firls(double varargin_1, const double varargin_2[4],
           ::coder::array<double, 2U> &h)
{
  static const signed char A[4]{1, 1, 0, 0};
  array<double, 2U> G;
  array<double, 2U> I1;
  array<double, 2U> I2;
  array<double, 2U> b_y_tmp;
  array<double, 2U> m;
  array<double, 2U> r;
  array<double, 2U> r1;
  array<double, 2U> y_tmp;
  array<double, 1U> b;
  array<double, 1U> b_k;
  array<double, 1U> c_k;
  array<double, 1U> y;
  double d;
  double xtmp;
  int i;
  int idx;
  int k;
  boolean_T Nodd;
  boolean_T exitg1;
  Nodd = std::isnan(varargin_2[0]);
  if (!Nodd) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 5)) {
      if (!std::isnan(varargin_2[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    xtmp = varargin_2[0];
  } else {
    xtmp = varargin_2[idx - 1];
    i = idx + 1;
    for (k = i; k < 5; k++) {
      d = varargin_2[k - 1];
      if (xtmp < d) {
        xtmp = d;
      }
    }
  }
  if (!(xtmp > 1.0)) {
    if (!Nodd) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k < 5)) {
        if (!std::isnan(varargin_2[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      xtmp = varargin_2[0];
    } else {
      xtmp = varargin_2[idx - 1];
      i = idx + 1;
      for (k = i; k < 5; k++) {
        d = varargin_2[k - 1];
        if (xtmp > d) {
          xtmp = d;
        }
      }
    }
    if (!(xtmp < 0.0)) {
      double F[4];
      double L;
      double b0;
      int b_loop_ub;
      int loop_ub;
      int md2;
      int s;
      boolean_T need_matrix;
      F[0] = varargin_2[0] / 2.0;
      F[1] = varargin_2[1] / 2.0;
      F[2] = varargin_2[2] / 2.0;
      F[3] = varargin_2[3] / 2.0;
      L = ((varargin_1 + 1.0) - 1.0) / 2.0;
      Nodd = (rt_remd_snf(varargin_1 + 1.0, 2.0) == 1.0);
      b0 = 0.0;
      if (!Nodd) {
        m.set_size(1, static_cast<int>(L) + 1);
        loop_ub = static_cast<int>(L);
        for (i = 0; i <= loop_ub; i++) {
          m[i] = static_cast<double>(i) + 0.5;
        }
      } else {
        m.set_size(1, static_cast<int>(L) + 1);
        loop_ub = static_cast<int>(L);
        for (i = 0; i <= loop_ub; i++) {
          m[i] = i;
        }
      }
      b_k.set_size(m.size(1));
      loop_ub = m.size(1);
      for (i = 0; i < loop_ub; i++) {
        b_k[i] = m[i];
      }
      need_matrix = (F[2] - F[1] != 0.0);
      if (need_matrix) {
        unsigned int uv[2];
        c_k.set_size(m.size(1));
        loop_ub = m.size(1);
        for (i = 0; i < loop_ub; i++) {
          c_k[i] = m[i];
        }
        G.set_size(c_k.size(0), m.size(1));
        loop_ub = m.size(1);
        for (i = 0; i < loop_ub; i++) {
          b_loop_ub = c_k.size(0);
          for (s = 0; s < b_loop_ub; s++) {
            G[s + G.size(0) * i] = c_k[s];
          }
        }
        uv[0] = static_cast<unsigned int>(c_k.size(0));
        uv[1] = 1U;
        if ((G.size(0) == c_k.size(0)) && (G.size(1) == m.size(1))) {
          I1.set_size(G.size(0), G.size(1));
          loop_ub = G.size(1);
          for (i = 0; i < loop_ub; i++) {
            b_loop_ub = G.size(0);
            for (s = 0; s < b_loop_ub; s++) {
              I1[s + I1.size(0) * i] = G[s + G.size(0) * i] + m[i];
            }
          }
        } else {
          b_binary_expand_op(I1, G, m, uv);
        }
        if ((G.size(0) == static_cast<int>(uv[0])) &&
            (G.size(1) == m.size(1))) {
          I2.set_size(G.size(0), G.size(1));
          loop_ub = G.size(1);
          for (i = 0; i < loop_ub; i++) {
            b_loop_ub = G.size(0);
            for (s = 0; s < b_loop_ub; s++) {
              I2[s + I2.size(0) * i] = G[s + G.size(0) * i] - m[i];
            }
          }
        } else {
          binary_expand_op(I2, G, m, uv);
        }
        G.set_size(m.size(1), m.size(1));
        loop_ub = m.size(1) * m.size(1);
        for (i = 0; i < loop_ub; i++) {
          G[i] = 0.0;
        }
      } else {
        I1.set_size(0, 0);
        I2.set_size(0, 0);
        G.set_size(0, 0);
      }
      if (Nodd) {
        if (b_k.size(0) < 2) {
          i = 0;
          s = 0;
        } else {
          i = 1;
          s = b_k.size(0);
        }
        idx = s - i;
        for (s = 0; s < idx; s++) {
          b_k[s] = b_k[i + s];
        }
        b_k.set_size(idx);
      }
      b.set_size(b_k.size(0));
      loop_ub = b_k.size(0);
      for (i = 0; i < loop_ub; i++) {
        b[i] = 0.0;
      }
      loop_ub = b_k.size(0);
      b_loop_ub = b_k.size(0);
      for (s = 0; s < 2; s++) {
        double a;
        double b1;
        double b1_tmp;
        double m_s;
        double m_s_tmp_tmp;
        int i2;
        signed char i1;
        md2 = s << 1;
        m_s_tmp_tmp = F[md2 + 1];
        d = F[md2];
        xtmp = m_s_tmp_tmp - d;
        i1 = A[md2];
        m_s = static_cast<double>(A[md2 + 1] - i1) / xtmp;
        b1_tmp = m_s * d;
        b1 = static_cast<double>(i1) - b1_tmp;
        if (Nodd) {
          b0 += b1 * xtmp + m_s / 2.0 * (m_s_tmp_tmp * m_s_tmp_tmp - d * d);
        }
        c_k.set_size(b_k.size(0));
        for (i = 0; i < loop_ub; i++) {
          c_k[i] = 6.2831853071795862 * b_k[i];
        }
        y.set_size(c_k.size(0));
        idx = c_k.size(0);
        for (i = 0; i < idx; i++) {
          y[i] = c_k[i] * m_s_tmp_tmp;
        }
        idx = y.size(0);
        for (k = 0; k < idx; k++) {
          y[k] = std::cos(y[k]);
        }
        idx = c_k.size(0);
        for (i = 0; i < idx; i++) {
          c_k[i] = c_k[i] * F[md2];
        }
        idx = c_k.size(0);
        for (k = 0; k < idx; k++) {
          c_k[k] = std::cos(c_k[k]);
        }
        a = m_s / 39.478417604357432;
        idx = b.size(0);
        if (y.size(0) == 1) {
          i = c_k.size(0);
        } else {
          i = y.size(0);
        }
        if (y.size(0) == 1) {
          i2 = c_k.size(0);
        } else {
          i2 = y.size(0);
        }
        if (i2 == 1) {
          i2 = b_k.size(0);
        } else if (y.size(0) == 1) {
          i2 = c_k.size(0);
        } else {
          i2 = y.size(0);
        }
        if ((y.size(0) == c_k.size(0)) && (i == b_k.size(0)) &&
            (b.size(0) == i2)) {
          for (i = 0; i < idx; i++) {
            b[i] = b[i] + a * (y[i] - c_k[i]) / (b_k[i] * b_k[i]);
          }
        } else {
          binary_expand_op(b, a, y, c_k, b_k);
        }
        c_k.set_size(b_k.size(0));
        for (i = 0; i < b_loop_ub; i++) {
          c_k[i] = 2.0 * b_k[i];
        }
        y.set_size(c_k.size(0));
        idx = c_k.size(0);
        for (i = 0; i < idx; i++) {
          y[i] = c_k[i] * m_s_tmp_tmp;
        }
        a = m_s_tmp_tmp * (m_s * m_s_tmp_tmp + b1);
        i = y.size(0);
        for (k = 0; k < i; k++) {
          if (std::abs(y[k]) < 1.0020841800044864E-292) {
            y[k] = 1.0;
          } else {
            d = 3.1415926535897931 * y[k];
            d = std::sin(d) / d;
            y[k] = d;
          }
        }
        idx = c_k.size(0);
        for (i = 0; i < idx; i++) {
          c_k[i] = c_k[i] * F[md2];
        }
        xtmp = F[md2] * (b1_tmp + b1);
        i = c_k.size(0);
        for (k = 0; k < i; k++) {
          if (std::abs(c_k[k]) < 1.0020841800044864E-292) {
            c_k[k] = 1.0;
          } else {
            d = 3.1415926535897931 * c_k[k];
            d = std::sin(d) / d;
            c_k[k] = d;
          }
        }
        idx = b.size(0);
        if (y.size(0) == 1) {
          i = c_k.size(0);
        } else {
          i = y.size(0);
        }
        if ((y.size(0) == c_k.size(0)) && (b.size(0) == i)) {
          for (i = 0; i < idx; i++) {
            b[i] = b[i] + (a * y[i] - xtmp * c_k[i]);
          }
        } else {
          binary_expand_op(b, a, y, xtmp, c_k);
        }
        if (need_matrix) {
          int i3;
          y_tmp.set_size(I1.size(0), I1.size(1));
          idx = I1.size(0) * I1.size(1);
          for (i = 0; i < idx; i++) {
            y_tmp[i] = 2.0 * I1[i];
          }
          r.set_size(y_tmp.size(0), y_tmp.size(1));
          idx = y_tmp.size(0) * y_tmp.size(1);
          for (i = 0; i < idx; i++) {
            r[i] = y_tmp[i] * m_s_tmp_tmp;
          }
          i = r.size(0) * r.size(1);
          for (k = 0; k < i; k++) {
            if (std::abs(r[k]) < 1.0020841800044864E-292) {
              r[k] = 1.0;
            } else {
              r[k] = 3.1415926535897931 * r[k];
              r[k] = std::sin(r[k]) / r[k];
            }
          }
          b_y_tmp.set_size(I2.size(0), I2.size(1));
          idx = I2.size(0) * I2.size(1);
          for (i = 0; i < idx; i++) {
            b_y_tmp[i] = 2.0 * I2[i];
          }
          r1.set_size(b_y_tmp.size(0), b_y_tmp.size(1));
          idx = b_y_tmp.size(0) * b_y_tmp.size(1);
          for (i = 0; i < idx; i++) {
            r1[i] = b_y_tmp[i] * m_s_tmp_tmp;
          }
          i = r1.size(0) * r1.size(1);
          for (k = 0; k < i; k++) {
            if (std::abs(r1[k]) < 1.0020841800044864E-292) {
              r1[k] = 1.0;
            } else {
              r1[k] = 3.1415926535897931 * r1[k];
              r1[k] = std::sin(r1[k]) / r1[k];
            }
          }
          idx = y_tmp.size(0) * y_tmp.size(1);
          for (i = 0; i < idx; i++) {
            y_tmp[i] = y_tmp[i] * F[md2];
          }
          i = y_tmp.size(0) * y_tmp.size(1);
          for (k = 0; k < i; k++) {
            if (std::abs(y_tmp[k]) < 1.0020841800044864E-292) {
              y_tmp[k] = 1.0;
            } else {
              y_tmp[k] = 3.1415926535897931 * y_tmp[k];
              y_tmp[k] = std::sin(y_tmp[k]) / y_tmp[k];
            }
          }
          idx = b_y_tmp.size(0) * b_y_tmp.size(1);
          for (i = 0; i < idx; i++) {
            b_y_tmp[i] = b_y_tmp[i] * F[md2];
          }
          i = b_y_tmp.size(0) * b_y_tmp.size(1);
          for (k = 0; k < i; k++) {
            if (std::abs(b_y_tmp[k]) < 1.0020841800044864E-292) {
              b_y_tmp[k] = 1.0;
            } else {
              b_y_tmp[k] = 3.1415926535897931 * b_y_tmp[k];
              b_y_tmp[k] = std::sin(b_y_tmp[k]) / b_y_tmp[k];
            }
          }
          a = 0.5 * m_s_tmp_tmp;
          xtmp = 0.5 * F[md2];
          if (r.size(0) == 1) {
            i = r1.size(0);
          } else {
            i = r.size(0);
          }
          if (y_tmp.size(0) == 1) {
            i2 = b_y_tmp.size(0);
          } else {
            i2 = y_tmp.size(0);
          }
          if (r.size(1) == 1) {
            idx = r1.size(1);
          } else {
            idx = r.size(1);
          }
          if (y_tmp.size(1) == 1) {
            k = b_y_tmp.size(1);
          } else {
            k = y_tmp.size(1);
          }
          if (r.size(0) == 1) {
            md2 = r1.size(0);
          } else {
            md2 = r.size(0);
          }
          if (md2 == 1) {
            if (y_tmp.size(0) == 1) {
              md2 = b_y_tmp.size(0);
            } else {
              md2 = y_tmp.size(0);
            }
          } else if (r.size(0) == 1) {
            md2 = r1.size(0);
          } else {
            md2 = r.size(0);
          }
          if (r.size(1) == 1) {
            i3 = r1.size(1);
          } else {
            i3 = r.size(1);
          }
          if (i3 == 1) {
            if (y_tmp.size(1) == 1) {
              i3 = b_y_tmp.size(1);
            } else {
              i3 = y_tmp.size(1);
            }
          } else if (r.size(1) == 1) {
            i3 = r1.size(1);
          } else {
            i3 = r.size(1);
          }
          if ((r.size(0) == r1.size(0)) && (r.size(1) == r1.size(1)) &&
              (y_tmp.size(0) == b_y_tmp.size(0)) &&
              (y_tmp.size(1) == b_y_tmp.size(1)) && (i == i2) && (idx == k) &&
              (G.size(0) == md2) && (G.size(1) == i3)) {
            idx = G.size(0) * G.size(1);
            for (i = 0; i < idx; i++) {
              G[i] =
                  G[i] + (a * (r[i] + r1[i]) - xtmp * (y_tmp[i] + b_y_tmp[i]));
            }
          } else {
            binary_expand_op(G, a, r, r1, xtmp, y_tmp, b_y_tmp);
          }
        }
      }
      if (Nodd) {
        b_k.set_size(b.size(0) + 1);
        b_k[0] = b0;
        loop_ub = b.size(0);
        for (i = 0; i < loop_ub; i++) {
          b_k[i + 1] = b[i];
        }
        b.set_size(b_k.size(0));
        loop_ub = b_k.size(0);
        for (i = 0; i < loop_ub; i++) {
          b[i] = b_k[i];
        }
      }
      if (need_matrix) {
        mldivide(G, b);
      } else {
        loop_ub = b.size(0);
        for (i = 0; i < loop_ub; i++) {
          b[i] = 4.0 * b[i];
        }
        if (Nodd) {
          b[0] = b[0] / 2.0;
        }
      }
      if (Nodd) {
        if (L + 1.0 < 2.0) {
          i = 0;
          s = 1;
          md2 = -1;
          k = 0;
          idx = 0;
        } else {
          i = static_cast<int>(L + 1.0) - 1;
          s = -1;
          md2 = 1;
          k = 1;
          idx = static_cast<int>(L + 1.0);
        }
        loop_ub = div_s32(md2 - i, s);
        h.set_size(1, ((loop_ub + idx) - k) + 2);
        for (md2 = 0; md2 <= loop_ub; md2++) {
          h[md2] = b[i + s * md2] / 2.0;
        }
        h[loop_ub + 1] = b[0];
        b_loop_ub = idx - k;
        for (i = 0; i < b_loop_ub; i++) {
          h[(i + loop_ub) + 2] = b[k + i] / 2.0;
        }
      } else {
        c_k.set_size(b.size(0));
        loop_ub = b.size(0);
        for (i = 0; i < loop_ub; i++) {
          c_k[i] = b[i];
        }
        idx = b.size(0) - 1;
        md2 = b.size(0) >> 1;
        for (s = 0; s < md2; s++) {
          xtmp = c_k[s];
          k = idx - s;
          c_k[s] = c_k[k];
          c_k[k] = xtmp;
        }
        h.set_size(1, c_k.size(0) + b.size(0));
        loop_ub = c_k.size(0);
        for (i = 0; i < loop_ub; i++) {
          h[i] = 0.5 * c_k[i];
        }
        loop_ub = b.size(0);
        for (i = 0; i < loop_ub; i++) {
          h[i + c_k.size(0)] = 0.5 * b[i];
        }
      }
    }
  }
}

} // namespace coder

//
// File trailer for firls.cpp
//
// [EOF]
//
