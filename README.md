# Face Privacy Filter

![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![OpenCV](https://img.shields.io/badge/OpenCV-5C3EE8?style=flat-square&logo=opencv&logoColor=white)

A real-time webcam privacy filter built with C++ and OpenCV. It detects faces using a Haar Cascade model and applies interactive privacy effects to the live video feed.

## Features

- Webcam capture through OpenCV
- Haar Cascade face detection
- Runtime privacy modes:
  - Gaussian blur
  - Pixelation
  - black box
  - outline mode
- Trackbar-based mode switching while the feed is running

## Repository Layout

```text
src/                                  # C++ source
haarcascade_frontalface_default.xml   # face detector model
README.txt                            # original project notes
```

## How It Works

```mermaid
flowchart LR
    A["webcam frame"] --> B["face detection"]
    B --> C["privacy mode"]
    C --> D["filtered output"]
```

## Notes

This is a compact computer-vision utility focused on local privacy preservation. The camera stream is processed on-device; no cloud service is required.
