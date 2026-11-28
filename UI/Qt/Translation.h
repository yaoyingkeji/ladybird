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

// Translates a user interface string to the active UI language. Falls back to the original English string when
// no translation is available. The active language comes from the in-app setting, then LADYBIRD_LANGUAGE, then
// the system locale.
QString localize(AK::StringView text);
QString localize(char const* text);

// Normalized language code of the active UI language ("en" or "zh-CN"). Built-in WebUI pages use it as well.
QString ui_language_code();

// Changes the UI language at runtime and sends QEvent::LanguageChange to the application. An empty code restores
// the "follow system" behaviour.
void set_ui_language(QString const& code);

// Whether a translation table is active. Useful for tests and for choosing language-dependent assets.
bool ui_translation_enabled();

// Widgets whose text was produced by localize() at construction time can retranslate themselves on a language
// switch by registering here. The callback runs after the new dictionary has been installed.
using LanguageChangeListener = void (*)(void*);
void add_language_change_listener(void* context, LanguageChangeListener callback);
void remove_language_change_listener(void* context, LanguageChangeListener callback);

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
