# Sample C app for Epsilon

[![Build](https://github.com/numworks/epsilon-sample-app-c/actions/workflows/build.yml/badge.svg)](https://github.com/numworks/epsilon-sample-app-c/actions/workflows/build.yml)

This is a sample C app to use on a [NumWorks calculator](https://www.numworks.com).

```c
#include <eadk.h>

int main(int argc, char * argv[]) {
  eadk_display_draw_string("Hello, world!", (eadk_point_t){0, 0}, true, eadk_color_black, eadk_color_white);
  eadk_timing_msleep(3000);
}
```

## Build the app

You need to install an embedded ARM toolchain and [nwlink](https://www.npmjs.com/package/nwlink).

```shell
brew install numworks/tap/arm-none-eabi-gcc node # Or equivalent on your OS
npm install -g nwlink
make clean && make build
```

Once you app 'output/app.nwa' is built, you can upload it onto your calculator from [NumWorks online uploader](https://my.numworks.com/apps).

## Run the app (development)

The app is sent over to the calculator using the DFU protocol over USB.
The last command has to be executed with the targeted device plugged to the computer.

```shell
# Now connect your NumWorks calculator to your computer using the USB cable
make run
```

## License

This sample app is distributed under the terms of the BSD License. See LICENSE for details.

## Trademarks

NumWorks is a registered trademark.
