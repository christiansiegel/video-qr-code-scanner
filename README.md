# Video QR Code Scanner
Scan QR Codes from video stream.

## Dependencies
* [OpenCV](http://opencv.org/) (tested with 3.2.0)
* [ZBar bar code reader](http://zbar.sourceforge.net/) (tested with 0.10)

## Build
```
git clone https://github.com/christiansiegel/video-qr-code-scanner.git
cd video-qr-code-scanner
mkdir build
cd build
cmake ..
make
./video-qr-code-scanner
```

## Example Output
All codes detected in a video frame are printed, e.g.:

![video frame](doc/frame.png "Video Frame")

```
5 codes (18 ms):
    >> "Ver1"
    >> "http://en.m.wikipedia.org/"
    >> "http://www.shopify.com/"
    >> "Hello :)"
    >> http://www.qrstuff.com/"
```

## FAQ
### Install ZBar
```
wget http://downloads.sourceforge.net/zbar/0.10/zbar-0.10.tar.bz2
tar xf zbar-0.10.tar.bz2 
cd zbar-0.10
export CFLAGS=""
./configure --prefix=/usr/local --without-gtk --without-python --disable-video
make
sudo make install
```
