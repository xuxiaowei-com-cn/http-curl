# http-curl

## [vcpkg](https://github.com/microsoft/vcpkg)

- [中文概述](https://github.com/microsoft/vcpkg/blob/master/README_zh_CN.md)
    - [快速开始: Windows](https://github.com/microsoft/vcpkg/blob/master/README_zh_CN.md#%E5%BF%AB%E9%80%9F%E5%BC%80%E5%A7%8B-windows)
    - 安装依赖
        - 注意事项
            - 需要安装 Visual Studio 英文语言包
        - [curl](https://github.com/curl/curl)
            ```
            vcpkg install curl
            vcpkg install curl:x64-windows
            ```
        - [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
            ```
            vcpkg install jsoncpp
            vcpkg install jsoncpp:x64-windows
            ```
