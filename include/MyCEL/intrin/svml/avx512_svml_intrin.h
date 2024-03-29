#include "../svml_prolog.h"

#define _mm512_mask_load_epu32  _mm512_mask_load_epi32
#define _mm512_mask_store_epu32 _mm512_mask_store_epi32

__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_div_epi8(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_i8div64 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_div_epi16(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_i16div32 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_div_epi32(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_i32div16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_div_epi64(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_i64div8 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_div_epu8(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_u8div64 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_div_epu16(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_u16div32 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_div_epu32(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_u32div16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_div_epu64(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_u64div8 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_div_epi32(__m512i param0, __mmask16 param1, __m512i param2, __m512i param3)
{
    register __m512i reg0 asm("zmm0");
    reg0 = _mm512_mask_load_epi32(param0, param1, &param2);
    register __m512i reg1 asm("zmm1");
    reg1 = _mm512_mask_load_epi32(param0, param1, &param3);
    asm(
        "call __vdecl_i32div16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_epi32(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_div_epu32(__m512i param0, __mmask16 param1, __m512i param2, __m512i param3)
{
    register __m512i reg0 asm("zmm0");
    reg0 = _mm512_mask_load_epu32(param0, param1, &param2);
    register __m512i reg1 asm("zmm1");
    reg1 = _mm512_mask_load_epu32(param0, param1, &param3);
    asm(
        "call __vdecl_u32div16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_epu32(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_rem_epi8(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_i8rem64 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_rem_epi16(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_i16rem32 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_rem_epi32(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_i32rem16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_rem_epi64(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_i64rem8 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_rem_epu8(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_u8rem64 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_rem_epu16(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_u16rem32 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_rem_epu32(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_u32rem16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_rem_epu64(__m512i param0, __m512i param1)
{
    register __m512i reg0 asm("zmm0") = param0;
    register __m512i reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_u64rem8 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_rem_epi32(__m512i param0, __mmask16 param1, __m512i param2, __m512i param3)
{
    register __m512i reg0 asm("zmm0");
    reg0 = _mm512_mask_load_epi32(param0, param1, &param2);
    register __m512i reg1 asm("zmm1");
    reg1 = _mm512_mask_load_epi32(param0, param1, &param3);
    asm(
        "call __vdecl_i32rem16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_epi32(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512i __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_rem_epu32(__m512i param0, __mmask16 param1, __m512i param2, __m512i param3)
{
    register __m512i reg0 asm("zmm0");
    reg0 = _mm512_mask_load_epu32(param0, param1, &param2);
    register __m512i reg1 asm("zmm1");
    reg1 = _mm512_mask_load_epu32(param0, param1, &param3);
    asm(
        "call __vdecl_u32rem16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_epu32(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_sin_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_sinf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_sin_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_sinf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_sin_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_sin8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_sin_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_sin8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_cos_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_cosf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_cos_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_cosf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_cos_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_cos8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_cos_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_cos8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_sincos_ps(__m512* param0, __m512 param1)
{
    register __m512 reg0 asm("zmm0") = param1;
    register __m512 reg1 asm("zmm1");
    asm(
        "call __vdecl_sincosf16 \t\n"
        : "=v" (reg0), "=v" (reg1)
        : "0" (reg0)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    *param0 = reg1;
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_sincos_ps(__m512* param0, __m512 param1, __m512 param2, __mmask16 param3, __m512 param4)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param2, param3, &param4);
    register __m512 reg1 asm("zmm1");
    asm(
        "call __vdecl_sincosf16 \t\n"
        : "=v" (reg0), "=v" (reg1)
        : "0" (reg0)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    *param0 = param2;
    _mm512_mask_store_ps(param0, param3, reg1);
    param4 = param1;
    _mm512_mask_store_ps(&param4, param3, reg0);
    return param4;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_sincos_pd(__m512d* param0, __m512d param1)
{
    register __m512d reg0 asm("zmm0") = param1;
    register __m512d reg1 asm("zmm1");
    asm(
        "call __vdecl_sincos8 \t\n"
        : "=v" (reg0), "=v" (reg1)
        : "0" (reg0)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    *param0 = reg1;
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_sincos_pd(__m512d* param0, __m512d param1, __m512d param2, __mmask8 param3, __m512d param4)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param2, param3, &param4);
    register __m512d reg1 asm("zmm1");
    asm(
        "call __vdecl_sincos8 \t\n"
        : "=v" (reg0), "=v" (reg1)
        : "0" (reg0)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    *param0 = param2;
    _mm512_mask_store_pd(param0, param3, reg1);
    param4 = param1;
    _mm512_mask_store_pd(&param4, param3, reg0);
    return param4;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_tan_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_tanf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_tan_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_tanf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_tan_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_tan8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_tan_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_tan8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_asin_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_asinf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_asin_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_asinf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_asin_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_asin8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_asin_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_asin8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_acos_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_acosf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_acos_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_acosf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_acos_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_acos8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_acos_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_acos8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_atan_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_atanf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_atan_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_atanf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_atan_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_atan8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_atan_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_atan8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_atan2_ps(__m512 param0, __m512 param1)
{
    register __m512 reg0 asm("zmm0") = param0;
    register __m512 reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_atan2f16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_atan2_ps(__m512 param0, __mmask16 param1, __m512 param2, __m512 param3)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    register __m512 reg1 asm("zmm1");
    reg1 = _mm512_mask_load_ps(param0, param1, &param3);
    asm(
        "call __vdecl_atan2f16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_atan2_pd(__m512d param0, __m512d param1)
{
    register __m512d reg0 asm("zmm0") = param0;
    register __m512d reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_atan28 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_atan2_pd(__m512d param0, __mmask8 param1, __m512d param2, __m512d param3)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    register __m512d reg1 asm("zmm1");
    reg1 = _mm512_mask_load_pd(param0, param1, &param3);
    asm(
        "call __vdecl_atan28 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_sind_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_sindf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_sind_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_sindf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_sind_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_sind8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_sind_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_sind8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_cosd_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_cosdf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_cosd_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_cosdf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_cosd_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_cosd8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_cosd_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_cosd8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_tand_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_tandf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_tand_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_tandf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_tand_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_tand8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_tand_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_tand8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_sinh_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_sinhf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_sinh_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_sinhf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_sinh_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_sinh8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_sinh_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_sinh8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_cosh_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_coshf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_cosh_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_coshf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_cosh_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_cosh8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_cosh_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_cosh8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_tanh_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_tanhf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_tanh_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_tanhf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_tanh_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_tanh8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_tanh_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_tanh8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_asinh_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_asinhf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_asinh_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_asinhf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_asinh_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_asinh8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_asinh_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_asinh8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_acosh_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_acoshf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_acosh_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_acoshf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_acosh_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_acosh8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_acosh_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_acosh8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_atanh_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_atanhf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_atanh_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_atanhf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_atanh_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_atanh8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_atanh_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_atanh8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_log_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_logf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_log_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_logf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_log_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_log8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_log_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_log8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_log1p_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_log1pf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_log1p_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_log1pf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_log1p_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_log1p8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_log1p_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_log1p8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_log10_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_log10f16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_log10_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_log10f16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_log10_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_log108 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_log10_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_log108 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_log2_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_log2f16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_log2_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_log2f16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_log2_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_log28 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_log2_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_log28 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_logb_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_logbf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_logb_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_logbf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_logb_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_logb8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_logb_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_logb8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_exp_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_expf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_exp_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_expf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_exp_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_exp8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_exp_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_exp8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_exp10_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_exp10f16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_exp10_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_exp10f16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_exp10_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_exp108 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_exp10_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_exp108 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_exp2_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_exp2f16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_exp2_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_exp2f16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_exp2_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_exp28 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_exp2_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_exp28 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_expm1_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_expm1f16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_expm1_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_expm1f16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_expm1_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_expm18 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_expm1_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_expm18 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_pow_ps(__m512 param0, __m512 param1)
{
    register __m512 reg0 asm("zmm0") = param0;
    register __m512 reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_powf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_pow_ps(__m512 param0, __mmask16 param1, __m512 param2, __m512 param3)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    register __m512 reg1 asm("zmm1");
    reg1 = _mm512_mask_load_ps(param0, param1, &param3);
    asm(
        "call __vdecl_powf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_pow_pd(__m512d param0, __m512d param1)
{
    register __m512d reg0 asm("zmm0") = param0;
    register __m512d reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_pow8 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_pow_pd(__m512d param0, __mmask8 param1, __m512d param2, __m512d param3)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    register __m512d reg1 asm("zmm1");
    reg1 = _mm512_mask_load_pd(param0, param1, &param3);
    asm(
        "call __vdecl_pow8 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_trunc_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_truncf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_trunc_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_truncf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_trunc_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_trunc8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_trunc_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_trunc8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}

__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_svml_round_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_roundf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_svml_round_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_roundf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_svml_round_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_round8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_svml_round_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_round8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_fmod_ps(__m512 param0, __m512 param1)
{
    register __m512 reg0 asm("zmm0") = param0;
    register __m512 reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_fmodf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_fmod_ps(__m512 param0, __mmask16 param1, __m512 param2, __m512 param3)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    register __m512 reg1 asm("zmm1");
    reg1 = _mm512_mask_load_ps(param0, param1, &param3);
    asm(
        "call __vdecl_fmodf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_fmod_pd(__m512d param0, __m512d param1)
{
    register __m512d reg0 asm("zmm0") = param0;
    register __m512d reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_fmod8 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_fmod_pd(__m512d param0, __mmask8 param1, __m512d param2, __m512d param3)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    register __m512d reg1 asm("zmm1");
    reg1 = _mm512_mask_load_pd(param0, param1, &param3);
    asm(
        "call __vdecl_fmod8 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_rint_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_rintf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_rint_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_rintf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_rint_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_rint8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_rint_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_rint8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_invsqrt_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_invsqrtf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_invsqrt_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_invsqrtf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_invsqrt_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_invsqrt8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_invsqrt_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_invsqrt8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_cbrt_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_cbrtf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_cbrt_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_cbrtf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_cbrt_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_cbrt8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_cbrt_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_cbrt8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_invcbrt_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_invcbrtf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_invcbrt_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_invcbrtf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_invcbrt_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_invcbrt8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_invcbrt_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_invcbrt8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_hypot_ps(__m512 param0, __m512 param1)
{
    register __m512 reg0 asm("zmm0") = param0;
    register __m512 reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_hypotf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_hypot_ps(__m512 param0, __mmask16 param1, __m512 param2, __m512 param3)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    register __m512 reg1 asm("zmm1");
    reg1 = _mm512_mask_load_ps(param0, param1, &param3);
    asm(
        "call __vdecl_hypotf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_hypot_pd(__m512d param0, __m512d param1)
{
    register __m512d reg0 asm("zmm0") = param0;
    register __m512d reg1 asm("zmm1") = param1;
    asm(
        "call __vdecl_hypot8 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_hypot_pd(__m512d param0, __mmask8 param1, __m512d param2, __m512d param3)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    register __m512d reg1 asm("zmm1");
    reg1 = _mm512_mask_load_pd(param0, param1, &param3);
    asm(
        "call __vdecl_hypot8 \t\n"
        : "=v" (reg0)
        : "0" (reg0), "v" (reg1)
        : "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_cdfnorm_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_cdfnormf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_cdfnorm_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_cdfnormf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_cdfnorm_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_cdfnorm8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_cdfnorm_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_cdfnorm8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_cdfnorminv_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_cdfnorminvf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_cdfnorminv_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_cdfnorminvf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_cdfnorminv_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_cdfnorminv8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_cdfnorminv_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_cdfnorminv8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_erf_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_erff16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_erf_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_erff16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_erf_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_erf8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_erf_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_erf8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_erfc_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_erfcf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_erfc_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_erfcf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_erfc_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_erfc8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_erfc_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_erfc8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_erfcinv_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_erfcinvf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_erfcinv_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_erfcinvf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_erfcinv_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_erfcinv8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_erfcinv_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_erfcinv8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_erfinv_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_erfinvf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_erfinv_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_erfinvf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_erfinv_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_erfinv8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_erfinv_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_erfinv8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_nearbyint_ps(__m512 param0)
{
    register __m512 reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_nearbyintf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512 __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_nearbyint_ps(__m512 param0, __mmask16 param1, __m512 param2)
{
    register __m512 reg0 asm("zmm0");
    reg0 = _mm512_mask_load_ps(param0, param1, &param2);
    asm(
        "call __vdecl_nearbyintf16 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_ps(&param2, param1, reg0);
    return param2;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_nearbyint_pd(__m512d param0)
{
    register __m512d reg0 asm("zmm0") = param0;
    asm(
        "call __vdecl_nearbyint8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    return reg0;
}


__SVML_INTRIN_PROLOG __m512d __DEFAULT_SVML_FN_ATTRS512
_mm512_mask_nearbyint_pd(__m512d param0, __mmask8 param1, __m512d param2)
{
    register __m512d reg0 asm("zmm0");
    reg0 = _mm512_mask_load_pd(param0, param1, &param2);
    asm(
        "call __vdecl_nearbyint8 \t\n"
        : "=v" (reg0)
        : "0" (reg0)
        : "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
    );
    param2 = param0;
    _mm512_mask_store_pd(&param2, param1, reg0);
    return param2;
}
