# Image Augmentation

Image augmentation artificially creates training images through different ways of processing or combination of multiple processing, such as rotation, flips, random crop and gaussian noise, etc.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine. 

### Prerequisites

Use at least Qt version 4.x and C++17

[Download Qt](https://www.qt.io/download)


### Installing

A step by step series of examples that tell you how to get the application running

Console application

On command line, type in the following commands:
```
$ make clean
$ qmake CONFIG+=consoleAppConf
$ make
```

Graphic application

On command line, type in the following commands:
```
$ make clean
$ qmake CONFIG+=GUIConf
$ make
```

Note that spaces are not allowed, so the following won't work
```
$ make clean
$ qmake CONFIG += consoleAppConf
$ make
```
## Usage Tutorial
Provide source image which has one of the following formats: png, jpeg, jpg, JPG, JPEG, gif, bmp, dib

Or directory (in this case all the images in this directory with the given formats will be proccesed)

Provide destination directory
```
$ ./ImageAugmentation /home/user/Pictures/example.gif /home/user/TempDir
$ ./ImageAugmentation /home/user/Pictures /home/user/TempDir
``` 
Console application is provided with several keys:

* -l 'number'

set maximum number of pictures after processing(default is 25)

* -d 'algorithm name'

restrict the use of an algorithm

* -a

show names of all algorithms
```
$ ./ImageAugmentation -a
crop | hflip | vflip | rotate90 | rotate45 | dithering | gaussnoise | kuwahara | 
lightening | rgbtone | whiteblack | blur | negative | sharpen | embross | 
lightblur | lightsharpen | lightembross | gaussblur | randomcrop

```
* -f 'format'

set format of processed images (png, jpeg, jpg, JPG, JPEG, gif, bmp, dib), default is jpg

* -o 'number'

set possible depths of overlay(default is 1)

* -c 'config file path'

set config file 

Example 1:
```
$ ./ImageAugmentation /home/user/Pictures /home/user/TempDir -d crop -d lightsharpen -o 3 -o 4 -l 8

```
This will

1) Take all images in /Pictures directory

2) 3 or 4 distinct algorithms(except for crop and lightsharpen) will be apllied on each image

3) No more than 8 images will be created from each source image in the directory

For example if /Pictures contains 3 images then in total it will create 24 images 

Example 2:
```
$ ./ImageAugmentation /home/user/Pictures/example.bmp /home/user/TempDir -f gif

```
This will

1) Take example.bmp image

2) Each algorithm will be applied but only once

3) Processed images will have gif format

This will create 25 distinct pictures 

(rotate90 and rotate45 both give 2 different images(rotation clockwise and counterclockwise), 2 types of gaussian noise) 

Example 3:
```
$ ./ImageAugmentation /home/user/Pictures/example.bmp /home/user/TempDir -f gif -d 2 -c /home/user/configfile.json

```
This will

1) Take example.bmp image

2) Only algorithms included in the config file with given configuration will be used
 
3) 2 distinct algorithms will be apllied on each image

4) Processed images will have gif format

For example if config file contained 4 distinct algorithms, this will create 4*3 = 12 images in total

### Config File
Example:
```
{
	"crop": {
		"upperLeftXInPercent": 10,
                "upperLeftYInPercent": 15,
                "downRightXInPercent": 30,
		"downRightYInPercent": 40
        },
	"blur": {
		"degree": 15
	},
	"negative": {
		"degree": 15
	},
	"sharpen": {
		"degree": 10
	},
	"embross": {
		"degree": 30
	},
        "lightBlur": {
		"degree": 15
	},
	"lightSharpen": {
		"degree": 15
	},
	"lightEmbross": {
		"degree": 15
	},
        "gaussBlur": {
		"degree": 15
	},
	"kuwahara": {
		"degreeOfBlur": 12
	},
	"lightening": {
		"degreeOfLightening": 40
	},
	"randomCrop": {
		"upperLeftXInPercent": 10,
                "upperLeftYInPercent": 15
        },
	"gaussiannoise": {
		"degreeOfNoise": 70,
		"mono": true
	},
	"blueRGBTone": {
		"degreeOfTone": 60
	},
	"redRGBTone": {
		"degreeOfTone": 50
	},
        "greenRGBTone": {
		"degreeOfTone": 40
	},
	"enable": [
		"dithering",
		"whiteblack",
		"vflip",
		"hflip",
		"rotate90Clockwise",
                "rotate90Counterclockwise",
                "rotate45Clockwise",
                "rotate45Counterclockwise"
	]
}
```

### Note
If source directory contains files in (png, jpeg, jpg, JPG, JPEG, gif, bmp, dib) format that are not images, application won't be able process to them (corresponding message will appear on the screen). 
But it will process all the other pictures in the directory.

Gaussian Blur and Kuwahara take a long time to be processed.

Some algorithms are not compatible with small pictures (less than 100 pixels in width or height)
## Built With

* [QtCreator](https://www.qt.io/)
## Description of the algorithms 
Source Image

![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/animal.jpg)
### Crop
The algorithm that cuts out part of the image: the user sets the relative size of the imageand the location of the upper left corner of the cropped image as a percentage of the size of the entire image


![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/animal_crop.jpg)
### Random crop 
An algorithm that randomly selects the position of the black square of a given relative size that covers part of the image

![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/cleverCrop.jpg)

### Dithering 
An algorithm that expresses colors that do not exist in a given palette through errors already known with dispersion

![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/ditheredAnimal.jpg)

### Gaussian Noise
An algorithm that applies color or black and white noise with given degree (from 0 to 100) to an image depending on the mode selected by the user


![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/Gauss.jpg)

### Horizontal Flip
Algorithm that reflects the transmitted image relative to the y-axis

![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/HorizontalFlip.jpg)

### Kuwahara
An algorithm that applies a blur filter to an image with given degree (from 0 to 30), creating the effect of a picture drawn in rough strokes

![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/Kuwahara.jpg)

### Lightening
The algorithm that brightens the image with given degree (from 0 to 255)

![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/Lightening.jpg)

### Matrix Convolution
A series of matrix convolution algorithms that passes through the image with a filter matrix and overlays one of the filters selected by the user: blur, negative, sharpen, embross, lightBlur, lightSharpen, lightEmbross, gaussBlur. Also user can tune the degree of Gauss Blur from 0 to 70

Embross
![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/ConvolutionEmbross.jpg)

Gaussian Blur
![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/GaussianBlur.jpg)

Negative
![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/Negative.jpg)

### RGB Tone
An algorithm that increments with given degree one of the components of an RGB vector. Thus, the image becomes more reddish, greenish or bluish

![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/RGBTone.jpg)

### Rotate 45
An algorithm that rotates an image 45 degrees clockwise or counterclockwise, depending on the user's choice. Pixel stretching is applied to the corners of the image. Thus, the picture looks holistic.

![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/Rotate45.jpg)

### Rotate 90
An algorithm that rotates an image 90 degrees clockwise or counterclockwise, depending on the user's choice.

![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/Rotate90.jpg)

### Vertical Flip
Algorithm that reflects the transmitted image relative to the x-axis

![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/VerticalFlip.jpg)

### White Black
An algorithm that converts an image to black and white palette

![Image alt](https://github.com/hwanglight/ImageAugmentation/raw/master/samples/SamplesGit/WhiteBlack.jpg)
