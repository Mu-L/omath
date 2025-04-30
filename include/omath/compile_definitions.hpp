//
// Created by Vlad on 4/30/2025.
//

#pragma once

#if defined(OMATH_USE_CONSTEXPR)
#define OMATH_CONSTEXPR constexpr
#define OMATH_STATIC_ASSERT(condition, msg)  static_assert((condition), msg)
#else
#define OMATH_CONSTEXPR
#define OMATH_STATIC_ASSERT(condition, msg)
#endif

#ifdef _MSC_VER
#define OMATH_NOINLINE __declspec(noinline)
#else
#define OMATH_NOINLINE __attribute__((noinline))
#endif

#if defined(OMATH_USE_SECURE_ENGINE)
#include <CodeVirtualizer/VirtualizerSDK.h>
#define OMATH_SE_COMPATIBLE OMATH_NOINLINE
#define OMATH_SE_PLACE_MACROS(macros) macros
#else
#define OMATH_SE_COMPATIBLE OMATH_NOINLINE
#define OMATH_SE_PLACE_MACROS(macros)
#endif
