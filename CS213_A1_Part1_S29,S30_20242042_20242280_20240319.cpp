/*
File Name: CS213_A1_Part1_S29,S30_20242042_20242280_20240319.cpp
    Team Members:
    - Abdelrahman Waleed Shaaban (ID: 20240319) - Filter 1 & 4
    - Mohamed Hanafy Mahmoud Hussein (ID: 20242280) - Filter 3 & 6
    - Eslam Ezzat Rasmy Abusarea Dawood (ID: 20242042) - Filter 2 & 5
    Section: S29, S30
*/


#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;

//فلتر 1
Image filter_1(const Image& image) {
    Image newImage = image;
    for (int y = 0; y < newImage.height; y++) {
        for (int x = 0; x < newImage.width; x++) {
            unsigned char r = newImage.getPixel(x, y, 0);
            unsigned char g = newImage.getPixel(x, y, 1);
            unsigned char b = newImage.getPixel(x, y, 2);
            unsigned char gray = (r + g + b) / 3;
            newImage.setPixel(x, y, 0, gray);
            newImage.setPixel(x, y, 1, gray);
            newImage.setPixel(x, y, 2, gray);
        }
    }
    return newImage;
}
// فلتر 2
Image filter_2(const Image& image) {
    Image newImage = image;
    for (int y = 0; y < newImage.height; y++) {
        for (int x = 0; x < newImage.width; x++) {
            unsigned char r = newImage.getPixel(x, y, 0);
            unsigned char g = newImage.getPixel(x, y, 1);
            unsigned char b = newImage.getPixel(x, y, 2);
            unsigned char gray = (r + g + b) / 3;
            unsigned char avg = 128;
            unsigned char W_B = (gray >= avg) ? 255 : 0;
            newImage.setPixel(x, y, 0, W_B);
            newImage.setPixel(x, y, 1, W_B);
            newImage.setPixel(x, y, 2, W_B);
        }
    }
    return newImage;
}
// فلتر 3
Image filter_3(const Image& image) {
    Image newImage = image;
    for (int y = 0; y < newImage.height; y++) {
        for (int x = 0; x < newImage.width; x++) {
            unsigned char r = newImage.getPixel(x, y, 0);
            unsigned char g = newImage.getPixel(x, y, 1);
            unsigned char b = newImage.getPixel(x, y, 2);
            unsigned char Ir = 255 - r;
            unsigned char Ig = 255 - g;
            unsigned char Ib = 255 - b;
            newImage.setPixel(x, y, 0, Ir);
            newImage.setPixel(x, y, 1, Ig);
            newImage.setPixel(x, y, 2, Ib);
        }
    }
    return newImage;
}
//تغير حجم الصور عشان الدمج
Image resizeImage(const Image& img, int newWidth, int newHeight) {
    Image resized(newWidth, newHeight);

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int srcX = x * img.width / newWidth;
            int srcY = y * img.height / newHeight;

            for (int c = 0; c < img.channels; ++c) {
                resized(x, y, c) = img(srcX, srcY, c);
            }
        }
    }
    return resized;
}
// فلتر 4
Image mergeImages(const Image& img1, const Image& img2, int mode) {
    Image merged;

    if (mode == 0) {
        // دمج أفقي
        int targetHeight = max(img1.height, img2.height);
        int newWidth1 = img1.width * targetHeight / img1.height;
        int newWidth2 = img2.width * targetHeight / img2.height;
        Image resized1 = resizeImage(img1, newWidth1, targetHeight);
        Image resized2 = resizeImage(img2, newWidth2, targetHeight);
        merged = Image(newWidth1 + newWidth2, targetHeight);
        for (int y = 0; y < targetHeight; ++y) {
            for (int x = 0; x < newWidth1; ++x)
                for (int c = 0; c < img1.channels; ++c)
                    merged(x, y, c) = resized1(x, y, c);
            for (int x = 0; x < newWidth2; ++x)
                for (int c = 0; c < img2.channels; ++c)
                    merged(x + newWidth1, y, c) = resized2(x, y, c);
        }
    }
    else {
        // دمج راسي
        int targetWidth = max(img1.width, img2.width);
        int newHeight1 = img1.height * targetWidth / img1.width;
        int newHeight2 = img2.height * targetWidth / img2.width;
        Image resized1 = resizeImage(img1, targetWidth, newHeight1);
        Image resized2 = resizeImage(img2, targetWidth, newHeight2);
        merged = Image(targetWidth, newHeight1 + newHeight2);
        for (int y = 0; y < newHeight1; ++y)
            for (int x = 0; x < targetWidth; ++x)
                for (int c = 0; c < img1.channels; ++c)
                    merged(x, y, c) = resized1(x, y, c);
        for (int y = 0; y < newHeight2; ++y)
            for (int x = 0; x < targetWidth; ++x)
                for (int c = 0; c < img2.channels; ++c)
                    merged(x, y + newHeight1, c) = resized2(x, y, c);
    }
    return merged;
}
// فلتر 5
Image rotateImage(const Image& img, int angle) {
    Image rotated;
    if (angle == 90) {
        rotated = Image(img.height, img.width);
        for (int y = 0; y < img.height; ++y)
            for (int x = 0; x < img.width; ++x)
                for (int c = 0; c < img.channels; ++c)
                    rotated(img.height - 1 - y, x, c) = img(x, y, c);
    }
    else if (angle == 180) {
        rotated = Image(img.width, img.height);
        for (int y = 0; y < img.height; ++y)
            for (int x = 0; x < img.width; ++x)
                for (int c = 0; c < img.channels; ++c)
                    rotated(img.width - 1 - x, img.height - 1 - y, c) = img(x, y, c);
    }
    else if (angle == 270) {
        rotated = Image(img.height, img.width);
        for (int y = 0; y < img.height; ++y)
            for (int x = 0; x < img.width; ++x)
                for (int c = 0; c < img.channels; ++c)
                    rotated(y, img.width - 1 - x, c) = img(x, y, c);
    }

    return rotated;
}
//فلتر 6
void flipImage(Image& img, int mode) {
    if (mode == 0) {
        // Flip Horizontal
        for (int y = 0; y < img.height; ++y) {
            for (int x = 0; x < img.width / 2; ++x) {
                for (int c = 0; c < img.channels; ++c) {
                    swap(img(x, y, c), img(img.width - 1 - x, y, c));
                }
            }
        }
    }
    else {
        // Flip Vertical
        for (int x = 0; x < img.width; ++x) {
            for (int y = 0; y < img.height / 2; ++y) {
                for (int c = 0; c < img.channels; ++c) {
                    swap(img(x, y, c), img(x, img.height - 1 - y, c));
                }
            }
        }
    }
}

