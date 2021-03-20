#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <zbar.h>
#include <iostream>
#include <chrono>

#define MEASURE_TIME
#define SHOW_VIDEO
#define DRAW_RECTANGLE

void draw_rectangle(const zbar::Symbol &code, cv::Mat &frame) {
  for (int i = 0; i < code.get_location_size(); i++) {
    auto p1 = cv::Point(code.get_location_x(i), 
                        code.get_location_y(i));
    auto p2 = cv::Point(code.get_location_x((i + 1) % 4),
                        code.get_location_y((i + 1) % 4));
    cv::line(frame, p1, p2, cv::Scalar(0, 0, 255), 3);
  }
}

int detect_codes(zbar::ImageScanner &scanner, cv::Mat &frame) {
  using namespace std;

#ifdef MEASURE_TIME
  auto start = chrono::high_resolution_clock::now();
#endif

  cv::Mat grey;
  cv::cvtColor(frame, grey, CV_BGR2GRAY);

  zbar::Image image(grey.cols,              // width
                    grey.rows,              // height
                    "Y800",                 // format
                    (uchar *)grey.data,     // data
                    grey.cols * grey.rows); // length
                    
  int n = scanner.scan(image);

#ifdef MEASURE_TIME
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << n << " codes (" << duration.count() << " ms):" << endl;
#endif

  for (auto code = image.symbol_begin(); code != image.symbol_end(); ++code) {
    cout << "    >> \"" << code->get_data() << "\"" << endl;

#if defined(SHOW_VIDEO) && defined(DRAW_RECTANGLE)
    draw_rectangle(*code, frame);
#endif
  }

  return n;
}

int main() {

  cv::VideoCapture capture(0);  // video camera #0
  if (!capture.isOpened()) return -1;

  zbar::ImageScanner scanner;
  scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 0);  // disable all symbologies
  scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);  // enable QR Code only

#ifdef SHOW_VIDEO
  cv::namedWindow("video", cv::WINDOW_AUTOSIZE);
#endif

  for (;;) {
    cv::Mat frame;
    capture >> frame;
    resize(frame, frame, cv::Size(320, 180), 0, 0, cv::INTER_CUBIC);
    
    detect_codes(scanner, frame);

#ifdef SHOW_VIDEO
    cv::imshow("video", frame);
#endif

    if (cv::waitKey(30) != -1) break;
  }

  return 0;
}
