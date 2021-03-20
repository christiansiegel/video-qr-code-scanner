# Video QR Code Scanner
Scan QR Codes from video stream.

## Dependencies
* [OpenCV](http://opencv.org/) (tested with 3.2.0)
* [ZBar bar code reader](http://zbar.sourceforge.net/) (tested with 0.10)

## Build
```bash
# Clone repository
git clone https://github.com/christiansiegel/video-qr-code-scanner.git
cd video-qr-code-scanner

# Create build directory
mkdir build && cd build

# Configure
cmake ..

# Build
make

# Run
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
    >> "http://www.qrstuff.com/"
```

## FAQ
### Install ZBar
```bash
wget -O zbar-0.10.tar.bz2  https://sourceforge.net/projects/zbar/files/zbar/0.10/zbar-0.10.tar.bz2/download
tar xf zbar-0.10.tar.bz2
cd zbar-0.10
CFLAGS="" ./configure --prefix=/usr/local --without-gtk --without-python --without-qt --disable-video
make
sudo make install
```
