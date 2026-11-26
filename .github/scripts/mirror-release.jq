# 把上游 release 转成本仓库的创建/更新请求体。
# GitHub 不允许设置发布作者和发布时间，因此把上游信息原样写在说明顶部。
{
  tag_name: .tag_name,
  name: .name,
  body: (
    "> 本发布同步自上游 [" + $repo + "](" + $server + "/" + $repo + ")\n" +
    "> 上游作者 / Upstream author: @" + (.author.login // "unknown") + "\n" +
    "> 上游发布时间 / Published upstream: " + (.published_at // .created_at // "unknown") + "\n" +
    "> 原始发布 / Original release: " + (.html_url // "") + "\n\n" +
    (.body // "")
  ),
  draft: .draft,
  prerelease: .prerelease,
  make_latest: "false"
}
