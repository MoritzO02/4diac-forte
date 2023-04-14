/*******************************************************************************
 * Copyright (c) 2023 Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Martin Erich Jobst - initial implementation
 *******************************************************************************/
#pragma once

#include <memory>
#include <variant>

#include "forte_any.h"
#include "forte_any_unique_ptr.h"
#include "forte_array_common.h"
#include "forte_bool.h"
#include "forte_byte.h"
#include "forte_char.h"
#include "forte_date.h"
#include "forte_date_and_time.h"
#include "forte_dint.h"
#include "forte_dword.h"
#include "forte_int.h"
#include "forte_ldate.h"
#include "forte_ldate_and_time.h"
#include "forte_lint.h"
#include "forte_lreal.h"
#include "forte_ltime.h"
#include "forte_ltime_of_day.h"
#include "forte_lword.h"
#include "forte_real.h"
#include "forte_sint.h"
#include "forte_string.h"
#include "forte_struct.h"
#include "forte_time.h"
#include "forte_time_of_day.h"
#include "forte_udint.h"
#include "forte_uint.h"
#include "forte_ulint.h"
#include "forte_usint.h"
#include "forte_wchar.h"
#include "forte_word.h"
#include "forte_wstring.h"

using TIecAnyVariantType = std::variant<
// ANY_ELEMENTARY
//  ANY_MAGNITUDE
//   ANY_NUM
//    ANY_INTEGER
//     ANY_SIGNED
        CIEC_SINT,
        CIEC_INT,
        CIEC_DINT,
        CIEC_LINT,
//     ANY_UNSINED
        CIEC_USINT,
        CIEC_UINT,
        CIEC_UDINT,
        CIEC_ULINT,
//    ANY_REAL
        CIEC_REAL,
        CIEC_LREAL,
//   ANY_DURATION
        CIEC_TIME,
        CIEC_LTIME,
//  ANY_BIT
        CIEC_BOOL,
        CIEC_BYTE,
        CIEC_WORD,
        CIEC_DWORD,
        CIEC_LWORD,
//  ANY_CHARS
//   ANY_CHAR
        CIEC_CHAR,
        CIEC_WCHAR,
//   ANY_STRING
        CIEC_STRING,
        CIEC_WSTRING,
//  ANY_DATE
        CIEC_DATE,
        CIEC_LDATE,
        CIEC_DATE_AND_TIME,
        CIEC_LDATE_AND_TIME,
        CIEC_TIME_OF_DAY,
        CIEC_LTIME_OF_DAY,
// ANY_DERIVED
        CIEC_ANY_UNIQUE_PTR<CIEC_ARRAY_COMMON<CIEC_ANY>>,
        CIEC_ANY_UNIQUE_PTR<CIEC_STRUCT>
// end
>;

class CIEC_ANY_VARIANT : public CIEC_ANY, public TIecAnyVariantType {
DECLARE_FIRMWARE_DATATYPE(ANY_VARIANT)
public:
    using TIecAnyVariantType::variant;
    using TIecAnyVariantType::operator=;
    template<class> static inline constexpr bool always_false_v = false;

    CIEC_ANY_VARIANT(const CIEC_ANY_VARIANT &paVal) : CIEC_ANY(), variant(paVal) {}

    CIEC_ANY_VARIANT &operator=(const CIEC_ANY_VARIANT &paOther) {
      variant::operator=(paOther);
      return *this;
    }

    void setValue(const CIEC_ANY &paValue) override;

    bool setDefaultValue(CIEC_ANY::EDataTypeID paDataTypeId);

    [[nodiscard]] CIEC_ANY &unwrap() override;

    [[nodiscard]] const CIEC_ANY &unwrap() const override;

    int fromString(const char *paValue) override;

    int toString(char* paValue, size_t paBufferSize) const override;

    size_t getToStringBufferSize() const override;

    [[nodiscard]] bool equals(const CIEC_ANY &paOther) const override {
      return unwrap().equals(paOther.unwrap());
    }
};

static_assert(std::is_copy_constructible_v<CIEC_ANY_VARIANT>);
static_assert(std::is_move_constructible_v<CIEC_ANY_VARIANT>);
static_assert(std::is_copy_assignable_v<CIEC_ANY_VARIANT>);
static_assert(std::is_destructible_v<CIEC_ANY_VARIANT>);

