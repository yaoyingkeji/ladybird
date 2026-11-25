/*
 * Copyright (c) 2026, LadybirdBrowser/ladybird contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/StringView.h>
#include <UI/Qt/StringUtils.h>
#include <UI/Qt/Translation.h>

#include <QByteArray>
#include <QHash>
#include <QLocale>
#include <QString>
#include <QtGlobal>

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
    { "100%", "100%" },
    { "About Ladybird", "关于 Ladybird" },
    { "Add Bookmark…", "添加书签…" },
    { "All Resolved Styles", "所有已解析样式" },
    { "Auto", "自动" },
    { "Back", "后退" },
    { "Block Pop-ups", "阻止弹出窗口" },
    { "Bookmark All Tabs…", "为所有标签页添加书签…" },
    { "Bookmarks", "书签" },
    { "Chrome", "Chrome" },
    { "Clear Browsing Data", "清除浏览数据" },
    { "Collect Garbage", "回收垃圾" },
    { "Color Scheme", "配色方案" },
    { "Contrast", "对比度" },
    { "Cookies", "Cookie" },
    { "Copy", "复制" },
    { "Copy Image", "复制图片" },
    { "Copy Link", "复制链接" },
    { "Copy Link to Highlight", "复制指向高亮的链接" },
    { "Crash Compositor Process", "使合成器进程崩溃" },
    { "Crash Current Page", "使当前页面崩溃" },
    { "CSS Errors", "CSS 错误" },
    { "Cut", "剪切" },
    { "Dark", "深色" },
    { "Debug", "调试" },
    { "Delete", "删除" },
    { "Delete Folder", "删除文件夹" },
    { "Disable DevTools", "禁用开发者工具" },
    { "Disabled", "已禁用" },
    { "Display List", "显示列表" },
    { "DOM Tree", "DOM 树" },
    { "Download", "下载" },
    { "Download Linked File", "下载链接文件" },
    { "Downloads", "下载" },
    { "Dump", "转储" },
    { "Edit…", "编辑…" },
    { "Edit Folder…", "编辑文件夹…" },
    { "Enable DevTools", "启用开发者工具" },
    { "Enable Scripting", "启用脚本" },
    { "Exit Full Screen", "退出全屏" },
    { "Exit Picture in Picture", "退出画中画" },
    { "Force Dark Mode", "强制深色模式" },
    { "Forward", "前进" },
    { "Full Screen", "全屏" },
    { "GC Graph", "GC 图表" },
    { "Gecko", "Gecko" },
    { "Help", "帮助" },
    { "Hide Controls", "隐藏控件" },
    { "Hide Sidebar", "隐藏侧边栏" },
    { "History", "历史记录" },
    { "Ignore Spelling", "忽略拼写" },
    { "Inspect", "检查" },
    { "Inspect Element", "检查元素" },
    { "Layout Tree", "布局树" },
    { "Learn Spelling", "学习拼写" },
    { "Less", "缩小" },
    { "Light", "浅色" },
    { "Local Storage", "本地存储" },
    { "Look Up", "查询" },
    { "Loop", "循环" },
    { "Manage Bookmarks", "管理书签" },
    { "More", "更多" },
    { "Motion", "动效" },
    { "Mute", "静音" },
    { "Navigator Compatibility Mode", "Navigator 兼容模式" },
    { "New Folder…", "新建文件夹…" },
    { "New Private Window", "新建隐私窗口" },
    { "New Tab", "新建标签页" },
    { "New Window", "新建窗口" },
    { "No Guesses Found", "未找到拼写建议" },
    { "No Preference", "无偏好" },
    { "Open All in Tabs", "在标签页中全部打开" },
    { "Open Image", "打开图片" },
    { "Open in New Tab", "在新标签页中打开" },
    { "Open in New Window", "在新窗口中打开" },
    { "Open in Private Window", "在隐私窗口中打开" },
    { "Open Link in New Window", "在新窗口中打开链接" },
    { "Open Link in Private Window", "在隐私窗口中打开链接" },
    { "Open Task Manager", "打开任务管理器" },
    { "Paste", "粘贴" },
    { "Paste and Match Style", "粘贴并匹配样式" },
    { "Pause", "暂停" },
    { "Picture in Picture", "画中画" },
    { "Play", "播放" },
    { "Preferred Languages…", "首选语言…" },
    { "Redo", "重做" },
    { "Reduce", "缩小" },
    { "Reload", "重新加载" },
    { "Reload Without Cache", "强制重新加载" },
    { "Report Leaked Documents", "报告泄露的文档" },
    { "Report Website Issue…", "报告网站问题…" },
    { "Reset Zoom", "重置缩放" },
    { "Save Image As…", "图片另存为…" },
    { "Save Link As…", "链接另存为…" },
    { "Select All", "全选" },
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
    { "Site Isolation Process Tree", "站点隔离进程树" },
    { "Spoof User Agent", "伪造 User Agent" },
    { "Stacking Context Tree", "层叠上下文树" },
    { "Style Sheets", "样式表" },
    { "Take Screenshot...", "截取屏幕截图..." },
    { "Take Screenshot…", "截取屏幕截图…" },
    { "Toggle Bookmark", "切换书签" },
    { "Translate", "翻译" },
    { "Translation", "翻译" },
    { "Undo", "撤销" },
    { "Unmute", "取消静音" },
    { "Use Higher-Quality Models", "使用更高质量的模型" },
    { "View History", "查看历史记录" },
    { "View Page Source", "查看页面源代码" },
    { "WebKit", "WebKit" },
    { "Zoom", "缩放" },
    { "Zoom In", "放大" },
    { "Zoom Out", "缩小" },
    { "&File", "文件(&F)" },
    { "&Edit", "编辑(&E)" },
    { "&View", "视图(&V)" },
    { "&Zoom", "缩放(&Z)" },
    { "&Translation", "翻译(&T)" },
    { "&Inspect", "检查(&I)" },
    { "&Debug", "调试(&D)" },
    { "Tab &Layout", "标签页布局(&L)" },
};

QHash<QByteArray, QString> s_dictionary;
bool s_initialized { false };
bool s_enabled { false };

void initialize()
{
    s_initialized = true;

    auto language = qEnvironmentVariable("LADYBIRD_LANGUAGE");
    if (language.isEmpty())
        language = QLocale::system().name();

    if (!language.startsWith("zh", Qt::CaseInsensitive))
        return;

    s_enabled = true;
    s_dictionary.reserve(static_cast<int>(std::size(s_simplified_chinese_translations)));

    for (auto const& translation : s_simplified_chinese_translations)
        s_dictionary.insert(QByteArray { translation.english }, QString::fromUtf8(translation.simplified_chinese));
}

}

bool ui_translation_enabled()
{
    if (!s_initialized)
        initialize();
    return s_enabled;
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
    return localize(AK::StringView { text });
}

}
