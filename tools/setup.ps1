
Set-Location $PSScriptRoot\..
New-Item .\downloads -ItemType Directory
New-Item .\libs\bin -ItemType Directory
New-Item .\libs\include -ItemType Directory
New-Item .\libs\lib -ItemType Directory

# ncnn
Invoke-WebRequest -Uri "https://github.com/Tencent/ncnn/releases/download/20221128/ncnn-20221128-windows-vs2022-shared.zip" -OutFile .\downloads\ncnn-windows.zip
Expand-Archive .\downloads\ncnn-windows.zip -DestinationPath .\downloads\ncnn-windows -Force
Copy-Item -Path .\downloads\ncnn-windows\ncnn-20221128-windows-vs2022-shared\x86\bin -Destination .\libs -Recurse -Force -Verbose
Copy-Item -Path .\downloads\ncnn-windows\ncnn-20221128-windows-vs2022-shared\x86\include -Destination .\libs -Recurse -Force -Verbose
Copy-Item -Path .\downloads\ncnn-windows\ncnn-20221128-windows-vs2022-shared\x86\lib -Destination .\libs -Recurse -Force -Verbose

# lua
Invoke-WebRequest -Uri "https://master.dl.sourceforge.net/project/luabinaries/5.1.4/Windows%20Libraries/lua5_1_4_Win32_dll8_lib.zip?viasf=1" -OutFile .\downloads\lua-windows.zip
Expand-Archive .\downloads\lua-windows.zip -DestinationPath .\downloads\lua-windows -Force
Move-Item -Path .\downloads\lua-windows\include\* -Destination .\libs\include -Force -Verbose
Copy-Item -Path .\downloads\lua-windows\* -Destination .\libs\lib -Recurse -Force -Verbose

# opencv
Invoke-WebRequest -Uri "https://github.com/streamwest-1629/kasaibox/releases/download/artifact-release/opencv4.6.0-x86-vc17.zip" -OutFile .\downloads\opencv-windows.zip
Expand-Archive .\downloads\opencv-windows.zip -DestinationPath .\downloads\opencv-windows -Force
Copy-Item -Path .\downloads\opencv-windows\opencv4.7.0-x86-vc17\bin -Destination .\libs -Recurse -Force -Verbose
Copy-Item -Path .\downloads\opencv-windows\opencv4.7.0-x86-vc17\include -Destination .\libs -Recurse -Force -Verbose
Copy-Item -Path .\downloads\opencv-windows\opencv4.7.0-x86-vc17\lib -Destination .\libs -Recurse -Force -Verbose

# Real-ESRGAN
Invoke-WebRequest -Uri "https://github.com/xinntao/Real-ESRGAN/releases/download/v0.2.3.0/realesrgan-ncnn-vulkan-20211212-windows.zip" -OutFile .\downloads\real-esrgan.zip
Expand-Archive .\downloads\real-esrgan.zip -DestinationPath .\downloads\real-esrgan -Force
Copy-Item -Path .\downloads\real-esrgan\models .\ -Recurse -Force -Verbose

Remove-Item .\downloads -Recurse

