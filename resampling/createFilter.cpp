//
// File: createFilter.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 29-Mar-2023 00:10:34
//

// Include Files
#include "createFilter.h"
#include "casyi.h"
#include "cmlri.h"
#include "firls.h"
#include "gammaln.h"
#include "mod.h"
#include "resampling_data.h"
#include "resampling_rtwutil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
static void binary_expand_op(coder::array<double, 2U> &in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<double, 1U> &in3);

// Function Definitions
//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 1U> &in3
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<double, 1U> &in3)
{
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in3.size(0) == 1) {
    i = in2.size(1);
  } else {
    i = in3.size(0);
  }
  in1.set_size(1, i);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(0) != 1);
  if (in3.size(0) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    in1[i] = in2[i * stride_0_1] * in3[i * stride_1_1];
  }
}

//
// Arguments    : double Lx
//                double p
//                double q
//                ::coder::array<double, 2U> &h
//                ::coder::array<double, 2U> &ht
//                double *delay
// Return Type  : void
//
namespace coder {
namespace signal {
namespace internal {
namespace resample {
void createFilter(double Lx, double p, double q, ::coder::array<double, 2U> &h,
                  ::coder::array<double, 2U> &ht, double *delay)
{
  array<double, 2U> r;
  array<double, 1U> r1;
  creal_T tmp;
  creal_T zd;
  double dv[4];
  double L;
  double fc;
  double pqmax;
  int inw;
  int iseven;
  int lastBlockLength;
  int mid;
  int nblocks;
  int nw;
  pqmax = std::fmax(p, q);
  fc = 0.5 / pqmax;
  L = 20.0 * pqmax + 1.0;
  dv[0] = 0.0;
  dv[1] = 2.0 * fc;
  dv[2] = 2.0 * fc;
  dv[3] = 1.0;
  firls(L - 1.0, dv, r);
  if (L == std::floor(L)) {
    nw = static_cast<int>(L);
  } else {
    nw = static_cast<int>(std::round(L));
  }
  r1.set_size(nw);
  if (nw <= 1) {
    r1.set_size(nw);
    for (inw = 0; inw < nw; inw++) {
      r1[inw] = 1.0;
    }
  } else {
    iseven = 1 - (nw & 1);
    mid = (nw >> 1) + 1;
    if (mid <= nw) {
      zd.im = 0.0;
    }
    for (int k{mid}; k <= nw; k++) {
      double hz_im;
      double hz_re;
      pqmax = static_cast<double>(iseven + ((k - mid) << 1)) /
              (static_cast<double>(nw) - 1.0);
      zd.re = 5.0 * std::sqrt((1.0 - pqmax) * (pqmax + 1.0));
      if (std::isnan(zd.re)) {
        tmp.re = rtNaN;
        tmp.im = 0.0;
      } else {
        double AZ_tmp;
        boolean_T guard1{false};
        nblocks = 0;
        AZ_tmp = rt_hypotd_snf(zd.re, 0.0);
        if (AZ_tmp > 1.0737418235E+9) {
          nblocks = 4;
        } else if (AZ_tmp > 32767.999992370605) {
          nblocks = 3;
        }
        tmp.re = 0.0;
        tmp.im = 0.0;
        guard1 = false;
        if (AZ_tmp <= 2.0) {
          lastBlockLength = 0;
          if (AZ_tmp == 0.0) {
            tmp.re = 1.0;
            tmp.im = 0.0;
          } else if (AZ_tmp < 2.2250738585072014E-305) {
            tmp.re = 1.0;
            tmp.im = 0.0;
          } else {
            double acz;
            double cz_re;
            hz_re = 0.5 * zd.re;
            if (AZ_tmp > 4.7170688552396617E-153) {
              cz_re = hz_re * hz_re;
              acz = rt_hypotd_snf(cz_re, 0.0);
            } else {
              cz_re = 0.0;
              acz = 0.0;
            }
            pqmax = 1.0;
            gammaln(&pqmax);
            fc = std::log(hz_re) * 0.0 - pqmax;
            if (fc > -700.92179369444591) {
              double b_atol;
              double coef_im;
              double coef_re_tmp;
              coef_re_tmp = std::exp(fc);
              coef_im = coef_re_tmp * 0.0;
              b_atol = 2.2204460492503131E-16 * acz;
              hz_re = 1.0;
              hz_im = 0.0;
              if (!(acz < 2.2204460492503131E-16)) {
                double aa;
                double ak;
                double s;
                fc = 1.0;
                pqmax = 0.0;
                ak = 3.0;
                s = 1.0;
                aa = 2.0;
                double re;
                double rs;
                do {
                  rs = 1.0 / s;
                  re = fc * cz_re - pqmax * 0.0;
                  pqmax = fc * 0.0 + pqmax * cz_re;
                  fc = rs * re;
                  pqmax *= rs;
                  hz_re += fc;
                  hz_im += pqmax;
                  s += ak;
                  ak += 2.0;
                  aa = aa * acz * rs;
                } while (!!(aa > b_atol));
              }
              pqmax = hz_re * coef_re_tmp - hz_im * coef_im;
              hz_im = hz_re * coef_im + hz_im * coef_re_tmp;
              tmp.re = pqmax - hz_im * 0.0;
              tmp.im = pqmax * 0.0 + hz_im;
            } else {
              lastBlockLength = 1;
              if (acz > 0.0) {
                lastBlockLength = -1;
              }
            }
          }
          if (lastBlockLength < 0) {
            inw = 1;
          } else {
            inw = lastBlockLength;
          }
          if ((1 - inw != 0) && (lastBlockLength < 0)) {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }
        if (guard1) {
          if (AZ_tmp < 21.784271729432426) {
            lastBlockLength = cmlri(zd, &tmp);
            if (lastBlockLength < 0) {
              if (lastBlockLength == -2) {
                inw = -2;
              } else {
                inw = -1;
              }
            } else {
              inw = 0;
            }
          } else {
            lastBlockLength = casyi(zd, &tmp);
            if (lastBlockLength < 0) {
              if (lastBlockLength == -2) {
                inw = -2;
              } else {
                inw = -1;
              }
            } else {
              inw = 0;
            }
          }
        }
        guard1 = false;
        if (inw < 0) {
          if (inw == -2) {
            tmp.re = rtNaN;
            tmp.im = 0.0;
          } else {
            nblocks = 2;
            guard1 = true;
          }
        } else {
          guard1 = true;
        }
        if (guard1 && (nblocks == 2)) {
          tmp.re = rtInf;
          tmp.im = 0.0;
        }
        if (zd.re > 0.0) {
          pqmax = tmp.re;
          tmp.re = pqmax;
          tmp.im = 0.0;
        }
      }
      if (tmp.im == 0.0) {
        hz_re = tmp.re / 27.239871823604449;
        hz_im = 0.0;
      } else if (tmp.re == 0.0) {
        hz_re = 0.0;
        hz_im = tmp.im / 27.239871823604449;
      } else {
        hz_re = tmp.re / 27.239871823604449;
        hz_im = tmp.im / 27.239871823604449;
      }
      r1[k - 1] = rt_hypotd_snf(hz_re, hz_im);
    }
    for (int k{0}; k <= mid - 2; k++) {
      r1[k] = r1[(nw - k) - 1];
    }
  }
  if (r1.size(0) == r.size(1)) {
    h.set_size(1, r.size(1));
    iseven = r.size(1);
    for (inw = 0; inw < iseven; inw++) {
      h[inw] = r[inw] * r1[inw];
    }
  } else {
    binary_expand_op(h, r, r1);
  }
  if (h.size(1) == 0) {
    pqmax = 0.0;
  } else {
    if (h.size(1) <= 1024) {
      iseven = h.size(1);
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      iseven = 1024;
      nblocks = static_cast<int>(static_cast<unsigned int>(h.size(1)) >> 10);
      lastBlockLength = h.size(1) - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    pqmax = h[0];
    for (int k{2}; k <= iseven; k++) {
      pqmax += h[k - 1];
    }
    for (inw = 2; inw <= nblocks; inw++) {
      iseven = (inw - 1) << 10;
      fc = h[iseven];
      if (inw == nblocks) {
        mid = lastBlockLength;
      } else {
        mid = 1024;
      }
      for (int k{2}; k <= mid; k++) {
        fc += h[(iseven + k) - 1];
      }
      pqmax += fc;
    }
  }
  h.set_size(1, h.size(1));
  iseven = h.size(1) - 1;
  for (inw = 0; inw <= iseven; inw++) {
    h[inw] = p * h[inw] / pqmax;
  }
  pqmax = (L - 1.0) / 2.0;
  fc = std::floor(q - b_mod(pqmax, q));
  r.set_size(1, h.size(1) + static_cast<int>(fc));
  iseven = static_cast<int>(fc);
  for (inw = 0; inw < iseven; inw++) {
    r[inw] = 0.0;
  }
  iseven = h.size(1);
  for (inw = 0; inw < iseven; inw++) {
    r[inw + static_cast<int>(fc)] = h[inw];
  }
  h.set_size(1, r.size(1));
  iseven = r.size(1);
  for (inw = 0; inw < iseven; inw++) {
    h[inw] = r[inw];
  }
  *delay = std::floor(std::ceil(pqmax + fc) / q);
  for (pqmax = 0.0;
       std::ceil((((Lx - 1.0) * p + static_cast<double>(h.size(1))) + pqmax) /
                 q) -
           *delay <
       std::ceil(Lx * p / q);
       pqmax++) {
  }
  inw = h.size(1);
  iseven = static_cast<int>(pqmax);
  h.set_size(h.size(0), h.size(1) + static_cast<int>(pqmax));
  for (mid = 0; mid < iseven; mid++) {
    h[inw + mid] = 0.0;
  }
  pqmax = static_cast<double>(h.size(1)) - pqmax;
  if (fc + 1.0 > pqmax) {
    inw = 0;
    mid = 0;
  } else {
    inw = static_cast<int>(fc + 1.0) - 1;
    mid = static_cast<int>(pqmax);
  }
  iseven = mid - inw;
  ht.set_size(1, iseven);
  for (mid = 0; mid < iseven; mid++) {
    ht[mid] = h[inw + mid];
  }
}

} // namespace resample
} // namespace internal
} // namespace signal
} // namespace coder

//
// File trailer for createFilter.cpp
//
// [EOF]
//
