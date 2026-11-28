#!/usr/bin/env bash

# Writes the bilingual release notes for an automated build to stdout.
#
# Usage: release-notes.sh [PACKAGES_DIRECTORY]

set -euo pipefail

packages_dir=${1:-Build/packages}

: "${VERSION:?VERSION is not set}"
: "${TAG:?TAG is not set}"
: "${COMMIT:?COMMIT is not set}"
: "${UPSTREAM:?UPSTREAM is not set}"
: "${TRIGGER:?TRIGGER is not set}"

repo=${GITHUB_REPOSITORY:-yaoyingkeji/ladybird}
server=${GITHUB_SERVER_URL:-https://github.com}
run_url="${server}/${repo}/actions/runs/${GITHUB_RUN_ID:-0}"
commit_short=${COMMIT:0:12}
built_at=$(date -u '+%Y-%m-%d %H:%M')

case "$TRIGGER" in
    push) trigger='代码更新 / push' ;;
    schedule) trigger='定时 / scheduled' ;;
    workflow_dispatch) trigger='手动触发 / manual' ;;
    *) trigger="$TRIGGER" ;;
esac

rows=''
shopt -s nullglob
for file in "$packages_dir"/*.AppImage "$packages_dir"/*.deb; do
    rows+="| \`$(basename "$file")\` | $(du -h "$file" | cut -f1) |"$'\n'
done

cat <<EOF
> [!WARNING]
> 这是社区 fork（[${repo}](${server}/${repo})）的自动构建，**不是 Ladybird 官方发布**。
> This is an automated build from a community fork. It is **not** an official Ladybird release.

## 构建来源 / Build provenance

| 项目 / Item | 值 / Value |
| --- | --- |
| 分支 / Branch | \`main\`（本 fork 的开发主线与默认分支 / development and default branch of this fork） |
| 版本 / Version | \`${VERSION}\` |
| 标签 / Tag | \`${TAG}\`（滚动标签，始终指向最近一次成功的最新构建 / rolling tag, always points to the latest successful build） |
| 提交 / Commit | [\`${commit_short}\`](${server}/${repo}/commit/${COMMIT}) |
| 上游基线 / Upstream base | \`${UPSTREAM}\` |
| 触发方式 / Trigger | ${trigger} |
| 构建时间 / Built at | ${built_at} UTC |
| 工作流 / Workflow run | [#${GITHUB_RUN_NUMBER:-0}](${run_url}) |

## 构建产物 / Artifacts

| 文件 / File | 大小 / Size |
| --- | --- |
${rows}
校验和 / Checksums: \`SHA256SUMS-${VERSION}.txt\`（本版本 / this build）、\`SHA256SUMS.txt\`（始终指向最近一次构建 / always the latest build）

固定下载地址 / Stable download: [${TAG}](${server}/${repo}/releases/tag/${TAG})（每次成功构建覆盖 / replaced on every successful build）

## 安装 / Installation

Debian 包（Ubuntu 22.04+ / Debian 12+ / Deepin 25+，x86_64）/ Debian package (Ubuntu 22.04+ / Debian 12+ / Deepin 25+, x86_64):

\`\`\`bash
sudo apt install ./ladybird_*.deb
\`\`\`

AppImage（x86_64）/ AppImage (x86_64):

\`\`\`bash
chmod +x ladybird-*.AppImage
./ladybird-*.AppImage
# 没有 FUSE 时 / without FUSE:
./ladybird-*.AppImage --appimage-extract-and-run
\`\`\`

## 与官方构建的差异 / Differences from official builds

- 未做代码签名与构建证明 / no code signing or build attestation
- 支持界面语言设置（跟随系统 / English / 简体中文），简体中文为完整语言包；WebUI 另可用 \`?lang=zh-CN\` 强制中文 / Interface language setting (follow system / English / Simplified Chinese) with a complete Chinese pack; WebUI also accepts \`?lang=zh-CN\`
- 更新检查与 AppImage 自更新已关闭 / update checks and AppImage self-updates are disabled
- 使用 Ubuntu 22.04 + Clang + \`Distribution\` preset（LTO、Qt 由 vcpkg 构建）/ built on Ubuntu 22.04 with Clang, the \`Distribution\` preset, LTO, and Qt from vcpkg
- 需要 glibc ≥ 2.35 / requires glibc ≥ 2.35
- 由 GitHub Actions 自动生成，未经过人工测试 / produced by GitHub Actions without manual testing

## 构建方式 / How it is built

工作流 / workflow: [\`.github/workflows/fork-build.yml\`](${server}/${repo}/blob/main/.github/workflows/fork-build.yml)
EOF
