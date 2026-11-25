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
    schedule) trigger='每日定时 / scheduled' ;;
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
| 分支 / Branch | \`auto-build\`（本 fork 的默认分支 / default branch of this fork） |
| 版本 / Version | \`${VERSION}\` |
| 标签 / Tag | \`${TAG}\` |
| 提交 / Commit | [\`${commit_short}\`](${server}/${repo}/commit/${COMMIT}) |
| 上游基线 / Upstream base | \`${UPSTREAM}\` |
| 触发方式 / Trigger | ${trigger} |
| 构建时间 / Built at | ${built_at} UTC |
| 工作流 / Workflow run | [#${GITHUB_RUN_NUMBER:-0}](${run_url}) |

## 构建产物 / Artifacts

| 文件 / File | 大小 / Size |
| --- | --- |
${rows}
校验和 / Checksums: \`SHA256SUMS.txt\`

## 安装 / Installation

Debian 包（Ubuntu 24.04 / Debian 13 及更新版本，x86_64）/ Debian package (Ubuntu 24.04 / Debian 13+, x86_64):

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
- 界面支持简体中文，随系统语言或 `LADYBIRD_LANGUAGE` 启用 / Simplified Chinese UI follows the system language or `LADYBIRD_LANGUAGE`
- 更新检查与 AppImage 自更新已关闭 / update checks and AppImage self-updates are disabled
- 使用 Ubuntu 24.04 + Clang + \`Distribution\` preset（LTO、Qt 由 vcpkg 构建）/ built on Ubuntu 24.04 with Clang, the \`Distribution\` preset, LTO, and Qt from vcpkg
- 需要 glibc ≥ 2.39 / requires glibc ≥ 2.39
- 由 GitHub Actions 自动生成，未经过人工测试 / produced by GitHub Actions without manual testing

## 构建方式 / How it is built

工作流 / workflow: [\`.github/workflows/build-packages.yml\`](${server}/${repo}/blob/auto-build/.github/workflows/build-packages.yml)
EOF
