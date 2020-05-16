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
Note that spaces are not allowed, so the following won't work
```
$ make clean
$ qmake CONFIG += consoleAppConf
$ make
```

## Running the tests

On command line, type in the following commands:
```
$ make clean
$ qmake CONFIG+=testConf
$ make
$ ./test
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

-l 'number'

set maximum number of pictures after processing(default is 25)

-d 'algorithm name'

restrict the use of an algorithm

-a

show names of all algorithms
```
$ ./ImageAugmentation -a
crop | hflip | vflip | rotate90 | rotate45 | dithering | gaussnoise | kuwahara | 
lightening | rgbtone | whiteblack | blur | negative | sharpen | embross | 
lightblur | lightsharpen | lightembross | gaussblur | randomcrop

```
-f 'format'

set format of processed images (png, jpeg, jpg, JPG, JPEG, gif, bmp, dib)

default is jpg

-o 'number'

set possible depths of overlay(default is 1)

-c 'config file path'

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

### Note
If source directory contains files in (png, jpeg, jpg, JPG, JPEG, gif, bmp, dib) format that are not images, application won't be able process to them (corresponding message will appear on the screen). 
But it will process all the other pictures in the directory.
## Built With

* [QtCreator](https://www.qt.io/)

