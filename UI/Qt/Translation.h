/*
 * Copyright (c) 2026, LadybirdBrowser/ladybird contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/StringView.h>
#include <QString>
#include <QTranslator>

namespace Ladybird {

// Translates a user interface string to the language selected by LADYBIRD_LANGUAGE or the system locale.
// Falls back to the original string when no translation is available.
QString localize(AK::StringView text);
QString localize(char const* text);

// Whether a translation table is active. Useful for tests and for choosing language-dependent assets.
bool ui_translation_enabled();

// Routes Qt's tr() lookups through the same dictionary, so widgets that use tr() are translated without touching
// their call sites. Install one instance on the application object.
class DictionaryTranslator final : public QTranslator {
public:
    explicit DictionaryTranslator(QObject* parent = nullptr);
    ~DictionaryTranslator() override = default;

    QString translate(char const* context, char const* source_text, char const* disambiguation = nullptr, int n = -1) const override;
    bool isEmpty() const override;
};

}
