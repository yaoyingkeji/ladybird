/*
 * Copyright (c) 2026, LadybirdBrowser/ladybird contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/StringView.h>
#include <QString>

namespace Ladybird {

// Translates a user interface string to the language selected by LADYBIRD_LANGUAGE or the system locale.
// Falls back to the original string when no translation is available.
QString localize(AK::StringView text);
QString localize(char const* text);

// Whether a translation table is active. Useful for tests and for choosing language-dependent assets.
bool ui_translation_enabled();

}
