
Set-Location $PSScriptRoot\..
New-Item .\downloads -ItemType Directory

# ncnn
Invoke-WebRequest -Uri "https://github.com/Tencent/ncnn/releases/download/20221128/ncnn-20221128-windows-vs2022.zip" -OutFile .\downloads\ncnn-windows.zip
Expand-Archive .\downloads\ncnn-windows.zip -DestinationPath .\downloads\ncnn-windows -Force
Copy-Item -Path .\downloads\ncnn-windows\ncnn-20221128-windows-vs2022\x86\bin -Destination .\libs -Recurse -Force
Copy-Item -Path .\downloads\ncnn-windows\ncnn-20221128-windows-vs2022\x86\include -Destination .\libs -Recurse -Force
Copy-Item -Path .\downloads\ncnn-windows\ncnn-20221128-windows-vs2022\x86\lib -Destination .\libs -Recurse -Force

# lua
Invoke-WebRequest -Uri "https://master.dl.sourceforge.net/project/luabinaries/5.1.4/Windows%20Libraries/lua5_1_4_Win32_dll8_lib.zip?viasf=1" -OutFile .\downloads\lua-windows.zip
Expand-Archive .\downloads\lua-windows.zip -DestinationPath .\downloads\lua-windows -Force
Move-Item -Path .\downloads\lua-windows\include\* -Destination .\libs\include -Force
Copy-Item -Path .\downloads\lua-windows\* -Destination .\libs\lib -Recurse -Force

Remove-Item .\downloads -Recurse

