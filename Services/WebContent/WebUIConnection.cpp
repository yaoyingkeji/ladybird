/*
 * Copyright (c) 2025, Tim Flynn <trflynn89@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/JsonObject.h>
#include <AK/NeverDestroyed.h>
#include <LibGC/Heap.h>
#include <LibJS/Runtime/PrimitiveString.h>
#include <LibWeb/Bindings/PlatformObject.h>
#include <LibWeb/Bindings/Wrappable.h>
#include <LibWeb/Bindings/WrapperWorld.h>
#include <LibWeb/DOM/CustomEvent.h>
#include <LibWeb/DOM/Document.h>
#include <LibWeb/DOM/Event.h>
#include <LibWeb/HTML/Scripting/Environments.h>
#include <LibWeb/HTML/Scripting/TemporaryExecutionContext.h>
#include <LibWeb/HTML/Window.h>
#include <LibWeb/Internals/WebUI.h>
#include <LibWeb/WebDriver/JSON.h>
#include <WebContent/WebUIConnection.h>

namespace WebContent {

static JS::PropertyKey const& ladybird_property()
{
    static NeverDestroyed<JS::PropertyKey> property { "ladybird"_utf16_fly_string };
    return *property;
}

static Utf16FlyString const& web_ui_loaded_event()
{
    static NeverDestroyed<Utf16FlyString> event { "WebUILoaded"_utf16_fly_string };
    return *event;
}

static Utf16FlyString const& web_ui_message_event()
{
    static NeverDestroyed<Utf16FlyString> event { "WebUIMessage"_utf16_fly_string };
    return *event;
}

static JS::PropertyKey const& ui_language_property()
{
    static NeverDestroyed<JS::PropertyKey> property { "__ladybirdLanguage"_utf16_fly_string };
    return *property;
}

ErrorOr<NonnullRefPtr<WebUIConnection>> WebUIConnection::connect(IPC::TransportHandle handle, Web::DOM::Document& document, String const& ui_language)
{
    auto transport = TRY(handle.create_transport());
    return adopt_ref(*new WebUIConnection(move(transport), document, ui_language));
}

WebUIConnection::WebUIConnection(NonnullOwnPtr<IPC::Transport> transport, Web::DOM::Document& document, String const& ui_language)
    : IPC::ConnectionFromClient<WebUIClientEndpoint, WebUIServerEndpoint>(*this, move(transport), 1)
    , m_document(document)
{
    auto& realm = m_document->relevant_settings_object().realm();
    auto& window = Web::HTML::relevant_window(realm.global_object());
    realm.global_object().define_direct_property(ladybird_property(), Web::Bindings::wrap(Web::Bindings::host_defined_wrapper_world(realm), realm, Web::Internals::WebUI::create(window)), JS::default_attributes);

    if (!ui_language.is_empty()) {
        realm.global_object().define_direct_property(
            ui_language_property(),
            JS::PrimitiveString::create(realm.vm(), Utf16String::from_utf8(ui_language)),
            JS::default_attributes);
    }

    Web::HTML::queue_a_task(Web::HTML::Task::Source::Unspecified, nullptr, m_document, GC::create_function(GC::Heap::the(), GC::captures(*m_document), [](auto& document) {
        document.dispatch_event(Web::DOM::Event::create(Web::HTML::relevant_global_object(document), web_ui_loaded_event()));
    }));
}

WebUIConnection::~WebUIConnection()
{
    if (!m_document->window())
        return;

    auto& global_object = m_document->relevant_settings_object().realm().global_object();
    (void)global_object.internal_delete(ladybird_property());
    (void)global_object.internal_delete(ui_language_property());
}

void WebUIConnection::visit_edges(JS::Cell::Visitor& visitor)
{
    visitor.visit(m_document);
}

void WebUIConnection::send_message(String name, JsonValue data)
{
    if (!m_document->browsing_context())
        return;

    JsonObject detail;
    detail.set("name"sv, move(name));
    detail.set("data"sv, move(data));

    auto& realm = m_document->relevant_settings_object().realm();
    Web::HTML::TemporaryExecutionContext context { realm };

    auto serialized_detail = Web::WebDriver::json_deserialize(*m_document->browsing_context(), detail);
    if (serialized_detail.is_error()) {
        warnln("Unable to serialize JSON data from browser: {}", serialized_detail.error());
        return;
    }

    m_document->dispatch_event(Web::DOM::create_custom_event(realm, web_ui_message_event(), serialized_detail.value()));
}

void WebUIConnection::set_ui_language(String const& code)
{
    send_message("loadUILanguage"_string, JsonValue(code));
}

void WebUIConnection::received_message_from_web_ui(Utf16String const& name, JS::Value data)
{
    if (!m_document->browsing_context())
        return;

    auto deserialized_data = Web::WebDriver::json_clone(*m_document->browsing_context(), data);
    if (deserialized_data.is_error()) {
        warnln("Unable to deserialize JS data from WebUI: {}", deserialized_data.error());
        return;
    }

    async_received_message(name.to_utf8(), deserialized_data.value());
}

}
