// 界面本地化：为内置页面（设置、历史、下载、书签、崩溃报告等）提供多语言文本。
// 源语言为英语；缺失的字符串自动回退英语。新增语言只需增加 languagePacks 词条。
// 语言来源优先级：URL ?lang= > 设置项（C++ 注入 window.__ladybirdLanguage）> 系统语言。
(() => {
    const languagePacks = {
        "en": {},
        "zh-CN": {
        "A truly independent web browser.": "真正独立的网页浏览器。",
        "About Ladybird": "关于 Ladybird",
        "About URLs": "关于 URL",
        "Accent color": "强调色",
        "Add": "添加",
        "Add a filter list maintained by a source you trust. Automatic updates reveal your IP address to that source.": "添加由你信任的来源维护的过滤列表。自动更新会向该来源暴露你的 IP 地址。",
        "Add Adblock-compatible rules, one per line.": "添加兼容 Adblock 的规则，每行一条。",
        "Add engine": "添加引擎",
        "Add filter list…": "添加过滤列表…",
        "Add site": "添加网站",
        "Advanced": "高级",
        "After 1 hour": "1 小时后",
        "After 2 hours": "2 小时后",
        "After 30 minutes": "30 分钟后",
        "After 4 hours": "4 小时后",
        "After 8 hours": "8 小时后",
        "All time": "全部时间",
        "Allow": "允许",
        "Allow audio and video": "允许音频和视频",
        "Allow automatic service connections": "允许自动服务连接",
        "Allow this time": "仅允许这一次",
        "Always": "总是",
        "Appearance": "外观",
        "Ask me": "询问我",
        "Automatic connections": "自动连接",
        "Automatic service connections are paused. Individual service choices are preserved.": "自动服务连接已暂停。各服务的单独选择会保留。",
        "Autoplay": "自动播放",
        "Block": "阻止",
        "Block ads, trackers and more": "拦截广告、跟踪器等",
        "Block audio": "阻止音频",
        "Block audio and video": "阻止音频和视频",
        "Blossom": "花开",
        "Bookmark folders": "书签文件夹",
        "Bookmark options": "书签选项",
        "Bookmarks": "书签",
        "Bookmarks bar": "书签栏",
        "Browsing": "浏览",
        "Browsing data": "浏览数据",
        "Browsing history": "浏览历史",
        "Built": "构建时间",
        "Cached files": "缓存文件",
        "Check for updates": "检查更新",
        "Cherry": "樱桃",
        "Choose a search engine to use search suggestions.": "选择用于搜索建议的搜索引擎。",
        "Choose languages for websites in order of preference": "按偏好顺序选择网站使用的语言",
        "Clear browsing data": "清除浏览数据",
        "Clear finished": "清除已完成",
        "Clear history…": "清除历史记录…",
        "Clear…": "清除…",
        "Close": "关闭",
        "Color": "颜色",
        "Content blocking": "内容拦截",
        "Cookies and site data": "Cookie 和网站数据",
        "Copper": "铜色",
        "Copy": "复制",
        "Crash details, Ladybird version and platform.": "崩溃详情、Ladybird 版本和平台。",
        "Crash report settings": "崩溃报告设置",
        "Crash Reports": "崩溃报告",
        "Crash reports": "崩溃报告",
        "Custom DNS server": "自定义 DNS 服务器",
        "Custom filters": "自定义过滤器",
        "Custom filters must be 4 MiB or smaller.": "自定义过滤器必须小于或等于 4 MiB。",
        "Custom search engines…": "自定义搜索引擎…",
        "Dark": "深色",
        "Darken web pages that don’t provide a dark theme of their own.": "将未提供深色主题的网页调暗。",
        "Default browser": "默认浏览器",
        "Default page zoom": "默认页面缩放",
        "Delete": "删除",
        "Delete all": "全部删除",
        "Developer": "开发者",
        "DNS": "DNS",
        "DNS provider": "DNS 提供商",
        "DNS server (IP or hostname)": "DNS 服务器（IP 或主机名）",
        "Don't trust": "不信任",
        "Download history": "下载历史",
        "Downloads": "下载",
        "Edit…": "编辑…",
        "Enter": "回车",
        "Enter a site URL, such as https://example.com.": "输入网站 URL，例如 https://example.com。",
        "Enter an HTTP or HTTPS URL.": "输入 HTTP 或 HTTPS URL。",
        "Everything in the sidebar": "侧边栏中的全部内容",
        "Example": "示例",
        "Exceptions…": "例外…",
        "Expand vertical tabs on hover when collapsed": "折叠时悬停展开垂直标签页",
        "Export to HTML…": "导出为 HTML…",
        "Feature": "功能",
        "Feedback": "反馈",
        "Filter configuration keys": "过滤配置项",
        "Filter list updates": "过滤列表更新",
        "Filter list URL": "过滤列表 URL",
        "Filter lists": "过滤列表",
        "Force dark mode": "强制深色模式",
        "Force dark mode overrides": "强制深色模式覆盖",
        "Free the memory of tabs in the background. A tab reloads when you return to it. Tabs that play sound, download, or have unsaved changes stay loaded.": "释放后台标签页占用的内存。返回时会重新加载标签页。正在播放声音、下载或有未保存更改的标签页会保持加载。",
        "Full report": "完整报告",
        "Glacier": "冰川",
        "Global Privacy Control": "全局隐私控制",
        "Harbor": "港湾",
        "History": "历史记录",
        "Import from HTML…": "从 HTML 导入…",
        "Import list…": "导入列表…",
        "Include website addresses": "包含网站地址",
        "is not secure": "的连接不安全",
        "isn't trusted by Ladybird: it's self-signed, or its chain ends at a self-signed root Ladybird doesn't trust. Someone might be intercepting your connection to access private information, like passwords, messages, or credit cards.": "不被 Ladybird 信任：它是自签名的，或其证书链终止于 Ladybird 不信任的自签名根证书。可能有人正在拦截你的连接以获取密码、消息或信用卡等私密信息。",
        "Ladybird": "Ladybird",
        "Ladybird cannot determine or set the default browser on this system.": "Ladybird 无法确定或设置此系统的默认浏览器。",
        "Ladybird logomark": "Ladybird 标志",
        "Ladybird tells you when a newer version is available.": "有新版本可用时 Ladybird 会通知你。",
        "Lagoon": "泻湖",
        "Languages": "语言",
        "Languages that websites are asked to use, in order of preference.": "请求网站使用的语言，按偏好顺序排列。",
        "Last 4 hours": "最近 4 小时",
        "Last hour": "最近 1 小时",
        "Lavender": "薰衣草",
        "Layout": "布局",
        "Left": "左侧",
        "Let individually enabled services connect in the background.": "允许单独启用的服务在后台连接。",
        "Let tabs share a process": "允许标签页共享进程",
        "Licenses": "许可证",
        "Light": "浅色",
        "Links from other apps open in another browser.": "其他应用中的链接将在其他浏览器中打开。",
        "Links from other apps open in Ladybird.": "其他应用中的链接将在 Ladybird 中打开。",
        "List of About URLs": "About URL 列表",
        "Load more": "加载更多",
        "Loading downloads…": "正在加载下载…",
        "Loading history…": "正在加载历史记录…",
        "Loading the certificate warning. If nothing appears, go back or reload the page.": "正在加载证书警告。如果没有显示，请返回或重新加载页面。",
        "Loading…": "正在加载…",
        "Local file": "本地文件",
        "Location": "位置",
        "Make default": "设为默认",
        "Manage custom search engines": "管理自定义搜索引擎",
        "Memory": "内存",
        "Microphone": "麦克风",
        "Moss": "苔藓",
        "Move down": "下移",
        "Move up": "上移",
        "Never": "从不",
        "Never send": "从不发送",
        "New folder": "新建文件夹",
        "New Tab": "新建标签页",
        "New tab page URL": "新建标签页 URL",
        "No close match found for zoom factor:": "未找到接近的缩放比例：",
        "No crash reports waiting": "没有等待处理的崩溃报告",
        "No custom search engines added": "尚未添加自定义搜索引擎",
        "No settings match this search.": "没有与搜索匹配的设置。",
        "No site overrides": "没有网站覆盖设置",
        "No sites added": "尚未添加网站",
        "None": "无",
        "Nothing is kept": "不保留任何内容",
        "Notifications": "通知",
        "Only continue if you know this is a local or development server you control. Trusting lets Ladybird accept this certificate from": "仅当你确认这是你控制的本地或开发服务器时才继续。信任后，Ladybird 将接受来自以下地址的此证书",
        "Only when hovering the navigation toolbar": "仅悬停在导航工具栏时",
        "Open folder": "打开文件夹",
        "Open the folder containing saved crash reports.": "打开保存崩溃报告的文件夹。",
        "Optional": "可选",
        "Or import an Adblock-compatible list stored on this computer.": "或导入此计算机上保存的兼容 Adblock 的列表。",
        "Overrides…": "覆盖设置…",
        "Page zoom overrides": "页面缩放覆盖",
        "Pages load faster. If a site breaks, turn it off for that site from the address bar.": "页面加载更快。如果某个网站出现问题，可从地址栏为该网站关闭此功能。",
        "Paste text from the clipboard when the middle mouse button is clicked.": "单击鼠标中键时从剪贴板粘贴文本。",
        "Paste with the middle mouse button": "使用鼠标中键粘贴",
        "Periodically check whether a newer version of Ladybird is available.": "定期检查是否有更新版本的 Ladybird。",
        "Periodically download updates for enabled filter list subscriptions.": "定期为已启用的过滤列表订阅下载更新。",
        "Permissions": "权限",
        "Platform": "平台",
        "Platform features": "平台功能",
        "Port": "端口",
        "Privacy and security": "隐私与安全",
        "Privacy Policy": "隐私政策",
        "Process": "进程",
        "Remove": "移除",
        "Remove all sites": "移除所有网站",
        "Remove browsing data from:": "从以下范围移除浏览数据：",
        "Remove data": "移除数据",
        "Remove items that help pages load faster": "移除有助于加快页面加载的项目",
        "Remove items that may sign you out of most sites": "移除可能导致你在多数网站退出的项目",
        "Remove records of downloaded files, but keep the files themselves": "移除已下载文件的记录，但保留文件本身",
        "Remove visited pages from history and address bar suggestions": "从历史记录和地址栏建议中移除访问过的页面",
        "Reports are kept on this computer until you review them": "报告会保留在此计算机上，直到你查看它们",
        "Reset all": "全部重置",
        "Restore default": "恢复默认",
        "Restore previous windows and tabs": "恢复之前的窗口和标签页",
        "Review reports": "查看报告",
        "Right": "右侧",
        "Saffron": "藏红花",
        "Same site": "同一网站",
        "Same subdomain": "同一子域",
        "Save changes": "保存更改",
        "Saved": "已保存",
        "Scroll pages by pressing the middle mouse button and moving the mouse.": "按住鼠标中键并移动鼠标来滚动页面。",
        "Search": "搜索",
        "Search bookmarks": "搜索书签",
        "Search engine": "搜索引擎",
        "Search engine name": "搜索引擎名称",
        "Search history": "搜索历史记录",
        "Search settings": "搜索设置",
        "Search URL": "搜索 URL",
        "Select a language to add…": "选择要添加的语言…",
        "Send": "发送",
        "Send all": "全部发送",
        "Server certificate SHA-256 fingerprint:": "服务器证书 SHA-256 指纹：",
        "Services are automatic connections Ladybird makes for browser features in the background. These controls do not affect normal browsing or actions you explicitly request, such as updating filter lists.": "服务是 Ladybird 为后台浏览器功能建立的自动连接。这些控件不影响正常浏览或你明确请求的操作，例如更新过滤列表。",
        "Settings": "设置",
        "Settings categories": "设置分类",
        "Show bookmarks bar": "显示书签栏",
        "Show Feedback button in toolbar": "在工具栏中显示反馈按钮",
        "Show language-specific lists": "显示特定语言的列表",
        "Show report": "显示报告",
        "Show search suggestions": "显示搜索建议",
        "Show system menu bar": "显示系统菜单栏",
        "Sidebar position": "侧边栏位置",
        "Site exceptions": "网站例外",
        "Site policy": "网站策略",
        "Sites can ask to know your location.": "网站可以请求获取你的位置。",
        "Sites can ask to send you notifications.": "网站可以请求向你发送通知。",
        "Sites can ask to use your microphone.": "网站可以请求使用你的麦克风。",
        "Sites can play audio and video on their own.": "网站可以自行播放音频和视频。",
        "Sites without an override use the default setting.": "未单独设置的网站使用默认设置。",
        "Start browsing": "开始浏览",
        "Startup": "启动",
        "Startup and browsing": "启动与浏览",
        "Status": "状态",
        "Suggestions URL (optional)": "建议 URL（可选）",
        "Support": "支持",
        "System": "系统",
        "System DNS": "系统 DNS",
        "Tabs": "标签页",
        "Tabs on the side": "侧边标签页",
        "Tabs on top": "顶部标签页",
        "Tabs that share a process use less memory, but if one of them crashes, the others crash with it. Tabs of the same subdomain are on mail.example.com, and tabs of the same site are anywhere on example.com.": "共享进程的标签页占用更少内存，但其中一个崩溃时其他标签页也会一起崩溃。同一子域的标签页指 mail.example.com 上的标签页，同一网站的标签页指 example.com 任意位置上的标签页。",
        "Tell websites not to sell or share your data.": "告知网站不要出售或共享你的数据。",
        "The certificate of": "证书",
        "The colors of tabs, toolbars, menus and highlights.": "标签页、工具栏、菜单和高亮的颜色。",
        "The encoded list is too large to import.": "编码后的列表过大，无法导入。",
        "The form you submitted came from another site, so trusting won't submit it. Submit it again once the page has loaded.": "你提交的表单来自另一个网站，因此信任不会提交它。页面加载后请重新提交。",
        "The selected list is larger than 64 MiB.": "所选列表大于 64 MiB。",
        "There is no certificate to review.": "没有可查看的证书。",
        "This setting is controlled via the command line": "此设置由命令行控制",
        "TLS": "TLS",
        "Today": "今天",
        "Trademark Policy": "商标政策",
        "Trust anyway": "仍然信任",
        "Trusting sends the form you submitted again.": "信任后会再次发送你提交的表单。",
        "Turn back on": "重新开启",
        "Turned off on": "已关闭于",
        "Type": "类型",
        "UDP": "UDP",
        "Unload tabs you haven’t looked at": "卸载未查看的标签页",
        "until Ladybird is closed. Any other certificate the site presents is still verified as usual.": "直到 Ladybird 关闭。网站提供的其他证书仍会照常验证。",
        "Untrusted Certificate": "不受信任的证书",
        "Update checks": "更新检查",
        "Update enabled lists": "更新已启用的列表",
        "Updates for this build of Ladybird are managed externally.": "此版本的 Ladybird 由外部管理更新。",
        "Updating…": "正在更新…",
        "Use %s as a placeholder for the search query": "使用 %s 作为搜索查询的占位符",
        "Use %s for the query. The response must use the OpenSearch JSON format.": "使用 %s 表示查询。响应必须使用 OpenSearch JSON 格式。",
        "Use autoscrolling": "使用自动滚动",
        "Use default": "使用默认值",
        "Validate DNSSEC locally": "在本地验证 DNSSEC",
        "Version": "版本",
        "Website languages": "网站语言",
        "Websites": "网站",
        "Welcome": "欢迎",
        "Welcome to Ladybird": "欢迎使用 Ladybird",
        "What were you doing? (optional)": "你当时在做什么？（可选）",
        "Whether websites are asked to show their light or dark design.": "网站应显示浅色还是深色设计。",
        "You can change any of this later in Settings.": "你可以稍后再在设置中更改这些内容。",
        "Your connection to": "你与",
        "Cancel": "取消",
        "Canceled": "已取消",
        "Completed": "已完成",
        "Downloading": "正在下载",
        "Failed": "失败",
        "Failure": "失败",
        "Files you download in this session will show up here.": "你在本次会话中下载的文件会显示在这里。",
        "No downloads yet.": "还没有下载内容。",
        "Open": "打开",
        "Partial file removed.": "部分文件已移除。",
        "Pause": "暂停",
        "Paused": "已暂停",
        "Resume": "继续",
        "Show in folder": "在文件夹中显示",
        "The download failed.": "下载失败。",
        "The server asked us to slow down, so Ladybird is waiting to retry.": "服务器要求放慢速度，Ladybird 正在等待重试。",
        "No bookmarks here yet.": "这里还没有书签。",
        "No bookmarks match your search.": "没有与搜索内容匹配的书签。",
        "Search results": "搜索结果",
        "Untitled Folder": "未命名文件夹",
        "Forget site": "忘记网站",
        "History entry options": "历史记录选项",
        "Loading more history…": "正在加载更多历史记录…",
        "No history entries match this search.": "没有与搜索内容匹配的历史记录。",
        "Pages you visit will show up here, grouped by day.": "你访问的页面会按天分组显示在这里。",
        "Yesterday": "昨天",
        "Couldn’t send": "无法发送",
        "Hide report": "隐藏报告",
        "Include website address": "包含网站地址",
        "Just now": "刚刚",
        "Sending…": "正在发送…",
        "Checking…": "正在检查…",
        "Blocked by": "被阻止： ",
        "Device": "设备",
        "Driver": "驱动程序",
        "Driver version": "驱动版本",
        "Enabled (forced)": "已启用（强制）",
        "Hardware": "硬件",
        "Identity": "标识",
        "Library": "库",
        "None described": "未提供描述",
        "None found": "未找到",
        "Not described by this build": "此版本未描述",
        "Not supported": "不支持",
        "Probe": "探测",
        "Show": "显示",
        "Hide": "隐藏",
        "Software": "软件",
        "Supported": "支持",
        "System FFmpeg": "系统 FFmpeg",
        "Bundled FFmpeg": "内置 FFmpeg",
        "Vendor and device ID": "厂商和设备 ID",
        "Video decoding at 1080p": "1080p 视频解码",
        "Video maintenance 2": "视频维护 2",
        "Vulkan video decoding": "Vulkan 视频解码",
        "Has a Vulkan decoder built for its version": "其版本内置 Vulkan 解码器",
        "DPB and output coincide": "DPB 与输出一致",
        "DPB and output distinct": "DPB 与输出不同",
        "DPB supports DRM format modifiers": "DPB 支持 DRM 格式修饰符",
        "YCbCr sampling": "YCbCr 采样",
        "AV1 through Vulkan": "通过 Vulkan 的 AV1",
        "H.264 through Vulkan": "通过 Vulkan 的 H.264",
        "HEVC through Vulkan": "通过 Vulkan 的 HEVC",
        "VP9 through Vulkan": "通过 Vulkan 的 VP9",
        "Always show scrollbars": "始终显示滚动条",
        "Use client-side window decorations": "使用客户端窗口装饰",
        "Use custom title bar and window controls instead of the system window frame.": "使用自定义标题栏和窗口控件，而不使用系统窗口边框。",
        "The licenses could not be loaded.": "无法加载许可证信息。",
        "Development": "开发版",
        "Interface language": "界面语言",
        "Choose the language used by browser pages and menus.": "选择浏览器页面与菜单使用的语言。",
        "Follow system": "跟随系统",
        "English": "英语",
        },
    };

    // 语言别名：把 BCP 47 / Qt 风格的语言代码映射到内置语言包。
    // 新增语言只需在 languagePacks 增加一张表，并在这里补充别名。
    const aliases = {
        "zh": "zh-CN", "zh-cn": "zh-CN", "zh-hans": "zh-CN", "zh-sg": "zh-CN",
        "zh-my": "zh-CN", "zh-tw": "zh-CN", "zh-hk": "zh-CN", "zh-mo": "zh-CN",
        "zh-hant": "zh-CN",
    };

    function normalizeCode(code) {
        const value = String(code || "").trim().replace(/_/g, "-").toLowerCase();
        if (!value)
            return "";
        if (aliases[value])
            return aliases[value];
        if (value.startsWith("zh"))
            return "zh-CN";
        if (value.startsWith("en"))
            return "en";
        return value;
    }

    function resolveLanguage() {
        // 优先级：URL ?lang= > 设置项（由 C++ 注入）> 系统语言。
        const candidates = [
            new URLSearchParams(location.search).get("lang"),
            window.__ladybirdLanguage,
            navigator.language,
            ...(navigator.languages || []),
        ];
        for (const candidate of candidates) {
            const code = normalizeCode(candidate);
            if (code === "en" || languagePacks[code])
                return code;
        }
        return "en";
    }

    const dictionaries = new Map();
    for (const [language, translations] of Object.entries(languagePacks)) {
        const dictionary = new Map();
        for (const [source, translation] of Object.entries(translations))
            dictionary.set(normalize(source), translation);
        dictionaries.set(language, dictionary);
    }

    function normalize(text) {
        return text.replace(/\s+/g, " ").trim();
    }

    const translated_attributes = ["placeholder", "title", "aria-label", "alt"];
    const originals = [];
    let currentLanguage = "en";
    let applying = false;

    function restoreOriginals() {
        for (let i = originals.length - 1; i >= 0; --i) {
            const record = originals[i];
            if (record.attribute === null) {
                if (record.node.nodeValue !== record.value)
                    record.node.nodeValue = record.value;
            } else if (record.node.getAttribute(record.attribute) !== record.value) {
                record.node.setAttribute(record.attribute, record.value);
            }
        }
        originals.length = 0;
    }

    function translate_text_node(node) {
        const original = node.nodeValue;
        if (!original || !original.trim())
            return;
        const dictionary = dictionaries.get(currentLanguage);
        if (!dictionary)
            return;
        const leading = original.match(/^\s*/)[0];
        const trailing = original.match(/\s*$/)[0];
        const core = original.slice(leading.length, original.length - trailing.length);
        const translation = dictionary.get(normalize(core));
        if (translation === undefined || translation === core)
            return;
        originals.push({ node, attribute: null, value: original });
        node.nodeValue = leading + translation + trailing;
    }

    function translate_element(element) {
        const dictionary = dictionaries.get(currentLanguage);
        if (!dictionary || !element.hasAttribute)
            return;
        for (const attribute of translated_attributes) {
            if (!element.hasAttribute(attribute))
                continue;
            const value = element.getAttribute(attribute);
            const translation = dictionary.get(normalize(value));
            if (translation === undefined || translation === value)
                continue;
            originals.push({ node: element, attribute, value });
            element.setAttribute(attribute, translation);
        }
    }

    function translate_subtree(root) {
        if (root.nodeType === Node.TEXT_NODE) {
            translate_text_node(root);
            return;
        }
        if (root.nodeType !== Node.ELEMENT_NODE && root.nodeType !== Node.DOCUMENT_NODE)
            return;
        if (root.nodeType === Node.ELEMENT_NODE)
            translate_element(root);
        const walker = document.createTreeWalker(root, NodeFilter.SHOW_TEXT | NodeFilter.SHOW_ELEMENT);
        let node = walker.nextNode();
        while (node) {
            if (node.nodeType === Node.TEXT_NODE)
                translate_text_node(node);
            else
                translate_element(node);
            node = walker.nextNode();
        }
    }

    function translate_title() {
        const dictionary = dictionaries.get(currentLanguage);
        if (!dictionary)
            return;
        const translation = dictionary.get(normalize(document.title));
        if (translation !== undefined && translation !== document.title)
            document.title = translation;
    }

    function apply(language) {
        applying = true;
        try {
            restoreOriginals();
            currentLanguage = language;
            document.documentElement.lang = language;
            window.__ladybirdUILanguage = language;
            if (language === "en")
                return;
            translate_subtree(document.body || document.documentElement);
            translate_title();
        } finally {
            applying = false;
        }
    }

    // 供设置页调用：切换后本页面立即生效，其他页面可监听该事件同步刷新。
    window.ladybirdSetUILanguage = function (code) {
        window.__ladybirdLanguage = String(code || "");
        apply(resolveLanguage());
        window.dispatchEvent(new CustomEvent("ladybirduilanguagechange", {
            detail: { language: currentLanguage },
        }));
        return currentLanguage;
    };

    // The native side answers this on every built-in page. "system" means: fall back to navigator.language.
    document.addEventListener("WebUILoaded", () => {
        window.ladybird?.sendMessage("loadUILanguage");
    });
    document.addEventListener("WebUIMessage", event => {
        if (event.detail?.name !== "loadUILanguage")
            return;
        const code = event.detail.data;
        window.__ladybirdLanguage = code === "system" ? "" : String(code || "");
        apply(resolveLanguage());
    });

    function start() {
        apply(resolveLanguage());
        const observer = new MutationObserver(records => {
            if (applying || currentLanguage === "en")
                return;
            for (const record of records) {
                if (record.type === "characterData") {
                    translate_text_node(record.target);
                    continue;
                }
                if (record.type === "attributes") {
                    translate_element(record.target);
                    continue;
                }
                for (const node of record.addedNodes)
                    translate_subtree(node);
            }
            translate_title();
        });
        observer.observe(document.documentElement, {
            subtree: true,
            childList: true,
            characterData: true,
            attributes: true,
            attributeFilter: translated_attributes,
        });
    }

    if (document.readyState === "loading")
        document.addEventListener("DOMContentLoaded", start);
    else
        start();
})();
