/* PowerPC-64 gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 2008, 2009, 2011, 2017 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of either:

  * the GNU Lesser General Public License as published by the Free
    Software Foundation; either version 3 of the License, or (at your
    option) any later version.

or

  * the GNU General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any
    later version.

or both in parallel, as here.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received copies of the GNU General Public License and the
GNU Lesser General Public License along with the GNU MP Library.  If not,
see https://www.gnu.org/licenses/.  */

/* 1800 MHz PPC970 */
/* FFT tuning limit = 0.5 M */
/* Generated by tuneup.c, 2017-01-01, gcc 4.0 */

#define DIVREM_1_NORM_THRESHOLD              0  /* always */
#define DIVREM_1_UNNORM_THRESHOLD            0  /* always */
#define MOD_1_1P_METHOD                      1
#define MOD_1_NORM_THRESHOLD                 0  /* always */
#define MOD_1_UNNORM_THRESHOLD               0  /* always */
#define MOD_1N_TO_MOD_1_1_THRESHOLD          7
#define MOD_1U_TO_MOD_1_1_THRESHOLD          5
#define MOD_1_1_TO_MOD_1_2_THRESHOLD         6
#define MOD_1_2_TO_MOD_1_4_THRESHOLD        46
#define PREINV_MOD_1_TO_MOD_1_THRESHOLD     15
#define USE_PREINV_DIVREM_1                  1
#define DIV_QR_1N_PI1_METHOD                 1
#define DIV_QR_1_NORM_THRESHOLD              2
#define DIV_QR_1_UNNORM_THRESHOLD            2
#define DIV_QR_2_PI2_THRESHOLD              15
#define DIVEXACT_1_THRESHOLD                 0  /* always */
#define BMOD_1_TO_MOD_1_THRESHOLD           88

#define DIV_1_VS_MUL_1_PERCENT             269

#define MUL_TOOM22_THRESHOLD                18
#define MUL_TOOM33_THRESHOLD                60
#define MUL_TOOM44_THRESHOLD                88
#define MUL_TOOM6H_THRESHOLD               124
#define MUL_TOOM8H_THRESHOLD               187

#define MUL_TOOM32_TO_TOOM43_THRESHOLD      61
#define MUL_TOOM32_TO_TOOM53_THRESHOLD      91
#define MUL_TOOM42_TO_TOOM53_THRESHOLD      61
#define MUL_TOOM42_TO_TOOM63_THRESHOLD      60
#define MUL_TOOM43_TO_TOOM54_THRESHOLD      74

#define SQR_BASECASE_THRESHOLD               4
#define SQR_TOOM2_THRESHOLD                 28
#define SQR_TOOM3_THRESHOLD                 90
#define SQR_TOOM4_THRESHOLD                143
#define SQR_TOOM6_THRESHOLD                181
#define SQR_TOOM8_THRESHOLD                272

#define MULMID_TOOM42_THRESHOLD             34

#define MULMOD_BNM1_THRESHOLD               10
#define SQRMOD_BNM1_THRESHOLD               15

#define MUL_FFT_MODF_THRESHOLD             252  /* k = 5 */
#define MUL_FFT_TABLE3                                      \
  { {    252, 5}, {     11, 6}, {      6, 5}, {     13, 6}, \
    {      7, 5}, {     15, 6}, {     13, 5}, {     27, 6}, \
    {     15, 7}, {      8, 6}, {     17, 7}, {      9, 6}, \
    {     19, 7}, {     17, 8}, {      9, 7}, {     20, 8}, \
    {     11, 7}, {     23, 8}, {     13, 9}, {      7, 8}, \
    {     21, 9}, {     11, 8}, {     27,10}, {      7, 9}, \
    {     15, 8}, {     33, 9}, {     19, 8}, {     39, 9}, \
    {     23, 8}, {     47, 9}, {     27,10}, {     15, 9}, \
    {     39,10}, {     23, 9}, {     47,11}, {     15,10}, \
    {     31, 9}, {     67,10}, {     39, 9}, {     83,10}, \
    {     47, 9}, {     95, 8}, {    191,10}, {     55,11}, \
    {     31,10}, {     63, 9}, {    127, 8}, {    255,10}, \
    {     71, 9}, {    143, 8}, {    287,10}, {     79, 9}, \
    {    159, 8}, {    319,11}, {     47,10}, {     95, 9}, \
    {    191, 8}, {    383,10}, {    103,12}, {     31,11}, \
    {     63,10}, {    127, 9}, {    255, 8}, {    511,10}, \
    {    143, 9}, {    287,11}, {     79,10}, {    159, 9}, \
    {    319, 8}, {    639,10}, {    175, 9}, {    351, 8}, \
    {    703,11}, {     95,10}, {    191, 9}, {    383, 8}, \
    {    767,10}, {    207, 9}, {    415,10}, {    223, 9}, \
    {    447,12}, {     63,11}, {    127,10}, {    255, 9}, \
    {    511,11}, {    143,10}, {    287, 9}, {    575,11}, \
    {    159,10}, {    319, 9}, {    639,11}, {    175,10}, \
    {    351, 9}, {    703,12}, {     95,11}, {    191,10}, \
    {    383, 9}, {    767,11}, {    207,10}, {    415,11}, \
    {    223,10}, {    447,13}, {   8192,14}, {  16384,15}, \
    {  32768,16} }
