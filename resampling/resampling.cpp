//
// File: resampling.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 29-Mar-2023 00:10:34
//

// Include Files
#include "resampling.h"
#include "createFilter.h"
#include "ipermute.h"
#include "mod.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// calling resampler
//
// Arguments    : const coder::array<double, 1U> &x
//                double fs_new
//                double fs_old
//                coder::array<double, 1U> &y
// Return Type  : void
//
void resampling(const coder::array<double, 1U> &x, double fs_new, double fs_old,
                coder::array<double, 1U> &y)
{
  coder::array<double, 2U> b_y;
  coder::array<double, 2U> hout;
  coder::array<double, 2U> indV;
  coder::array<double, 2U> yVec;
  coder::array<double, 1U> yV1;
  double Ly;
  double absx;
  double d;
  double delay;
  double dlast;
  double n;
  double nlast;
  double p;
  double q;
  double rndx;
  double tmp;
  double xin;
  int exponent;
  int i;
  Ly = fs_new / fs_old;
  xin = Ly;
  absx = std::abs(Ly);
  if (std::isinf(absx) || std::isnan(absx)) {
    absx = rtNaN;
  } else if (absx < 4.4501477170144028E-308) {
    absx = 4.94065645841247E-324;
  } else {
    std::frexp(absx, &exponent);
    absx = std::ldexp(1.0, exponent - 53);
  }
  absx = std::fmax(1.0E-12, absx);
  if (std::isinf(Ly) || std::isnan(Ly)) {
    if (!std::isnan(Ly)) {
      if (Ly < 0.0) {
        p = -1.0;
      } else {
        p = 1.0;
      }
    } else {
      p = 0.0;
    }
    q = 0.0;
  } else {
    n = 1.0;
    d = 0.0;
    nlast = 0.0;
    dlast = 1.0;
    int exitg1;
    do {
      exitg1 = 0;
      rndx = std::round(Ly);
      if (!std::isinf(Ly)) {
        Ly -= rndx;
        tmp = nlast;
        nlast = n;
        n = n * rndx + tmp;
        tmp = dlast;
        dlast = d;
        d = d * rndx + tmp;
      } else {
        nlast = n;
        dlast = d;
        n = Ly;
        d = 0.0;
      }
      if ((Ly == 0.0) || (std::abs(n / d - xin) <= absx)) {
        exitg1 = 1;
      } else {
        Ly = 1.0 / Ly;
      }
    } while (exitg1 == 0);
    if (std::isnan(d)) {
      Ly = rtNaN;
    } else if (d < 0.0) {
      Ly = -1.0;
    } else {
      Ly = (d > 0.0);
    }
    p = n / Ly;
    q = std::abs(d);
  }
  if ((p == 1.0) && (q == 1.0)) {
    coder::ipermute(x, yV1);
    b_y.set_size(x.size(0), 1);
    exponent = x.size(0);
    for (i = 0; i < exponent; i++) {
      b_y[i] = yV1[i];
    }
  } else {
    double b_Ly;
    double pq;
    double sxTrue_idx_0;
    double sxTrue_idx_1;
    int Lh;
    int Lx;
    coder::signal::internal::resample::createFilter(
        static_cast<double>(x.size(0)), p, q, indV, hout, &delay);
    b_Ly = std::ceil(static_cast<double>(x.size(0)) * p / q);
    sxTrue_idx_0 = x.size(0);
    sxTrue_idx_1 = 1.0;
    if (x.size(0) == 1) {
      sxTrue_idx_1 = b_Ly;
    } else {
      sxTrue_idx_0 = b_Ly;
    }
    Lx = x.size(0);
    Lh = indV.size(1);
    pq = p * q;
    absx = p * (static_cast<double>(x.size(0)) - 1.0) +
           static_cast<double>(indV.size(1));
    if (std::isnan(absx)) {
      Ly = rtNaN;
    } else if (absx < 0.0) {
      Ly = -1.0;
    } else {
      Ly = (absx > 0.0);
    }
    if (Ly != 0.0) {
      n = coder::b_mod(absx, q);
    } else {
      n = coder::b_mod(absx, q) - q;
    }
    if (n != 0.0) {
      Ly = std::floor(absx / q + 1.0);
    } else {
      Ly = std::floor(absx / q);
    }
    exponent = static_cast<int>(Ly);
    y.set_size(exponent);
    for (i = 0; i < exponent; i++) {
      y[i] = 0.0;
    }
    i = static_cast<int>((p - 1.0) + 1.0);
    for (exponent = 0; exponent < i; exponent++) {
      xin = static_cast<double>(exponent) + 1.0;
      absx = static_cast<double>(exponent) * q;
      nlast = coder::b_mod(absx, p) + 1.0;
      absx = std::floor(absx / p);
      rndx = absx + 1.0;
      tmp = nlast + p * absx;
      dlast = (static_cast<double>(Lh) + 1.0) - nlast;
      if (coder::b_mod(dlast, p) != 0.0) {
        dlast = dlast / p + 1.0;
        dlast = std::floor(dlast);
      } else {
        dlast /= p;
        dlast = std::floor(dlast);
      }
      while ((rndx < static_cast<double>(Lx) + 1.0) &&
             (tmp < static_cast<double>(Lh) + 1.0)) {
        d = 0.0;
        absx = rndx;
        for (n = nlast; n <= tmp; n += p) {
          d += indV[static_cast<int>(n) - 1] * x[static_cast<int>(absx) - 1];
          absx--;
        }
        y[static_cast<int>(xin) - 1] = y[static_cast<int>(xin) - 1] + d;
        xin += p;
        rndx += q;
        tmp += pq;
      }
      if (rndx < static_cast<double>(Lx) + 1.0) {
        while (tmp >= static_cast<double>(Lh) + 1.0) {
          tmp -= p;
        }
        while (rndx < static_cast<double>(Lx) + 1.0) {
          d = 0.0;
          absx = rndx;
          for (n = nlast; n <= tmp; n += p) {
            d += indV[static_cast<int>(n) - 1] * x[static_cast<int>(absx) - 1];
            absx--;
          }
          if (xin < Ly + 1.0) {
            y[static_cast<int>(xin) - 1] = y[static_cast<int>(xin) - 1] + d;
          }
          xin += p;
          rndx += q;
        }
      } else if (tmp < static_cast<double>(Lh) + 1.0) {
        while (tmp < static_cast<double>(Lh) + 1.0) {
          d = 0.0;
          n = 1.0;
          nlast = tmp;
          while (static_cast<unsigned int>(n) <
                 static_cast<unsigned int>(Lx) + 1U) {
            d += indV[static_cast<int>(nlast) - 1] * x[static_cast<int>(n) - 1];
            n++;
            nlast -= p;
          }
          y[static_cast<int>(xin) - 1] = y[static_cast<int>(xin) - 1] + d;
          xin += p;
          rndx += q;
          tmp += pq;
        }
      }
      while (tmp >= static_cast<double>(Lh) + 1.0) {
        tmp -= p;
      }
      for (absx = (rndx - dlast) + 1.0; absx < static_cast<double>(Lx) + 1.0;
           absx += q) {
        d = 0.0;
        n = absx;
        nlast = tmp;
        while (n < static_cast<double>(Lx) + 1.0) {
          d += indV[static_cast<int>(nlast) - 1] * x[static_cast<int>(n) - 1];
          n++;
          nlast -= p;
        }
        y[static_cast<int>(xin) - 1] = y[static_cast<int>(xin) - 1] + d;
        xin += p;
      }
    }
    if (x.size(0) == 1) {
      yVec.set_size(1, y.size(0));
      exponent = y.size(0);
      for (i = 0; i < exponent; i++) {
        yVec[yVec.size(0) * i] = y[i];
      }
    } else {
      yVec.set_size(y.size(0), 1);
      exponent = y.size(0);
      for (i = 0; i < exponent; i++) {
        yVec[i] = y[i];
      }
    }
    if (std::isnan(b_Ly)) {
      indV.set_size(1, 1);
      indV[0] = rtNaN;
    } else if (b_Ly < 1.0) {
      indV.set_size(indV.size(0), 0);
    } else {
      indV.set_size(1, static_cast<int>(b_Ly - 1.0) + 1);
      exponent = static_cast<int>(b_Ly - 1.0);
      for (i = 0; i <= exponent; i++) {
        indV[i] = static_cast<double>(i) + 1.0;
      }
    }
    indV.set_size(1, indV.size(1));
    exponent = indV.size(1) - 1;
    for (i = 0; i <= exponent; i++) {
      indV[i] = delay + indV[i];
    }
    if (x.size(0) != 1) {
      yV1.set_size(indV.size(1));
      exponent = indV.size(1);
      for (i = 0; i < exponent; i++) {
        yV1[i] = indV[i];
      }
      b_y.set_size(yV1.size(0), 1);
      exponent = yV1.size(0);
      for (i = 0; i < exponent; i++) {
        b_y[i] = yVec[static_cast<int>(yV1[i]) - 1];
      }
    } else {
      yV1.set_size(indV.size(1));
      exponent = indV.size(1);
      for (i = 0; i < exponent; i++) {
        yV1[i] = yVec[static_cast<int>(indV[i]) - 1];
      }
      b_y.set_size(static_cast<int>(sxTrue_idx_0),
                   static_cast<int>(sxTrue_idx_1));
      exponent =
          static_cast<int>(sxTrue_idx_0) * static_cast<int>(sxTrue_idx_1);
      for (i = 0; i < exponent; i++) {
        b_y[i] = yV1[i];
      }
    }
  }
  y.set_size(b_y.size(0));
  exponent = b_y.size(0);
  for (i = 0; i < exponent; i++) {
    y[i] = b_y[i];
  }
}

//
// File trailer for resampling.cpp
//
// [EOF]
//
