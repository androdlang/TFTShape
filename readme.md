# TFTShape
TFTShape is a 2D graphics library designed to work with the [Bodmer/TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) library which supports SPI-TFT-displays for ESP8266/ESP32 processors. This library is abstracting low level primitives (pixels, lines) to bring them together for use as shape-based 2D drawing functions. It was developed to have an efficient implementation with a low footprint to run with best performance on the target processors. TFTShape has successfully been tested on an ODROID-GO (ILI9341 and ESP32@150MHz Wrover inside).

TFTShape uses, as the name states, a shape based concept. Shapes are containers for groups of vertices which will be interpreted mostly as closed polygons, but depending on the used shape, the vertices can also be single points, open polygons or independent lines. Shapes have all common 2D drawing functions implemented, this includes sizing, translation, rotation, setting a pivot point and filling functions. Shapes can also be used to draw another shape at the position of the parent shape's vertices (grouping). 

Following classes and subclasses are available:
* TFTShape - represents points and closed lines (polygons)
* TFTLineShape - represents individual lines
* TFTSplineShape - represents points interpreted as B-splines (open and looped splines)
* TFTLinestripShape - represent contiguous lines (not closed)
* TFTShapeBuilder - Factory to create special shapes, ie. grids,splines,stars, n-gons etc.

To have an overview about the various output this library can produce, here are screenshots from the testsuite of the examples directory: 

![screenshot_20293.png](/images/screenshot_20293.png) ![screenshot_35854.png](/images/screenshot_35854.png)![screenshot_4572.png](/images/screenshot_4572.png) ![screenshot_66902.png](/images/screenshot_66902.png) ![screenshot_20320.png](/images/screenshot_20320.png) ![screenshot_4554.png](/images/screenshot_4554.png) ![screenshot_4598.png](/images/screenshot_4598.png) ![screenshot_66925.png](/images/screenshot_66925.png) ![screenshot_20260.png](/images/screenshot_20260.png) ![screenshot_35807.png](/images/screenshot_35807.png) ![screenshot_4559.png](/images/screenshot_4559.png) ![screenshot_51345.png](/images/screenshot_51345.png) ![screenshot_20266.png](/images/screenshot_20266.png) ![screenshot_35845.png](/images/screenshot_35845.png) ![screenshot_4564.png](/images/screenshot_4564.png) ![screenshot_51372.png](/images/screenshot_51372.png) ![screenshot_20287.png](/images/screenshot_20287.png) ![screenshot_35853.png](/images/screenshot_35853.png) ![screenshot_4571.png](/images/screenshot_4571.png) ![screenshot_51387.png](/images/screenshot_51387.png)

## installation
* Install [Bodmer/TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) library and make sure examples are running.
* Download zip and move extraced directory to the arduino libraries folder or use the Library Manager and select `install from zip`
## test
* From the arduino file menu select examples TFTShape
