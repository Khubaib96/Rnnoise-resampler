//
// File: xgeqp3.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 29-Mar-2023 00:10:34
//

// Include Files
#include "xgeqp3.h"
#include "resampling_rtwutil.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &A
//                ::coder::array<double, 1U> &tau
//                ::coder::array<int, 2U> &jpvt
// Return Type  : void
//
namespace coder {
namespace internal {
namespace lapack {
void xgeqp3(::coder::array<double, 2U> &A, ::coder::array<double, 1U> &tau,
            ::coder::array<int, 2U> &jpvt)
{
  array<double, 1U> vn1;
  array<double, 1U> vn2;
  array<double, 1U> work;
  int i;
  int knt;
  int m;
  int minmana;
  int n;
  boolean_T guard1{false};
  m = A.size(0);
  n = A.size(1);
  knt = A.size(0);
  minmana = A.size(1);
  if (knt <= minmana) {
    minmana = knt;
  }
  tau.set_size(minmana);
  for (i = 0; i < minmana; i++) {
    tau[i] = 0.0;
  }
  guard1 = false;
  if ((A.size(0) == 0) || (A.size(1) == 0)) {
    guard1 = true;
  } else {
    knt = A.size(0);
    minmana = A.size(1);
    if (knt <= minmana) {
      minmana = knt;
    }
    if (minmana < 1) {
      guard1 = true;
    } else {
      double smax;
      int k;
      int ma;
      int minmn;
      jpvt.set_size(1, A.size(1));
      minmana = A.size(1);
      for (i = 0; i < minmana; i++) {
        jpvt[i] = 0;
      }
      for (k = 0; k < n; k++) {
        jpvt[k] = k + 1;
      }
      ma = A.size(0);
      knt = A.size(0);
      minmn = A.size(1);
      if (knt <= minmn) {
        minmn = knt;
      }
      work.set_size(A.size(1));
      minmana = A.size(1);
      for (i = 0; i < minmana; i++) {
        work[i] = 0.0;
      }
      vn1.set_size(A.size(1));
      minmana = A.size(1);
      for (i = 0; i < minmana; i++) {
        vn1[i] = 0.0;
      }
      vn2.set_size(A.size(1));
      minmana = A.size(1);
      for (i = 0; i < minmana; i++) {
        vn2[i] = 0.0;
      }
      for (knt = 0; knt < n; knt++) {
        smax = blas::xnrm2(m, A, knt * ma + 1);
        vn1[knt] = smax;
        vn2[knt] = smax;
      }
      for (int b_i{0}; b_i < minmn; b_i++) {
        double s;
        double temp2;
        int ii;
        int ip1;
        int lastc;
        int mmi;
        int nmi;
        int pvt;
        ip1 = b_i + 2;
        lastc = b_i * ma;
        ii = lastc + b_i;
        nmi = n - b_i;
        mmi = m - b_i;
        if (nmi < 1) {
          minmana = -1;
        } else {
          minmana = 0;
          if (nmi > 1) {
            smax = std::abs(vn1[b_i]);
            for (k = 2; k <= nmi; k++) {
              s = std::abs(vn1[(b_i + k) - 1]);
              if (s > smax) {
                minmana = k - 1;
                smax = s;
              }
            }
          }
        }
        pvt = b_i + minmana;
        if (pvt + 1 != b_i + 1) {
          minmana = pvt * ma;
          for (k = 0; k < m; k++) {
            knt = minmana + k;
            smax = A[knt];
            i = lastc + k;
            A[knt] = A[i];
            A[i] = smax;
          }
          minmana = jpvt[pvt];
          jpvt[pvt] = jpvt[b_i];
          jpvt[b_i] = minmana;
          vn1[pvt] = vn1[b_i];
          vn2[pvt] = vn2[b_i];
        }
        if (b_i + 1 < m) {
          temp2 = A[ii];
          minmana = ii + 2;
          tau[b_i] = 0.0;
          if (mmi > 0) {
            smax = blas::xnrm2(mmi - 1, A, ii + 2);
            if (smax != 0.0) {
              s = rt_hypotd_snf(A[ii], smax);
              if (A[ii] >= 0.0) {
                s = -s;
              }
              if (std::abs(s) < 1.0020841800044864E-292) {
                knt = 0;
                i = ii + mmi;
                do {
                  knt++;
                  for (k = minmana; k <= i; k++) {
                    A[k - 1] = 9.9792015476736E+291 * A[k - 1];
                  }
                  s *= 9.9792015476736E+291;
                  temp2 *= 9.9792015476736E+291;
                } while ((std::abs(s) < 1.0020841800044864E-292) && (knt < 20));
                s = rt_hypotd_snf(temp2, blas::xnrm2(mmi - 1, A, ii + 2));
                if (temp2 >= 0.0) {
                  s = -s;
                }
                tau[b_i] = (s - temp2) / s;
                smax = 1.0 / (temp2 - s);
                for (k = minmana; k <= i; k++) {
                  A[k - 1] = smax * A[k - 1];
                }
                for (k = 0; k < knt; k++) {
                  s *= 1.0020841800044864E-292;
                }
                temp2 = s;
              } else {
                tau[b_i] = (s - A[ii]) / s;
                smax = 1.0 / (A[ii] - s);
                i = ii + mmi;
                for (k = minmana; k <= i; k++) {
                  A[k - 1] = smax * A[k - 1];
                }
                temp2 = s;
              }
            }
          }
          A[ii] = temp2;
        } else {
          tau[b_i] = 0.0;
        }
        if (b_i + 1 < n) {
          int jA;
          int lastv;
          temp2 = A[ii];
          A[ii] = 1.0;
          jA = (ii + ma) + 1;
          if (tau[b_i] != 0.0) {
            boolean_T exitg2;
            lastv = mmi - 1;
            minmana = (ii + mmi) - 1;
            while ((lastv + 1 > 0) && (A[minmana] == 0.0)) {
              lastv--;
              minmana--;
            }
            lastc = nmi - 2;
            exitg2 = false;
            while ((!exitg2) && (lastc + 1 > 0)) {
              int exitg1;
              minmana = jA + lastc * ma;
              k = minmana;
              do {
                exitg1 = 0;
                if (k <= minmana + lastv) {
                  if (A[k - 1] != 0.0) {
                    exitg1 = 1;
                  } else {
                    k++;
                  }
                } else {
                  lastc--;
                  exitg1 = 2;
                }
              } while (exitg1 == 0);
              if (exitg1 == 1) {
                exitg2 = true;
              }
            }
          } else {
            lastv = -1;
            lastc = -1;
          }
          if (lastv + 1 > 0) {
            if (lastc + 1 != 0) {
              for (knt = 0; knt <= lastc; knt++) {
                work[knt] = 0.0;
              }
              knt = 0;
              i = jA + ma * lastc;
              for (pvt = jA; ma < 0 ? pvt >= i : pvt <= i; pvt += ma) {
                smax = 0.0;
                minmana = pvt + lastv;
                for (k = pvt; k <= minmana; k++) {
                  smax += A[k - 1] * A[(ii + k) - pvt];
                }
                work[knt] = work[knt] + smax;
                knt++;
              }
            }
            if (!(-tau[b_i] == 0.0)) {
              for (knt = 0; knt <= lastc; knt++) {
                if (work[knt] != 0.0) {
                  smax = work[knt] * -tau[b_i];
                  i = lastv + jA;
                  for (minmana = jA; minmana <= i; minmana++) {
                    A[minmana - 1] =
                        A[minmana - 1] + A[(ii + minmana) - jA] * smax;
                  }
                }
                jA += ma;
              }
            }
          }
          A[ii] = temp2;
        }
        for (knt = ip1; knt <= n; knt++) {
          minmana = b_i + (knt - 1) * ma;
          smax = vn1[knt - 1];
          if (smax != 0.0) {
            s = std::abs(A[minmana]) / smax;
            s = 1.0 - s * s;
            if (s < 0.0) {
              s = 0.0;
            }
            temp2 = smax / vn2[knt - 1];
            temp2 = s * (temp2 * temp2);
            if (temp2 <= 1.4901161193847656E-8) {
              if (b_i + 1 < m) {
                smax = blas::xnrm2(mmi - 1, A, minmana + 2);
                vn1[knt - 1] = smax;
                vn2[knt - 1] = smax;
              } else {
                vn1[knt - 1] = 0.0;
                vn2[knt - 1] = 0.0;
              }
            } else {
              vn1[knt - 1] = smax * std::sqrt(s);
            }
          }
        }
      }
    }
  }
  if (guard1) {
    jpvt.set_size(1, A.size(1));
    minmana = A.size(1);
    for (i = 0; i < minmana; i++) {
      jpvt[i] = 0;
    }
    for (knt = 0; knt < n; knt++) {
      jpvt[knt] = knt + 1;
    }
  }
}

} // namespace lapack
} // namespace internal
} // namespace coder

//
// File trailer for xgeqp3.cpp
//
// [EOF]
//
