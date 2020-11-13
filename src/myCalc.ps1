$wshell = New-Object -ComObject Wscript.Shell
$wshell.Run("calc")
Start-Sleep -m 1000
$wshell.appactivate("Calculator")
Start-Sleep -m 1000
$wshell.SendKeys("5")
Start-Sleep -m 1000
$wshell.SendKeys("*")
Start-Sleep -m 500
$wshell.SendKeys("5")
Start-Sleep -m 1500
$wshell.SendKeys("=")