string pathi (){
        cout << "ENTER THE FILE NAME (without extension)... ";
        string name, namepath;
        cin >> name;

        cout << "Choose the image type:\n"
             << "1. PNG\n"
             << "2. JPG\n"
             << "3. BMP\n"
             << "4. JPEG\n"
             << "Enter choice: ";
        int choose;
        cin >> choose;

        switch(choose){
        case 1: namepath = name + ".png";cout<<"saving image...";break;
        case 2: namepath = name + ".jpg";cout<<"saving image..."; break;
        case 3: namepath = name + ".bmp";cout<<"saving image..."; break;
        case 4: namepath = name + ".jpeg";cout<<"saving image..."; break;
        default:
            cout << "Invalid choose Saving as .png by default.\n";
            namepath = name + ".png";
        }
        return namepath;


}

//المنيو
int main() {
    cout << "=====================================\n";
    cout << "   Welcome to Photo Editor Program! \n";
    cout << "=====================================\n";

    string path;
    cout << "Enter the image path: ";
    cin >> path;

    Image img(path);

    int choice;
    do {
        cout << "\nChoose an option:\n";
        cout << "1. Grayscale\n";
        cout << "2. Black & White\n";
        cout << "3. Invert Image\n";
        cout << "4. Merge Two Images\n";
        cout << "5. Flip Image (Horizontal / Vertical)\n";
        cout << "6. Rotate Image (90°, 180°, 270°)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Applying Grayscale...\n";
            {
            Image newImg = filter_1(img);
            newImg.saveImage(pathi());
            }
            break;

        case 2:
            cout << "Applying Black & White...\n";
            {
            Image newImg = filter_2(img);
            newImg.saveImage(pathi());
            }
            break;

        case 3:
            cout << "Applying Invert Image...\n";
            {
            Image newImg = filter_3(img);
            newImg.saveImage(pathi());
            }
            break;

            case 4: {
                cout << "Enter second image path: ";
                string path2;
                cin >> path2;
                Image img2(path2);

                int mode;
                cout << "Enter 0 for Horizontal merge or 1 for Vertical merge: ";
                cin >> mode;

                cout << "Merging images...\n";
                Image merged = mergeImages(img, img2, mode);
                merged.saveImage(pathi());
                break;
            }

            case 5: {
                int mode;
                cout << "Enter 0 for Horizontal, 1 for Vertical: ";
                cin >> mode;
                cout << "Flipping image...\n";
                flipImage(img, mode);
                img.saveImage(pathi());
                break;
            }

            case 6: {
                int angle;
                cout << "Enter angle (90, 180, 270): ";
                cin >> angle;
                cout << "Rotating image...\n";
                Image rotated = rotateImage(img, angle);
                rotated.saveImage(pathi());
                break;
            }

            case 0:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}