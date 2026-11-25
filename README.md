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
- 产物 / artifacts: `.deb`（Ubuntu 24.04, x86_64，含 `ladybird-dbgsym`）与 `.AppImage`（x86_64）
- 版本号 / version: `<上游标签 upstream tag>.auto.<YYYYMMDD>`
- 下载 / download: [Releases](https://github.com/yaoyingkeji/ladybird/releases/latest)
- 构建日志 / build logs: [Actions](https://github.com/yaoyingkeji/ladybird/actions/workflows/build-packages.yml)

```bash
# Debian / Ubuntu 24.04+ (x86_64)
sudo apt install ./ladybird_*.deb

# AppImage (x86_64)
chmod +x ladybird-*.AppImage && ./ladybird-*.AppImage
```

构建环境：Ubuntu 24.04、Clang、`Distribution` preset（LTO，Qt 由 vcpkg 构建），运行要求 glibc ≥ 2.39。
Build environment: Ubuntu 24.04 with Clang and the `Distribution` preset (LTO, Qt from vcpkg); requires glibc ≥ 2.39.
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
