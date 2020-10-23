# shaders
Collection of Shadertoy shaders displayed in a Qt window.

## Build
```
mkdir build
cd build
cmake ../ -DCMAKE_BUILD_TYPE=Release
make
```

## Usage
You can skip through the shaders with the mouse wheel.

## Adding a new shader
```
- Add fragment shader and texture files
- Add header file for the new effect
- Add new effect to the effects enum in mainwindow.h
- Add new case in MainWindow::setEffect()
- Update CMakeLists.txt and resources.rc
```
See existing files for examples.

### Currently supported Shadertoy variables
```
uniform vec3         iResolution              // viewport resolution (in pixels)
uniform float        iTime                    // shader playback time (in seconds)
uniform vec3         iChannelResolution[4]    // channel resolution (in pixels)
uniform samplerXX    iChannel0..3             // input channel. XX = 2D/Cube
```

## Credits
- digitalrain: [Digital Rain](https://www.shadertoy.com/view/ldccW4) by WillKirkby
- matrix: [3d matrix rain](https://www.shadertoy.com/view/MsVBDG) by laserdog
- starfield: Modified version of [Parallax starfield](https://www.shadertoy.com/view/WsfGDM) by dax105

## License
- All fragment shaders and images: [CC BY-NC-SA 3.0](https://creativecommons.org/licenses/by-nc-sa/3.0/)
- All other: [MIT License](./LICENSE.md)