#define MUL_FFT_TABLE3_SIZE 105
#define MUL_FFT_THRESHOLD                 5248

#define SQR_FFT_MODF_THRESHOLD             236  /* k = 5 */
#define SQR_FFT_TABLE3                                      \
  { {    236, 5}, {     13, 6}, {     15, 7}, {      8, 6}, \
    {     17, 7}, {      9, 6}, {     19, 7}, {     17, 8}, \
    {      9, 7}, {     20, 8}, {     11, 7}, {     24, 8}, \
    {     13, 9}, {      7, 8}, {     19, 9}, {     11, 8}, \
    {     25,10}, {      7, 9}, {     15, 8}, {     33, 9}, \
    {     19, 8}, {     39, 9}, {     23, 8}, {     47, 9}, \
    {     27,10}, {     15, 9}, {     39,10}, {     23, 9}, \
    {     47,11}, {     15,10}, {     31, 9}, {     67,10}, \
    {     39, 9}, {     79, 8}, {    159,10}, {     47, 9}, \
    {     95, 8}, {    191,11}, {     31,10}, {     63, 9}, \
    {    127, 8}, {    255,10}, {     71, 9}, {    143, 8}, \
    {    287,10}, {     79, 9}, {    159, 8}, {    319,11}, \
    {     47,10}, {     95, 9}, {    191, 8}, {    383,12}, \
    {     31,11}, {     63,10}, {    127, 9}, {    255, 8}, \
    {    511,10}, {    143, 9}, {    287, 8}, {    575,11}, \
    {     79,10}, {    159, 9}, {    319, 8}, {    639,10}, \
    {    175, 9}, {    351, 8}, {    703,11}, {     95,10}, \
    {    191, 9}, {    383, 8}, {    767,10}, {    207, 9}, \
    {    415,10}, {    223,12}, {     63,11}, {    127,10}, \
    {    255, 9}, {    511,11}, {    143,10}, {    287, 9}, \
    {    575,11}, {    159,10}, {    319, 9}, {    639,11}, \
    {    175,10}, {    351, 9}, {    703,11}, {    191,10}, \
    {    383, 9}, {    767,11}, {    207,10}, {    415,11}, \
    {    223,10}, {    447,13}, {   8192,14}, {  16384,15}, \
    {  32768,16} }
#define SQR_FFT_TABLE3_SIZE 97
#define SQR_FFT_THRESHOLD                 3200

#define MULLO_BASECASE_THRESHOLD             0  /* always */
#define MULLO_DC_THRESHOLD                  56
#define MULLO_MUL_N_THRESHOLD             8648
#define SQRLO_BASECASE_THRESHOLD             2
#define SQRLO_DC_THRESHOLD                 106
#define SQRLO_SQR_THRESHOLD               6293

#define DC_DIV_QR_THRESHOLD                 28
#define DC_DIVAPPR_Q_THRESHOLD             102
#define DC_BDIV_QR_THRESHOLD                51
#define DC_BDIV_Q_THRESHOLD                124

#define INV_MULMOD_BNM1_THRESHOLD           34
#define INV_NEWTON_THRESHOLD               123
#define INV_APPR_THRESHOLD                 109

#define BINV_NEWTON_THRESHOLD              206
#define REDC_1_TO_REDC_N_THRESHOLD          51

#define MU_DIV_QR_THRESHOLD                807
#define MU_DIVAPPR_Q_THRESHOLD             807
#define MUPI_DIV_QR_THRESHOLD               53
#define MU_BDIV_QR_THRESHOLD               748
#define MU_BDIV_Q_THRESHOLD                872

#define POWM_SEC_TABLE  2,23,66,440,1555

#define GET_STR_DC_THRESHOLD                 7
#define GET_STR_PRECOMPUTE_THRESHOLD        17
#define SET_STR_DC_THRESHOLD              1035
#define SET_STR_PRECOMPUTE_THRESHOLD      2170

#define FAC_DSC_THRESHOLD                  542
#define FAC_ODD_THRESHOLD                   24

#define MATRIX22_STRASSEN_THRESHOLD         10
#define HGCD_THRESHOLD                     108
#define HGCD_APPR_THRESHOLD                116
#define HGCD_REDUCE_THRESHOLD             1437
#define GCD_DC_THRESHOLD                   268
#define GCDEXT_DC_THRESHOLD                241
#define JACOBI_BASE_METHOD                   4
