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
    { "%1 of %2", "第 %1 项，共 %2 项" },
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
    { "100%", "100%" },
    { "About Ladybird", "关于 Ladybird" },
    { "Add Bookmark…", "添加书签…" },
    { "Add bookmark", "添加书签" },
    { "Add folder", "添加文件夹" },
    { "All Resolved Styles", "所有已解析样式" },
    { "All site settings", "所有网站设置" },
    { "Allow", "允许" },
    { "Allow this time", "仅允许这一次" },
    { "Allow while visiting the site", "访问此网站时允许" },
    { "Ask", "询问" },
    { "Auto", "自动" },
    { "Autoplay", "自动播放" },
    { "Back", "后退" },
    { "Back to site settings", "返回网站设置" },
    { "Block", "阻止" },
    { "Block Pop-ups", "阻止弹出窗口" },
    { "Block audio", "阻止音频" },
    { "Blocked on this page", "此页面已拦截的内容" },
    { "Bookmark All Tabs…", "为所有标签页添加书签…" },
    { "Bookmarks", "书签" },
    { "Bookmarks bar", "书签栏" },
    { "CSS Errors", "CSS 错误" },
    { "Chrome", "Chrome" },
    { "Cl&ose Other Tabs", "关闭其他标签页(&O)" },
    { "Clear Browsing Data", "清除浏览数据" },
    { "Clear finished", "清除已完成" },
    { "Close Tabs B&elow", "关闭下方标签页(&E)" },
    { "Close Tabs to the R&ight", "关闭右侧标签页(&I)" },
    { "Close find", "关闭查找" },
    { "Collect Garbage", "回收垃圾" },
    { "Color Scheme", "配色方案" },
    { "Connection is not secure", "连接不安全" },
    { "Content blocking", "内容拦截" },
    { "Content blocking on this site", "对此网站启用内容拦截" },
    { "Contrast", "对比度" },
    { "Cookies", "Cookie" },
    { "Copy", "复制" },
    { "Copy &Link", "复制链接(&L)" },
    { "Copy Image", "复制图片" },
    { "Copy Link", "复制链接" },
    { "Copy Link to Highlight", "复制指向高亮的链接" },
    { "Crash Compositor Process", "使合成器进程崩溃" },
    { "Crash Current Page", "使当前页面崩溃" },
    { "Cut", "剪切" },
    { "DOM Tree", "DOM 树" },
    { "Dark", "深色" },
    { "Debug", "调试" },
    { "Default (%1)", "默认（%1）" },
    { "Delete", "删除" },
    { "Delete Folder", "删除文件夹" },
    { "DevTools is enabled on port %1", "开发者工具已在端口 %1 上启用" },
    { "Disable", "禁用" },
    { "Disable DevTools", "禁用开发者工具" },
    { "Disabled", "已禁用" },
    { "Display List", "显示列表" },
    { "Download", "下载" },
    { "Download Linked File", "下载链接文件" },
    { "Downloads", "下载" },
    { "Dump", "转储" },
    { "Edit Folder…", "编辑文件夹…" },
    { "Edit bookmark", "编辑书签" },
    { "Edit folder", "编辑文件夹" },
    { "Edit…", "编辑…" },
    { "Enable DevTools", "启用开发者工具" },
    { "Enable Scripting", "启用脚本" },
    { "Exit Full Screen", "退出全屏" },
    { "Exit Picture in Picture", "退出画中画" },
    { "Filter lists", "过滤列表" },
    { "Find in page", "在页面中查找" },
    { "Folder:", "文件夹：" },
    { "Force Dark Mode", "强制深色模式" },
    { "Force dark mode", "强制深色模式" },
    { "Force dark mode on this site", "对此网站强制深色模式" },
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
    { "Ladybird can't %1", "Ladybird 无法%1" },
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
    { "Navigator Compatibility Mode", "Navigator 兼容模式" },
    { "Never allow", "永不允许" },
    { "New Folder…", "新建文件夹…" },
    { "New Private Window", "新建隐私窗口" },
    { "New Tab", "新建标签页" },
    { "New Tab &Below", "在下方新建标签页(&B)" },
    { "New Tab to the &Right", "在右侧新建标签页(&R)" },
    { "New Window", "新建窗口" },
    { "Next match", "下一个匹配项" },
    { "No Guesses Found", "未找到拼写建议" },
    { "No Preference", "无偏好" },
    { "No downloads", "暂无下载" },
    { "No matches", "无匹配项" },
    { "Not now", "暂不" },
    { "Not secure", "不安全" },
    { "Nothing has been blocked on this page.", "此页面没有拦截任何内容。" },
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
    { "Previous match", "上一个匹配项" },
    { "Recently closed", "最近关闭" },
    { "Redo", "重做" },
    { "Reduce", "缩小" },
    { "Reload", "重新加载" },
    { "Reload Without Cache", "强制重新加载" },
    { "Report Leaked Documents", "报告泄露的文档" },
    { "Report Website Issue…", "报告网站问题…" },
    { "Reset", "重置" },
    { "Reset Zoom", "重置缩放" },
    { "Reset permissions", "重置权限" },
    { "Save Image As…", "图片另存为…" },
    { "Save Link As…", "链接另存为…" },
    { "Search or enter address", "搜索或输入网址" },
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
    { "Show all downloads", "显示所有下载" },
    { "Site Isolation Process Tree", "站点隔离进程树" },
    { "Site settings", "网站设置" },
    { "Spoof User Agent", "伪造 User Agent" },
    { "Stacking Context Tree", "层叠上下文树" },
    { "Style Sheets", "样式表" },
    { "Tab &Layout", "标签页布局(&L)" },
    { "Take Screenshot...", "截取屏幕截图..." },
    { "Take Screenshot…", "截取屏幕截图…" },
    { "The connection to this site is not secure", "与此网站的连接不安全" },
    { "This file", "此文件" },
    { "This page", "此页面" },
    { "This page is using your location", "此页面正在使用你的位置" },
    { "This page is using your microphone", "此页面正在使用你的麦克风" },
    { "Title:", "标题：" },
    { "Toggle Bookmark", "切换书签" },
    { "Translate", "翻译" },
    { "Translation", "翻译" },
    { "URL:", "网址：" },
    { "Un&mute Tab", "取消静音(&M)" },
    { "Undo", "撤销" },
    { "Unmute", "取消静音" },
    { "Use Higher-Quality Models", "使用更高质量的模型" },
    { "Using your location", "正在使用你的位置" },
    { "Using your microphone", "正在使用你的麦克风" },
    { "View History", "查看历史记录" },
    { "View Page Source", "查看页面源代码" },
    { "WebKit", "WebKit" },
    { "Your system will then ask you to let Ladybird %1.", "随后系统会询问是否允许 Ladybird %1。" },
    { "Your system's privacy settings don't let Ladybird %1.", "你的系统隐私设置不允许 Ladybird %1。" },
    { "Zoom", "缩放" },
    { "Zoom In", "放大" },
    { "Zoom Out", "缩小" },
    { "know your location", "获取你的位置" },
    { "send you notifications", "向你发送通知" },
    { "use your microphone", "使用你的麦克风" },
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
