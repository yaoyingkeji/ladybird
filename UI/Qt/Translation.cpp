/*
 * Copyright (c) 2026, LadybirdBrowser/ladybird contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/Pair.h>
#include <AK/StringView.h>
#include <AK/Vector.h>
#include <UI/Qt/StringUtils.h>
#include <UI/Qt/Translation.h>

#include <QApplication>
#include <QByteArray>
#include <QEvent>
#include <QHash>
#include <QLocale>
#include <QString>
#include <QtGlobal>

#include <cstring>
#include <iterator>

namespace Ladybird {

namespace {

struct Translation {
    char const* english;
    char const* simplified_chinese;
};

// Menu and action strings. Strings that are not listed here fall back to English, which keeps this table safe to
// extend without having to touch the call sites.
static constexpr Translation s_simplified_chinese_translations[] = {
    { "%1 (Private)", "%1（隐私）" },
    { "%1 embedded frames", "%1 个嵌入框架" },
    { "%1 frames", "%1 个框架" },
    { "%1 frames, %2 sandboxed", "%1 个框架，其中 %2 个为沙箱" },
    { "%1 h %2 min", "%1 小时 %2 分钟" },
    { "%1 min", "%1 分钟" },
    { "%1 of %2", "第 %1 项，共 %2 项" },
    { "%1 processes", "%1 个进程" },
    { "%1 sandboxed frames", "%1 个沙箱框架" },
    { "%1 sites", "%1 个网站" },
    { "%1 tabs", "%1 个标签页" },
    { "%1 wants to %2", "%1 想要%2" },
    { "&Close Tab", "关闭标签页(&C)" },
    { "&Debug", "调试(&D)" },
    { "&Duplicate Tab", "复制标签页(&D)" },
    { "&Edit", "编辑(&E)" },
    { "&File", "文件(&F)" },
    { "&Inspect", "检查(&I)" },
    { "&Mute Tab", "静音标签页(&M)" },
    { "&Pin Tab", "固定标签页(&P)" },
    { "&Translation", "翻译(&T)" },
    { "&View", "视图(&V)" },
    { "&Zoom", "缩放(&Z)" },
    { "(Empty)", "（空）" },
    { "1 embedded frame", "1 个嵌入框架" },
    { "1 frame", "1 个框架" },
    { "1 process", "1 个进程" },
    { "1 sandboxed frame", "1 个沙箱框架" },
    { "1 site", "1 个网站" },
    { "1 tab", "1 个标签页" },
    { "100%", "100%" },
    { "A few words about what you were doing can help us reproduce it.", "简单描述你当时在做什么，有助于我们重现问题。" },
    { "About Ladybird", "关于 Ladybird" },
    { "Actual size", "实际大小" },
    { "Actual size. Drag to look around, click to see all of it.", "实际大小。拖动可查看四周，单击可查看全部。" },
    { "Add Bookmark", "添加书签" },
    { "Add Bookmark…", "添加书签…" },
    { "Add bookmark", "添加书签" },
    { "Add folder", "添加文件夹" },
    { "All Resolved Styles", "所有已解析样式" },
    { "All site settings", "所有网站设置" },
    { "All tabs", "所有标签页" },
    { "Allow", "允许" },
    { "Allow this time", "仅允许这一次" },
    { "Allow while visiting the site", "访问此网站时允许" },
    { "Along the &Top", "位于顶部(&T)" },
    { "Also sends the address and your browser setup.", "同时发送地址和你的浏览器配置。" },
    { "Always", "总是" },
    { "Always on T&op", "始终位于顶部(&O)" },
    { "Ask", "询问" },
    { "Auto", "自动" },
    { "Autoplay", "自动播放" },
    { "Back", "后退" },
    { "Back to site settings", "返回网站设置" },
    { "Back to the site", "返回网站" },
    { "Block", "阻止" },
    { "Block Pop-ups", "阻止弹出窗口" },
    { "Block audio", "阻止音频" },
    { "Blocked on this page", "此页面已拦截的内容" },
    { "Bookmark", "书签" },
    { "Bookmark All Tabs…", "为所有标签页添加书签…" },
    { "Bookmark added", "已添加书签" },
    { "Bookmark this page", "为此页面添加书签" },
    { "Bookmark · %1", "书签 · %1" },
    { "Bookmarks", "书签" },
    { "Bookmarks bar", "书签栏" },
    { "CSS Errors", "CSS 错误" },
    { "Can unload", "可卸载" },
    { "Cancel", "取消" },
    { "Capture Full Page", "截取整个页面" },
    { "Capture Visible Page", "截取可见区域" },
    { "Check for Updates…", "检查更新…" },
    { "Chrome", "Chrome" },
    { "Cl&ose Other Tabs", "关闭其他标签页(&O)" },
    { "Clear Browsing Data", "清除浏览数据" },
    { "Clear finished", "清除已完成" },
    { "Click to see it in actual size.", "单击以实际大小查看。" },
    { "Close Ladybird", "关闭 Ladybird" },
    { "Close Tab", "关闭标签页" },
    { "Close Tabs B&elow", "关闭下方标签页(&E)" },
    { "Close Tabs to the R&ight", "关闭右侧标签页(&I)" },
    { "Close find", "关闭查找" },
    { "Close tab", "关闭标签页" },
    { "Collect Garbage", "回收垃圾" },
    { "Color Scheme", "配色方案" },
    { "Compositor Layers", "合成器图层" },
    { "Connection is not secure", "连接不安全" },
    { "Content blocking", "内容拦截" },
    { "Content blocking on this site", "对此网站启用内容拦截" },
    { "Context menu", "上下文菜单" },
    { "Continue Without Screenshot", "不截图并继续" },
    { "Contrast", "对比度" },
    { "Cookies", "Cookie" },
    { "Copy", "复制" },
    { "Copy &Link", "复制链接(&L)" },
    { "Copy Audio Address", "复制音频地址" },
    { "Copy Email Address", "复制电子邮件地址" },
    { "Copy Image", "复制图片" },
    { "Copy Image Address", "复制图片地址" },
    { "Copy Link", "复制链接" },
    { "Copy Link to Highlight", "复制指向高亮的链接" },
    { "Copy PID", "复制 PID" },
    { "Copy Phone Number", "复制电话号码" },
    { "Copy Video Address", "复制视频地址" },
    { "Couldn’t send report", "无法发送报告" },
    { "Crash Compositor Process", "使合成器进程崩溃" },
    { "Crash Current Page", "使当前页面崩溃" },
    { "Cut", "剪切" },
    { "DOM Tree", "DOM 树" },
    { "Dark", "深色" },
    { "Debug", "调试" },
    { "Default", "默认" },
    { "Default (%1)", "默认（%1）" },
    { "Default ({})", "默认（{}）" },
    { "Delete", "删除" },
    { "Delete Folder", "删除文件夹" },
    { "DevTools are open for it", "已打开开发者工具" },
    { "DevTools is enabled on port %1", "开发者工具已在端口 %1 上启用" },
    { "DevTools is enabled on port {}", "开发者工具已在端口 {} 上启用" },
    { "Disable", "禁用" },
    { "Disable DevTools", "禁用开发者工具" },
    { "Disabled", "已禁用" },
    { "Dismiss", "忽略" },
    { "Display List", "显示列表" },
    { "Done", "完成" },
    { "Don’t send", "不发送" },
    { "Down the &Left Side", "位于左侧(&L)" },
    { "Down the &Right Side", "位于右侧(&R)" },
    { "Download", "下载" },
    { "Download Linked File", "下载链接文件" },
    { "Downloads", "下载" },
    { "Downloads are still in progress.", "下载仍在进行中。" },
    { "Drag to select the part of the page that shows the problem.", "拖动选择页面中出现问题的部分。" },
    { "Drag to select the part of the page to save.", "拖动选择要保存的页面部分。" },
    { "Dump", "转储" },
    { "Edit Folder…", "编辑文件夹…" },
    { "Edit bookmark", "编辑书签" },
    { "Edit folder", "编辑文件夹" },
    { "Edit…", "编辑…" },
    { "Enable DevTools", "启用开发者工具" },
    { "Enable Scripting", "启用脚本" },
    { "End %1 processes", "结束 %1 个进程" },
    { "End Process", "结束进程" },
    { "Exit Full Screen", "退出全屏" },
    { "Exit Picture in Picture", "退出画中画" },
    { "Exit full screen", "退出全屏" },
    { "Files on this computer have no site settings.", "此计算机上的文件没有网站设置。" },
    { "Filter lists", "过滤列表" },
    { "Find &Next", "查找下一个(&N)" },
    { "Find Pre&vious", "查找上一个(&V)" },
    { "Find in page", "在页面中查找" },
    { "Folder", "文件夹" },
    { "Folder:", "文件夹：" },
    { "Force Dark Mode", "强制深色模式" },
    { "Force dark mode", "强制深色模式" },
    { "Force dark mode on this site", "对此网站强制深色模式" },
    { "Forward", "前进" },
    { "Full Screen", "全屏" },
    { "Full screen", "全屏" },
    { "GC Graph", "GC 图表" },
    { "Gecko", "Gecko" },
    { "Help", "帮助" },
    { "Helps us fix graphics and video bugs. It names your graphics card, its driver and your media libraries.", "帮助修复图形和视频问题。会记录显卡、驱动和媒体库信息。" },
    { "Helps us fix rendering bugs. It can contain text from the page.", "帮助修复渲染问题。可能包含页面中的文本。" },
    { "Hide Controls", "隐藏控件" },
    { "Hide Sidebar", "隐藏侧边栏" },
    { "History", "历史记录" },
    { "Ignore Spelling", "忽略拼写" },
    { "Include graphics and video information", "包含图形和视频信息" },
    { "Include layout and painting information", "包含布局和绘制信息" },
    { "Include this website URL in the report", "在报告中包含此网站 URL" },
    { "Includes technical crash details, your Ladybird version and platform.", "包含技术崩溃详情、Ladybird 版本和平台。" },
    { "Inspect", "检查" },
    { "Inspect Element", "检查元素" },
    { "It can still be unloaded when the system is about to run out of memory.", "系统即将内存不足时仍可卸载。" },
    { "It changed its icon while hidden", "隐藏时更改了图标" },
    { "It changed its title while hidden", "隐藏时更改了标题" },
    { "It crashed", "已崩溃" },
    { "It has a Picture-in-Picture window", "有画中画窗口" },
    { "It isn't a tab", "不是标签页" },
    { "It played sound in the last minute", "最近一分钟内播放过声音" },
    { "It's downloading a file", "正在下载文件" },
    { "It's loading", "正在加载" },
    { "It's pinned", "已固定" },
    { "It's playing sound", "正在播放声音" },
    { "It's the current tab of its window", "是其窗口的当前标签页" },
    { "It's using the microphone", "正在使用麦克风" },
    { "It's using your location", "正在使用你的位置" },
    { "It's visible", "可见" },
    { "It's waiting for you to answer a permission request", "正在等待你回应权限请求" },
    { "Its window doesn't keep its history", "其窗口不保留历史记录" },
    { "Ladybird can't %1", "Ladybird 无法%1" },
    { "Ladybird is already running, but it is not responding.", "Ladybird 已在运行，但没有响应。" },
    { "Ladybird pages have no site settings.", "Ladybird 页面没有网站设置。" },
    { "Layout Tree", "布局树" },
    { "Learn Spelling", "学习拼写" },
    { "Less", "缩小" },
    { "Light", "浅色" },
    { "Local Storage", "本地存储" },
    { "Look Up", "查询" },
    { "Loop", "循环" },
    { "Manage Bookmarks", "管理书签" },
    { "Match case", "区分大小写" },
    { "More", "更多" },
    { "Motion", "动效" },
    { "Move to New &Window", "移动到新窗口(&W)" },
    { "Mute", "静音" },
    { "Name", "名称" },
    { "Navigator Compatibility Mode", "Navigator 兼容模式" },
    { "Never allow", "永不允许" },
    { "New Folder…", "新建文件夹…" },
    { "New Private Window", "新建隐私窗口" },
    { "New Tab", "新建标签页" },
    { "New Tab &Below", "在下方新建标签页(&B)" },
    { "New Tab to the &Right", "在右侧新建标签页(&R)" },
    { "New Window", "新建窗口" },
    { "Next match", "下一个匹配项" },
    { "No", "否" },
    { "No Guesses Found", "未找到拼写建议" },
    { "No Preference", "无偏好" },
    { "No downloads", "暂无下载" },
    { "No matches", "无匹配项" },
    { "Not now", "暂不" },
    { "Not secure", "不安全" },
    { "Nothing has been blocked on this page.", "此页面没有拦截任何内容。" },
    { "Only when the system is about to run out of memory", "仅当系统即将内存不足时" },
    { "Open All in Tabs", "在标签页中全部打开" },
    { "Open Image", "打开图片" },
    { "Open Link in New Window", "在新窗口中打开链接" },
    { "Open Link in Private Window", "在隐私窗口中打开链接" },
    { "Open Settings", "打开系统设置" },
    { "Open Task Manager", "打开任务管理器" },
    { "Open client", "打开客户端" },
    { "Open in New Tab", "在新标签页中打开" },
    { "Open in New Window", "在新窗口中打开" },
    { "Open in Private Window", "在隐私窗口中打开" },
    { "Paste", "粘贴" },
    { "Paste and Match Style", "粘贴并匹配样式" },
    { "Pause", "暂停" },
    { "Permission request", "权限请求" },
    { "Picture in Picture", "画中画" },
    { "Picture-in-Picture", "画中画" },
    { "Play", "播放" },
    { "Preferred Languages…", "首选语言…" },
    { "Preparing report…", "正在准备报告…" },
    { "Previous match", "上一个匹配项" },
    { "Processes", "进程" },
    { "Recently closed", "最近关闭" },
    { "Redo", "重做" },
    { "Reduce", "缩小" },
    { "Reload", "重新加载" },
    { "Reload Without Cache", "强制重新加载" },
    { "Reload page", "重新加载页面" },
    { "Report Leaked Documents", "报告泄露的文档" },
    { "Report Website Issue", "报告网站问题" },
    { "Report Website Issue…", "报告网站问题…" },
    { "Report a website issue", "报告网站问题" },
    { "Report already on its way", "报告已在发送中" },
    { "Report details", "报告详情" },
    { "Report not sent", "报告未发送" },
    { "Report sent", "报告已发送" },
    { "Reset", "重置" },
    { "Reset Zoom", "重置缩放" },
    { "Reset permissions", "重置权限" },
    { "Retake", "重新截取" },
    { "Sandboxed", "沙箱" },
    { "Sandboxed frames run apart from the other documents of their site.", "沙箱框架与该网站的其他文档隔离运行。" },
    { "Save Image As…", "图片另存为…" },
    { "Save Link As…", "链接另存为…" },
    { "Screenshot", "屏幕截图" },
    { "Search or enter address", "搜索或输入网址" },
    { "Search processes", "搜索进程" },
    { "See everything", "查看全部" },
    { "Select All", "全选" },
    { "Selected area", "选定区域" },
    { "Send report", "发送报告" },
    { "Sending crash report", "正在发送崩溃报告" },
    { "Sending crash report…", "正在发送崩溃报告…" },
    { "Sending report", "正在发送报告" },
    { "Sending report…", "正在发送报告…" },
    { "Session History Tree", "会话历史树" },
    { "Session Storage", "会话存储" },
    { "Settings", "设置" },
    { "Show Bookmarks Bar", "显示书签栏" },
    { "Show Caret Hit Test Debug Overlay", "显示光标命中测试调试覆盖层" },
    { "Show Compositor Layers and Tiles", "显示合成器图层与瓦片" },
    { "Show Controls", "显示控件" },
    { "Show Line Box Borders", "显示行盒边框" },
    { "Show Menu Bar", "显示菜单栏" },
    { "Show Original", "显示原文" },
    { "Show Sidebar", "显示侧边栏" },
    { "Show Tab Performance Monitor", "显示标签页性能监视器" },
    { "Show all downloads", "显示所有下载" },
    { "Site Isolation Process Tree", "站点隔离进程树" },
    { "Site settings", "网站设置" },
    { "Sites", "网站" },
    { "Some", "部分" },
    { "Spare", "备用" },
    { "Spoof User Agent", "伪造 User Agent" },
    { "Stacking Context Tree", "层叠上下文树" },
    { "Stays loaded:", "保持加载：" },
    { "Style Sheets", "样式表" },
    { "Tab &Layout", "标签页布局(&L)" },
    { "Take Screenshot...", "截取屏幕截图..." },
    { "Take Screenshot…", "截取屏幕截图…" },
    { "Task Manager", "任务管理器" },
    { "The connection to this site is not secure", "与此网站的连接不安全" },
    { "The site may show notifications", "网站可能显示通知" },
    { "This file", "此文件" },
    { "This page", "此页面" },
    { "This page is using your location", "此页面正在使用你的位置" },
    { "This page is using your microphone", "此页面正在使用你的麦克风" },
    { "Title:", "标题：" },
    { "Toggle Bookmark", "切换书签" },
    { "Translate", "翻译" },
    { "Translation", "翻译" },
    { "Try sending again", "重试发送" },
    { "URL:", "网址：" },
    { "Un&mute Tab", "取消静音(&M)" },
    { "Undo", "撤销" },
    { "Unloads in %1 if it stays hidden", "若保持隐藏，将在 %1 后卸载" },
    { "Unmute", "取消静音" },
    { "Untitled", "无标题" },
    { "Use Higher-Quality Models", "使用更高质量的模型" },
    { "Using your location", "正在使用你的位置" },
    { "Using your microphone", "正在使用你的麦克风" },
    { "View History", "查看历史记录" },
    { "View Page Source", "查看页面源代码" },
    { "WebKit", "WebKit" },
    { "Yes", "是" },
    { "You typed into the page", "你在页面中输入过内容" },
    { "Your system will then ask you to let Ladybird %1.", "随后系统会询问是否允许 Ladybird %1。" },
    { "Your system's privacy settings don't let Ladybird %1.", "你的系统隐私设置不允许 Ladybird %1。" },
    { "Zoom", "缩放" },
    { "Zoom In", "放大" },
    { "Zoom Out", "缩小" },
    { "know your location", "获取你的位置" },
    { "less than a minute", "不到一分钟" },
    { "send you notifications", "向你发送通知" },
    { "use your microphone", "使用你的麦克风" },
};

QHash<QByteArray, QString> s_dictionary;
bool s_initialized { false };
bool s_enabled { false };
QString s_language_code { "en" };
QString s_language_override;
Vector<Pair<void*, LanguageChangeListener>> s_language_change_listeners;

// New language packs can be added here without touching any call site: add a translation table above and a mapping
// below. Unsupported languages intentionally fall back to the original English source strings.
QString normalize_language_code(QString const& language)
{
    auto code = language.toLower().replace('_', '-');
    if (code.isEmpty() || code == "system" || code == "auto")
        return QLocale::system().name().toLower().replace('_', '-');
    return code;
}

QString resolve_language_code()
{
    auto language = s_language_override.isEmpty() ? QString::fromUtf8(qEnvironmentVariable("LADYBIRD_LANGUAGE")) : s_language_override;
    if (language.isEmpty())
        language = QLocale::system().name();

    auto code = normalize_language_code(language);
    if (code.startsWith("zh"))
        return "zh-CN";
    return "en";
}

void rebuild_dictionary()
{
    s_dictionary.clear();
    s_language_code = resolve_language_code();
    s_enabled = s_language_code == "zh-CN";
    if (!s_enabled)
        return;

    s_dictionary.reserve(static_cast<int>(std::size(s_simplified_chinese_translations)));
    for (auto const& translation : s_simplified_chinese_translations)
        s_dictionary.insert(QByteArray { translation.english }, QString::fromUtf8(translation.simplified_chinese));
}

void initialize()
{
    s_initialized = true;
    rebuild_dictionary();
}

}

QString ui_language_code()
{
    if (!s_initialized)
        initialize();
    return s_language_code;
}

void set_ui_language(QString const& code)
{
    if (!s_initialized)
        initialize();

    auto raw = code.trimmed().toLower();
    auto follows_system = raw.isEmpty() || raw == "system" || raw == "auto";
    auto normalized = follows_system ? QString {} : normalize_language_code(code);
    s_language_override = normalized;
    auto resolved = follows_system ? resolve_language_code() : (normalized.startsWith("zh") ? QString { "zh-CN" } : QString { "en" });
    if (resolved == s_language_code)
        return;

    rebuild_dictionary();

    for (auto const& [context, callback] : s_language_change_listeners)
        callback(context);

    // Let Qt widgets that implement changeEvent() retranslate their tr() strings immediately.
    QEvent event(QEvent::LanguageChange);
    QCoreApplication::sendEvent(qApp, &event);
    for (auto* widget : QApplication::topLevelWidgets())
        QCoreApplication::sendEvent(widget, &event);
}

bool ui_translation_enabled()
{
    if (!s_initialized)
        initialize();
    return s_enabled;
}

void add_language_change_listener(void* context, LanguageChangeListener callback)
{
    s_language_change_listeners.append({ context, callback });
}

void remove_language_change_listener(void* context, LanguageChangeListener callback)
{
    s_language_change_listeners.remove_first_matching([&](auto const& listener) {
        return listener.first == context && listener.second == callback;
    });
}

QString localize(AK::StringView text)
{
    if (!s_initialized)
        initialize();

    if (s_enabled && !text.is_empty()) {
        auto key = QByteArray { text.characters_without_null_termination(), static_cast<qsizetype>(text.length()) };
        if (auto it = s_dictionary.constFind(key); it != s_dictionary.constEnd())
            return *it;
    }

    return qstring_from_ak_string(text);
}

QString localize(char const* text)
{
    return localize(AK::StringView { text, std::strlen(text) });
}

DictionaryTranslator::DictionaryTranslator(QObject* parent)
    : QTranslator(parent)
{
}

QString DictionaryTranslator::translate(char const*, char const* source_text, char const*, int) const
{
    if (!source_text)
        return {};
    return localize(AK::StringView { source_text, std::strlen(source_text) });
}

bool DictionaryTranslator::isEmpty() const
{
    return !ui_translation_enabled();
}

}
