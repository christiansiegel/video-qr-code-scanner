#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <zbar.h>
#include <iostream>
#include <chrono>

#define MEASURE_TIME
#define SHOW_VIDEO
#define DRAW_RECTANGLE

void printSymbolFrame(const zbar::Symbol &symbol, cv::Mat &frame)
{
    int n = symbol.get_location_size();
    for(int i = 0; i < n; i++)
    {
        int x, y;
        x = symbol.get_location_x(i);
        y = symbol.get_location_y(i);
        auto p1 = cv::Point(x, y);

        x = symbol.get_location_x((i+1)%4);
        y = symbol.get_location_y((i+1)%4);
        auto p2 = cv::Point(x, y);

        cv::line(frame, p1, p2, cv::Scalar(0,0,255), 3);
    }
}

int processFrame(zbar::ImageScanner &scanner, cv::Mat &frame)
{
    using namespace std;

#ifdef MEASURE_TIME
    auto start = chrono::high_resolution_clock::now();
#endif

    cv::Mat grey;
    cv::cvtColor(frame, grey, CV_BGR2GRAY);

    zbar::Image image(
        grey.cols,              // width
        grey.rows,              // height
        "Y800",                 // format
        (uchar *)grey.data,     // data
        grey.cols * grey.rows   // length
    );

    int n = scanner.scan(image);

    for(auto symbol = image.symbol_begin();
        symbol != image.symbol_end();
        ++symbol)
    {
        cout << symbol->get_data() << endl;

#if defined (SHOW_VIDEO) && defined (DRAW_RECTANGLE)
        printSymbolFrame(*symbol, frame);
#endif
    }

#ifdef MEASURE_TIME
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << duration << " ms" << endl;
#endif

#ifdef SHOW_VIDEO
    cv::imshow("MyVideo", frame);
#endif

    return n;
}

int main(int argc, char* argv[])
{
    using namespace std;

    cv::VideoCapture capture(0); // video camera #0
    //cv::VideoCapture capture("rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov");

    if (!capture.isOpened())
        return -1;

    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 0); // disable all symbologies
    scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1); // enable QR Code only

    for(;;)
    {
        cv::Mat frame;
        capture >> frame;
        resize(frame, frame, cv::Size(320, 180), 0, 0, cv::INTER_CUBIC);
        processFrame(scanner, frame);

        if(cv::waitKey(25) >= 0)
            break;
    }

    return 0;
}
