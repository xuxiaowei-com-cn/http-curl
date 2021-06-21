# http-curl

## [curl](https://github.com/curl/curl)

## [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

- [Build with VS 2019 on Windows](https://github.com/open-source-parsers/jsoncpp/wiki/Build-with-VS-2019-on-Windows)

    - x86

    ```
    mkdir build_x86
    cd build_x86
    "D:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
    cmake -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF ..
    cmake --build . --config Release
    cmake --build . --config Debug
    ```

    - x64

    ```
    mkdir build_x64
    cd build_x64
    "D:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    cmake -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF ..
    cmake --build . --config Release
    cmake --build . --config Debug
    ```
