# パラメータ設定
# Line Notify エンドポイント
$uri    =  "https://notify-api.line.me/api/notify"

# トークン
$token  = "EmcpAu24UiBeVCSSSL1OW8fKKOY9EjE4vxEjKCYksLz"

# トークンをリクエストヘッダ内Authorizationに指定
$header = @{Authorization=$token}

# POSTパラメータにメッセージを指定
$body   = @{message="PowerShell から LINE Notify"}

# ★リクエスト実行
$res = Invoke-RestMethod -Uri $uri -Method Post -Headers $header -Body $body 

# デバッグ用結果表示
echo $res