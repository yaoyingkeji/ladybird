# Ladybird

[Ladybird](https://ladybird.org) is a truly independent web browser, using a novel engine based on web standards.

> [!IMPORTANT]
> Ladybird is in a pre-alpha state, and only suitable for use by developers
>

## 本仓库的分支 / Branches in this fork

> 本仓库是 [LadybirdBrowser/ladybird](https://github.com/LadybirdBrowser/ladybird) 的社区 fork，**不是官方发布**。
> This repository is a community fork of [LadybirdBrowser/ladybird](https://github.com/LadybirdBrowser/ladybird).
> Builds published here are **not** official Ladybird releases.

| 分支 / Branch | 说明 / Description |
| --- | --- |
| [`auto-build`](https://github.com/yaoyingkeji/ladybird/tree/auto-build)（默认 / default） | 上游 `master` + 自动打包工作流 / upstream `master` plus the automated packaging workflows |
| [`master`](https://github.com/yaoyingkeji/ladybird/tree/master) | 上游镜像，保持原样 / unmodified mirror of upstream |

### 自动构建 / Automated builds

- 每日 UTC 02:00 定时构建，也可手动触发 / built daily at 02:00 UTC, and on demand
- 产物 / artifacts: `.deb`（Ubuntu 22.04 构建，x86_64，含 `ladybird-dbgsym`）与 `.AppImage`（x86_64）
- 版本号 / version: `<上游标签 upstream tag>.auto.<YYYYMMDD>`
- 下载 / download: [Releases](https://github.com/yaoyingkeji/ladybird/releases/latest)
- 构建日志 / build logs: [Actions](https://github.com/yaoyingkeji/ladybird/actions/workflows/build-packages.yml)

```bash
# Ubuntu 22.04+ / Debian 12+ / Deepin 25+ (x86_64)
sudo apt install ./ladybird_*.deb

# AppImage (x86_64)
chmod +x ladybird-*.AppImage && ./ladybird-*.AppImage
```

构建环境：Ubuntu 22.04、Clang、`Distribution` preset（LTO，Qt 由 vcpkg 构建），运行要求 glibc ≥ 2.35（Ubuntu 22.04+、Debian 12+、Deepin 25+）。
Build environment: Ubuntu 22.04 with Clang and the `Distribution` preset (LTO, Qt from vcpkg); requires glibc ≥ 2.35 (Ubuntu 22.04+, Debian 12+, Deepin 25+).

### 上游同步 / Upstream sync

- 每日 UTC 01:30 检测上游 [LadybirdBrowser/ladybird](https://github.com/LadybirdBrowser/ladybird) 的分支、标签与发布是否有更新 / checks upstream branches, tags and releases daily at 01:30 UTC
- 有更新时才同步：所有分支、标签与发布（含发布说明和附件）/ when changes are found, all branches, tags and releases (including notes and assets) are mirrored
- 标签直接使用上游原始标签对象，打标签者与时间保持不变 / tags are the original upstream tag objects, so the tagger and date are preserved
- 同步的发布保留上游名称、说明、预发布标记与附件，并在说明顶部记录上游作者和发布时间（GitHub 不允许直接设置这两项）/ mirrored releases keep the upstream name, notes, prerelease flag and assets, and record the upstream author and publish time at the top of the notes (GitHub does not allow setting these two fields directly)
- 上游 `master` 前进时自动变基 `auto-build`，冲突时改用合并提交 / `auto-build` is rebased onto upstream `master` when it advances, falling back to a merge commit on conflicts
- 上游没有更新时不产生任何提交或推送 / nothing is committed or pushed when upstream has no changes
- 同步后的提交者为本仓库账号，不使用机器人身份 / commits created by the sync use this repository's account, not a bot identity

### 中文界面 / Chinese interface

`auto-build` 分支加入了简体中文界面：菜单、地址栏、查找栏、下载与书签、权限提示、设置页、历史页、证书警告、崩溃报告等均已翻译；未收录的文本自动回退英文。
The `auto-build` branch adds a Simplified Chinese interface: menus, address bar, find bar, downloads and bookmarks, permission prompts, built-in settings/history pages, certificate warnings, crash reports and more. Untranslated text falls back to English.

系统语言为 `zh_*` 时自动启用；也可单独指定 / Enabled automatically when the system locale is `zh_*`, or force it with:

```bash
LADYBIRD_LANGUAGE=zh-CN ladybird
```

内置页面按浏览器的 `navigator.language` 判断语言；如需覆盖，可在页面 URL 后加 `?lang=zh-CN`。
Built-in pages use the browser's `navigator.language`; append `?lang=zh-CN` to the page URL to override it.
更新检查与 AppImage 自更新已关闭，构建未做代码签名。/ Update checks and AppImage self-updates are disabled; builds are not code signed.

## Features

We aim to build a complete, usable browser for the modern web.

Ladybird uses a [multi-process architecture](Documentation/ProcessArchitecture.md) with a main UI process,
WebContent renderer processes, and helper processes for tasks such as networking, image decoding, compositing and media.

Documents from different sites run in separate renderer processes, each sandboxed from the rest of the system.
Image decoding and network connections are done out of process, separately for each site, to be more robust against
malicious content.

At the moment, many core library support components are inherited from SerenityOS:

- LibWeb: Web rendering engine
- LibJS: JavaScript engine
- LibWasm: WebAssembly implementation
- LibCrypto/LibTLS: Cryptography primitives and Transport Layer Security
- LibHTTP: HTTP/1.1 client
- LibGfx: 2D Graphics Library, Image Decoding and Rendering
- LibUnicode: Unicode and locale support
- LibMedia: Audio and video playback
- LibCore: Event loop, OS abstraction layer
- LibIPC: Inter-process communication

## How do I build and run this?

See [build instructions](Documentation/BuildInstructionsLadybird.md) for information on how to build Ladybird.

Ladybird runs on Linux, macOS, Windows (with WSL2), and many other \*Nixes.

## How do I read the documentation?

Code-related documentation can be found in the [documentation](Documentation/) folder.

## Get in touch and participate!

Join [our Discord server](https://discord.gg/nvfjVJ4Svh) to participate in issue and development discussions.

Please read [Getting involved with Ladybird](Documentation/GettingStartedContributing.md) if you're new to Ladybird and want to help.

Before opening an issue, please see the [issue policy](CONTRIBUTING.md#issue-policy) and the [detailed issue-reporting guidelines](ISSUES.md).

The project participation guidelines can be found in [`CONTRIBUTING.md`](CONTRIBUTING.md).

## License

Ladybird is licensed under a 2-clause BSD license.
