// FCAI – Structured Programming – 2024 - Assignment 3
// Program Name: CS112_A3_Part2B_S15_S16_20231178_20230142_20230495.cpp
// Program Description: This program allows the user to upload and apply on it diffrent 15 filters and the user can choose more than one image to apply the filter needed, the user can apply diffrent filters on the same image, it allows the user to save the image too. 
// Last Modification Date: 13/4/2024
// Author1 and ID and Group: Menna Abdallah Helmi, ID: 20231178, she did Invert Image colors filter & Rotate Image filter & Blur filter & Frame filter & Infrared Filter.
// Email: mennaabdallah2.2.6@gmail.com
// Author2 and ID and Group: Roaa Mohammed Sayed, ID: 20230142, she did Grayscale Conversion filter & Darken and Lighten Image & Edge detection filter & Merge Filter & Purpule look Filter. 
//Email: roaamuhamed312@gmail.com
// Author3 and ID and Group: Yosef Hamdy Aboelmaaty, ID: 20230495, He did Black and White filter & Flip Image filter & crop image filter & resize filter & Good natural sunlight filter. 
// Email: yosefhamdy4102@gmail.com
// Teaching Assistant: Belal Tarek Hassan


#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;
// Function to rotate the image by 90 degrees clockwise
Image *rotate90(Image *image){
    // Create a new image with swapped dimensions for rotation
    Image *rotated = new Image(image->height, image->width);
    for (int i = 0; i < image->width; ++i) {
        for (int j = 0; j < image->height; ++j) {
            for(int c = 0; c < 3; ++c){ // Assuming 3 channels for RGB
                rotated->setPixel((image->height - 1) - j, i, c, image->getPixel(i,j,c));
            }
        }
    }
    return rotated;// Return the rotated image
}
// Function to handle rotation options (90, 180, 270 degrees)
Image *rotatedDriver(Image *current){
    int choice;
    do {cout << "Please choose a number:\n(1) Rotate by 90 degrees.\n(2) Rotate by 180 degrees.\n(3) Rotate by 270 degrees.\n";
        cin >> choice;
    } while (choice != 1 && choice != 2 && choice != 3);


    Image *rotated = 0;
    if(choice == 1){
        rotated = rotate90(current);  // Rotate by 90 degrees
    }
    else if(choice == 2){
        rotated = rotate90(current);  //Rotate by 90 degrees twice for 180 degrees rotation
        Image *tmp = rotated;
        rotated = rotate90(rotated);
        delete tmp;
    }
    else{
        rotated = rotate90(current);  // Rotate by 90 degrees thrice for 270 degrees rotation
        Image *tmp = rotated;
        rotated = rotate90(rotated);
        delete tmp;
        tmp = rotated;
        rotated = rotate90(rotated);
        delete tmp;
    }

    return rotated;// Return the rotated image
}
// Function to invert colors of the image
Image *invert(Image *image){
    // Create a new image for storing inverted colors
    Image *inverted = new Image(image->width, image->height);
    for (int i = 0; i < image->width; ++i) {
        for (int j = 0; j < image->height; ++j){
            for(int o = 0; o < image->channels; ++o){
                inverted->getPixel(i, j, o) = 255 - image->getPixel(i, j, o); // Invert color values
            }
        }
    }
    return inverted;// Return the inverted image
}


// Function to apply black and white filter to the image
void applyBlackAndWhiteFilter(Image *image) {
    const int BLACK_THRESHOLD = 128; // Threshold for converting to black and white

    for (int o = 0; o < image->width; ++o) {
        for (int p = 0; p < image->height; ++p) {
            // Convert pixel to black or white based on intensity
            int intensity = (image->getPixel(o, p, 0) + image->getPixel(o, p, 1) + image->getPixel(o, p, 2)) / 3;
            if (intensity < BLACK_THRESHOLD) {
                image->getPixel(o, p, 0) = 0; // Set Red channel to 0 (black)
                image->getPixel(o, p, 1) = 0; // Set Green channel to 0 (black)
                image->getPixel(o, p, 2) = 0; // Set Blue channel to 0 (black)
            } else {
                image->getPixel(o, p, 0) = 255; // Set Red channel to 255 (white)
                image->getPixel(o, p, 1) = 255; // Set Green channel to 255 (white)
                image->getPixel(o, p, 2) = 255; // Set Blue channel to 255 (white)
            }
        }
    }
}
// Function to flip the image horizontally
void flipHorizontal(Image *image) {
    int width = image->width;
    int height = image->height;

    // Iterate through each row
    for (int p = 0; p < height; ++p) {
        // Swap pixels from left to right
        for (int o = 0; o < width / 2; ++o) {
            for (int q = 0; q < 3; ++q) { // 3 for RGB channels
                swap(image->getPixel(o, p, q), image->getPixel(width - 1 - o, p, q));// Swap pixels
            }
        }
    }
}
// Function to flip the image vertically
void flipVertical(Image *image) {
    int width = image->width;
    int height = image->height;

    // Iterate through each column
    for (int o = 0; o < width; ++o) {
        // Swap pixels from top to bottom
        for (int p = 0; p < height / 2; ++p) {
            for (int q = 0; q < 3; ++q) { // 3 for RGB channels
                swap(image->getPixel(o, p, q), image->getPixel(o, height - 1 - p, q));// Swap pixels
            }
        }
    }
}
// Function to handle flip options (horizontal or vertical)
void driveFliping(Image *image){
    char flip_choice;
    bool valid_choice = false;

    while (!valid_choice) {
        cout << "Choose flip direction (h for horizontal, v for vertical): ";
        cin >> flip_choice;

        if (flip_choice == 'h' || flip_choice == 'H') {
            flipHorizontal(image);
            valid_choice = true;
        } else if (flip_choice == 'v' || flip_choice == 'V') {
            flipVertical(image);
            valid_choice = true;
        } else {
            cout << "Invalid choice. Please choose either 'h' for horizontal or 'v' for vertical flip." << endl;
        }
    }
}
// Function to convert the image to grayscale
void convertToGrayscale(Image *image) {
    for (int i = 0; i < image->width; ++i) {
        for (int j = 0; j < image->height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image->channels; ++k) {
                avg += image->getPixel(i, j, k);
            }
            avg /= 3;// Calculate average intensity
            for (int k = 0; k < image->channels; ++k) {// Set all channels to average intensity
                image->getPixel(i, j, k) = avg;
            }
        }
    }
}
// Function to darken the image
void darkenImage(Image *image) {
    for (int i = 0; i < image->width; ++i) {
        for (int j = 0; j < image->height; ++j) {
            for (int k = 0; k < image->channels; ++k) {
                int newValue = image->getPixel(i, j, k) * 0.5; // Multiply pixel value by 0.5 to darken
                if (newValue < 0) newValue = 0; // Ensure value doesn't go below 0
                image->getPixel(i, j, k) = newValue;// Update pixel value

            }
        }
    }
}
// Function to lighten the image
void lightenImage(Image *image) {
    for (int i = 0; i < image->width; ++i) {
        for (int j = 0; j < image->height; ++j) {
            for (int k = 0; k < image->channels; ++k) {
                int newValue = image->getPixel(i, j, k) * 1.5;// Multiply pixel value by 1.5 to lighten
                if (newValue > 255) newValue = 255; // Ensure value doesn't exceed 255
                image->getPixel(i, j, k) = newValue;// Update pixel value

            }
        }
    }
}
// Function to handle darken/lighten options
void DarLighDriver(Image *image){
    int choice;
    bool validChoice = false;
    while (!validChoice) {
        cout << "Choose a filter:" << endl;
        cout << "1. Darken the image" << endl;
        cout << "2. Lighten the image" << endl;
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;

        switch (choice) {
            case 1:
                darkenImage(image);
                cout << "Image darkened successfully." << endl;
                validChoice = true;
                break;
            case 2:
                lightenImage(image);
                cout << "Image lightened successfully." << endl;
                validChoice = true;
                break;
            default:
                cerr << "Invalid choice. Please enter 1 or 2." << endl;
        }
    }
}
// Function to load an image
void loadImgDriver(Image *img){
    while(true){
        cout << "Enter the full path to the image file: ";
        cin >> ws;

        string filename;
        getline(cin, filename);

        try {
            img->loadNewImage(filename); // Load the image from file
            cout << "Image loaded successfully!\n";
            break;
        } catch (exception &e) {
            cout << e.what() << '\n'; // Display error if loading fails
        }
    }
}
// Function to save an image
void saveImgDriver(Image *img){
    while(true){
        cout << "Pls enter image name to store new image and specify extension (.jpg, .bmp, .png, .tga ,.jpeg):\n";
        string outputFilename;
        cin >> outputFilename;
        try {
            img->saveImage(outputFilename);
            cout << "Image saved successfully as "<<outputFilename<<endl;
            break;
        } catch (exception &e) {
            cout << e.what() << '\n';
        }
    }
}
// function to blur an image
void blur(Image *image){
    for (int i = 0; i < image->width; ++i) {
        for (int j = 0; j < image->height; ++j) {
            int r = image->getPixel(i, j, 0);
            int g = image->getPixel(i, j, 1);
            int b = image->getPixel(i, j, 2);
            int counter = 1;
            const int LIMIT = 20;
        
            for(int x = i-1; x >= max(i - LIMIT, 0); --x){
                r += image->getPixel(x, j, 0);
                g += image->getPixel(x, j, 1);
                b += image->getPixel(x, j, 2);
                counter++;
            }
            

            for(int x = i+1; x < min(i + LIMIT + 1, image->width); ++x){
                r += image->getPixel(x, j, 0);
                g += image->getPixel(x, j, 1);
                b += image->getPixel(x, j, 2);
                counter++;
            }               
            

            for(int x = j-1; x >= max(j - LIMIT, 0); --x){
                r += image->getPixel(i, x, 0);
                g += image->getPixel(i, x, 1);
                b += image->getPixel(i, x, 2);
                counter++;
            }                 
            

            for(int x = j+1; x < min(j+LIMIT + 1, image->height); ++x){
                r += image->getPixel(i, x, 0);
                g += image->getPixel(i, x, 1);
                b += image->getPixel(i, x, 2);
                counter += 1; 
            }                

            for(int x = i - 1, y = j + 1; x >= max(i - LIMIT, 0) && y < min(j + LIMIT + 1, image->height); --x, ++y){
                r += image->getPixel(x, y, 0);
                g += image->getPixel(x, y, 1);
                b += image->getPixel(x, y, 2);
                counter += 1;
            }

            for(int x = i - 1, y = j - 1; x >= max(i - LIMIT, 0) && y >= max(j - LIMIT, 0); --x, --y){
                r += image->getPixel(x, y, 0);
                g += image->getPixel(x, y, 1);
                b += image->getPixel(x, y, 2);
                counter += 1;
            }       

            for(int x = i + 1, y = j + 1; x < min(i + LIMIT + 1, image->width) && y < min(j + LIMIT + 1, image->height); ++x, ++y){
                r += image->getPixel(x, y, 0);
                g += image->getPixel(x, y, 1);
                b += image->getPixel(x, y, 2);
                counter += 1;               
            }

            for(int x = i + 1, y = j - 1; x < min(i + LIMIT + 1, image->width) && y >= max(j - LIMIT, 0); ++x, --y){
                r += image->getPixel(x, y, 0);
                g += image->getPixel(x, y, 1);
                b += image->getPixel(x, y, 2);
                counter += 1;               
            }
            
            image->getPixel(i,j,0)=round((double)r/counter);
            image->getPixel(i,j,1)=round((double)g/counter);
            image->getPixel(i,j,2)=round((double)b/counter);
        }
    }
}
// function to apply a simple frame
Image *simple_frame(Image *image){
    int frame_size = 4;
    int n_width = image->width + 2 * frame_size;
    int n_height = image->height + 2 * frame_size;

    // Define a color 
    const int PINK_R = 255;   // Red component
    const int PINK_G = 128;   // Green component
    const int PINK_B = 0;   // Blue component

    // Create a new image with the frame
    Image *framed = new Image(n_width, n_height);

    // Draw the frame
    for (int y = 0; y < n_height; ++y) {
        for (int x = 0; x < n_width; ++x) {
            if (x < frame_size || y < frame_size || x >= n_width - frame_size || y >= n_height - frame_size) {
                // Set the frame color to pink
                framed->getPixel(x, y, 0) = PINK_R;
                framed->getPixel(x, y, 1) = PINK_G;
                framed->getPixel(x, y, 2) = PINK_B;
            } else {
                // Copy the pixel from the original image
                int original_x = x - frame_size;
                int original_y = y - frame_size;

                framed->getPixel(x,y,0) = image->getPixel(original_x,original_y,0);
                framed->getPixel(x,y,1) = image->getPixel(original_x,original_y,1);
                framed->getPixel(x,y,2) = image->getPixel(original_x,original_y,2);
            }
        }
    }

    return framed;
}
// function to apply a fancy frame 
void fancy_frame(Image *image){
    const int FRAME_SIZE = 2;
    const int MARGINS = 5;
    for(int i = 0; i < image->width; i++){
        for(int j = 0; j < FRAME_SIZE;j++){
            image->getPixel(i,j + MARGINS,0) = 255;
            image->getPixel(i,j + MARGINS,1) = 255;
            image->getPixel(i,j + MARGINS,2) = 255;
        }
    }
    for(int i = 0; i < image->width; i++){
        for(int j = 0; j < FRAME_SIZE; j++){
            image->getPixel(i, image->height - MARGINS - j,0) = 255;
            image->getPixel(i, image->height - MARGINS - j,1) = 255;
            image->getPixel(i, image->height - MARGINS - j,2) = 255;
        }
    }
    for(int j = 0; j < image->height; j++){
        for(int i = 0; i < FRAME_SIZE; i++){
            image->getPixel(i + MARGINS, j, 0) = 255;
            image->getPixel(i + MARGINS, j, 1) = 255;
            image->getPixel(i + MARGINS, j, 2) = 255;
        }
    }
    for(int j = 0; j < image->height; j++){
        for(int i = 0; i < FRAME_SIZE; i++){
            image->getPixel(image->width - MARGINS - i, j, 0) = 255;
            image->getPixel(image->width - MARGINS - i, j, 1) = 255;
            image->getPixel(image->width - MARGINS - i, j, 2) = 255;
        }
    }
}
// function to drive the frame filter
Image *frame_driver(Image *image){
    int choice;
    do {
        cout << "Please choose a number:\n(1) Apply a simple frame.\n(2) Apply a fancy frame.\n";
        cin >> choice;
    } while (choice != 1 && choice != 2);

    Image *framed = 0;
    if(choice == 1){
        framed = simple_frame(image);
    }
    else{
        fancy_frame(image);
        framed = simple_frame(image);
    }
    return framed;
}
// Function to show integer input
int getValidIntegerInput(const string& prompt, int lowerBound, int upperBound) {
    int input;
    while (true) {
        cout << prompt;
        if (!(cin >> input)) { // Check if input is not an integer
            cout << "Invalid input. Please enter a valid integer." << endl;
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input


        } else if (input < lowerBound || input > upperBound) { // Check if input is within bounds


            cout << "Input out of bounds. Please enter a number between " << lowerBound << " and " << upperBound << "." << endl;
        } else {
            break; // Input is valid
        }
    }
    return input;
}
// function to drive cropping an image
void cropping_driver(Image *image) {
    // Get image dimensions
    int original_width = image->width;
    int original_height = image->height;

    // Variables to store cropping dimensions
    int x, y, width, height;

    // Ask the user for cropping dimensions until true dimensions are provided
    x = getValidIntegerInput("Enter the point (x) of the upper-left corner : ", 0, original_width);
    y = getValidIntegerInput("Enter the point (y) of the upper-left corner : ", 0, original_height);
    width = getValidIntegerInput("Enter the width to crop: ", 1, original_width - x);
    height = getValidIntegerInput("Enter the height to crop: ", 1, original_height - y);

    // Create a new image to store the cropped area
    Image cropped_image(width, height);

    // Copy pixels from the original image to the cropped image
    for (int g = 0; g < width; ++g) {
        for (int h = 0; h < height; ++h) {
            // Check bounds to avoid segmentation fault
            if (x + g < original_width && y + g < original_height) {
                cropped_image(g, h, 0) = image->getPixel(x + g, y + h, 0);
                cropped_image(g, h, 1) = image->getPixel(x + g, y + h, 1);
                cropped_image(g, h, 2) = image->getPixel(x + g, y + h, 2);
            }
        }
    }
    *image = cropped_image;
}
// Function to resize the image
void resizeImage(Image& image, int new_width, int new_height) {
    // Create a new image with the true dimensions
    Image resized_image(new_width, new_height);

    // Calculate measures for width and height
    float width_scale = static_cast<float>(image.width) / new_width;
    float height_scale = static_cast<float>(image.height) / new_height;

    // Iterate over each pixel in the resized image
    for (int m = 0; m < new_width; ++m) {
        for (int n = 0; n < new_height; ++n) {
            // Calculate corresponding pixel coordinates in the original image
            int original_x = static_cast<int>(m * width_scale);
            int original_y = static_cast<int>(n * height_scale);

            // Set the pixel values in the resized image
            resized_image(m, n, 0) = image(original_x, original_y, 0);
            resized_image(m, n, 1) = image(original_x, original_y, 1);
            resized_image(m, n, 2) = image(original_x, original_y, 2);
        }
    }

    // Update the original image with the resized image
    image = resized_image;
}
// fuction to drive resizing an image
void resize_driver(Image *image) {
    // Loop until the user enters a valid choice
    char choice;
    bool valid_choice = false;
    do {
        cout << "Do you want to resize the image by dimensions (1) or by ratio (2)? ";
        cin >> choice;
        // Convert choice to lowercase
        choice = tolower(choice);
        if (choice == '1' || choice == '2') {
            valid_choice = true;
        } else {
            cout << "Invalid choice. Please enter '1' for  dimensions or '2' for ratio." << endl;
        }
    } while (!valid_choice);

    if (choice == '1') {
        // Resize by dimensions
        int new_width, new_height;
        // Loop until the user enters valid dimensions (numbers)
        do {
            cout << "Enter the new width: ";
            cin >> new_width;
            if (cin.fail() || new_width <= 0 || new_width > 10000) {
                cout << "Invalid input. Please enter a valid number between 1 and 10000." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (new_width <= 0 || new_width > 10000);

        do {
            cout << "Enter the new height: ";
            cin >> new_height;
            if (cin.fail() || new_height <= 0 || new_height > 10000) {
                cout << "Invalid input. Please enter a valid number between 1 and 10000." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (new_height <= 0 || new_height > 10000);

        resizeImage(*image, new_width, new_height);
    } else if (choice == '2') {
        // Resize by ratio
        float ratio;
        // Loop until the user enters a valid ratio (number)
        do {
            cout << "Enter the resizing ratio (0 for no change): ";
            cin >> ratio;
            if (cin.fail() || ratio <= 0) {
                cout << "Invalid input. Please enter a valid number greater than 0." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (ratio <= 0);

        int new_width = static_cast<int>(image->width * ratio);
        int new_height = static_cast<int>(image->height * ratio);
        resizeImage(*image, new_width, new_height);
    }
}
// Function to resize an image
void resizeImage(Image*& image, int newWidth, int newHeight) {
    Image* resizedImage = new Image(newWidth, newHeight);

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            for (int c = 0; c < image->channels; ++c) {
                int originalX = x * image->width / newWidth;
                int originalY = y * image->height / newHeight;
                resizedImage->setPixel(x, y, c, image->getPixel(originalX, originalY, c));
            }
        }
    }
    // Free memory of the original image
    delete image;
    // Assign the resized image to the original pointer
    image = resizedImage;
}
// Function to merge two images by resizing the smaller image to the dimensions of the largest image
Image* mergeWithResize(const Image& img1, const Image& img2) {
    // Get dimensions of the larger image
    int mergedWidth = max(img1.width, img2.width);
    int mergedHeight = max(img1.height, img2.height);

    // Resize images to the dimensions of the largest image
    Image* resizedImg1 = new Image(img1);
    Image* resizedImg2 = new Image(img2);

    if (img1.width != img2.width || img1.height != img2.height) {
        resizeImage(resizedImg1, mergedWidth, mergedHeight);
        resizeImage(resizedImg2, mergedWidth, mergedHeight);
    }

    // Merge images
    Image* mergedImage = new Image(mergedWidth, mergedHeight);

    for (int y = 0; y < mergedHeight; ++y) {
        for (int x = 0; x < mergedWidth; ++x) {
            for (int c = 0; c < mergedImage->channels; ++c) {
                int pixelValue = (resizedImg1->getPixel(x, y, c) + resizedImg2->getPixel(x, y, c)) / 2;
                mergedImage->setPixel(x, y, c, pixelValue);
            }
        }
    }
    // Free memory of resized images
    delete resizedImg1;
    delete resizedImg2;

    return mergedImage;
}
// Function to merge two images by taking only the common area
Image* mergeCommonArea(const Image& img1, const Image& img2) {
    // Get dimensions of the common area
    int commonWidth = min(img1.width, img2.width);
    int commonHeight = min(img1.height, img2.height);

    // Merge images taking only the common area
    Image* mergedImage = new Image(commonWidth, commonHeight);

    for (int y = 0; y < commonHeight; ++y) {
        for (int x = 0; x < commonWidth; ++x) {
            for (int c = 0; c < mergedImage->channels; ++c) {
                int pixelValue = (img1.getPixel(x, y, c) + img2.getPixel(x, y, c)) / 2;
                mergedImage->setPixel(x, y, c, pixelValue);
            }
        }
    }

    return mergedImage;
}
// function to drive merging an image
void merge_driver(Image *image) {
    Image* img1 = image;
    Image* img2 = nullptr;
    string filename2;
    int mergeOption = 0;

    // Load second image
    while (true) {
        cout << "Enter the full path to the second image file: ";
        cin >> ws;
        getline(cin, filename2); // Allowing spaces in file paths

        try {
            img2 = new Image(filename2);
            cout << "Second image loaded successfully." << endl;
            break;
        } catch (invalid_argument& e) {
            cerr << e.what() << endl; // Display the error message
        }
    }

    // Choose merge option
    while (mergeOption != 1 && mergeOption != 2) {
        cout << "Choose merge option:" << endl;
        cout << "1) Resize smaller image to largest image and merge" << endl;
        cout << "2) Merge common area" << endl;
        cout << "Enter option (1 or 2): ";
        cin >> mergeOption;

        if (mergeOption != 1 && mergeOption != 2) {
            cout << "Invalid option. Please enter 1 or 2." << endl;
        }
    }

    // Merge images
    Image* merged = nullptr;
    if (mergeOption == 1) {
        // Resize smaller image to largest image and then merge
        merged = mergeWithResize(*img1, *img2);
    } else {
        // Merge common area of images
        merged = mergeCommonArea(*img1, *img2);
    }
    // Free memory of images
    delete img1;
    delete img2;
    *image = *merged;
    delete merged;
}
// Function to perform edge detection using the Sobel operator
void detectEdges(Image* image) {
    Image edges(image->width, image->height); // Create a new image for storing the edges

    int gxMatrix[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gyMatrix[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int x = 1; x < image->width - 1; ++x) {
        for (int y = 1; y < image->height - 1; ++y) {
            int gx = 0;
            int gy = 0;

            // Apply the Sobel operator matrices to calculate gx and gy
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    gx += gxMatrix[i + 1][j + 1] * image->getPixel(x + i, y + j, 0);
                    gy += gyMatrix[i + 1][j + 1] * image->getPixel(x + i, y + j, 0);
                }
            }

            // Calculate the magnitude of the gradient
            int magnitude = sqrt(gx * gx + gy * gy);

            if (magnitude > 128) {
                // Set pixel to black
                edges.setPixel(x, y, 0, 0);
                edges.setPixel(x, y, 1, 0);
                edges.setPixel(x, y, 2, 0);
            } else {
                // Set pixel to white
                edges.setPixel(x, y, 0, 255);
                edges.setPixel(x, y, 1, 255);
                edges.setPixel(x, y, 2, 255);
            }
        }
    }

    *image = edges; // Update the original image with the detected edges
}
// function to drive edge detection
void edgeDetection_driver(Image *image) {
    convertToGrayscale(image);
    // Perform edge detection
    detectEdges(image);
}
// Function to apply sunlight filter to the image
void applySunlightFilter(Image* image) {
    for (int y = 0; y < image->height; ++y) {
        for (int x = 0; x < image->width; ++x) {
            unsigned char r = image->getPixel(x, y, 0);
            unsigned char g = image->getPixel(x, y, 1);
            unsigned char b = image->getPixel(x, y, 2);

            r = min(static_cast<int>(r) + 50, 255);
            g = min(static_cast<int>(g) + 50, 255);
            b = max(static_cast<int>(b) - 10, 0);

            image->setPixel(x, y, 0, r);
            image->setPixel(x, y, 1, g);
            image->setPixel(x, y, 2, b);
        }
    }
}
// Function to add a hint of purple tint to the image
void addHintOfPurple(Image* image) {
    for (int i = 0; i < image->width; ++i) {
        for (int j = 0; j < image->height; ++j) {
            // Increase red and blue channels slightly
            (*image)(i, j, 1) = (*image)(i, j, 1) * 0.75; // Red
        }
    }
}
void infrared (Image *image){
    for (int i = 0; i < image->width; ++i) {
        for (int j = 0; j < image->height; ++j) {
            unsigned  int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += image->getPixel(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average
            image->getPixel(i, j, 0) = 255;
            image->getPixel(i, j, 1) = 255 - avg;
            image->getPixel(i, j, 2) = 255 - avg;
        }
    }
}
// Main function
int main(){
    cout << "************Welcome to Baby Photoshop for Image Processing************\n";

    Image *current = new Image();
    loadImgDriver(current); // Load initial image

    int option = 0;
    while(option != 18){
        cout << "Please choose an option.\n";
        cout << "1- Load a new image\n";
        cout << "2- Filter: Rotate an image\n";
        cout << "3- Filter: Invert image colors\n";
        cout << "4- Filter: Turn image to only Black&White\n";
        cout << "5- Filter: Flip image\n";
        cout << "6- Filter: Convert to gray scale.\n";
        cout << "7- Filter: Lighten or darken an image.\n";
        cout << "8- Filter: Blur an image.\n";
        cout << "9- Filter: Put a frame on an image.\n";
        cout << "10- Filter: Crop an image.\n";
        cout << "11- Filter: Resizing an image.\n";
        cout << "12- Filter: Merge an image.\n";
        cout << "13- Filter: Edge detection.\n";
        cout << "14- Filter: Good natural sunlight.\n";
        cout << "15- Filter: Purpule look.\n";
        cout << "16- Filter: Infrared image.\n";
        cout << "17- save an image.\n";
        cout << "18-Exit.\n";
        cout << " >> ";
        cin >> option;

        Image *img = 0;
        switch(option){
            case 1:
                loadImgDriver(current); // Load a new image
                break;

            case 2:
                img = rotatedDriver(current); // Rotate the current image
                delete current;
                current = img;
                cout << "Image modified successfully." << endl; // Print success message
                break;

            case 3:
                img = invert(current); // Invert colors of the current image
                delete current;
                current = img;
                cout << "Image modified successfully." << endl; // Print success message
                break;

            case 4:
                applyBlackAndWhiteFilter(current); // Convert the current image to black and white
                cout << "Image modified successfully." << endl; // Print success message
                break;

            case 5:
                driveFliping(current); // Flip the current image
                cout << "Image modified successfully." << endl; // Print success message
                break;

            case 6:
                convertToGrayscale(current); // Convert the current image to grayscale
                cout << "Image modified successfully." << endl; // Print success message
                break;

            case 7:
                DarLighDriver(current); // Apply lighten/darken filter to the current image
                break;
            
            case 8:
                blur(current);
                cout << "Image modified successfully." << endl; // Print success message
                break;
            case 9:
                img = frame_driver(current);
                delete current;
                current = img;
                cout << "Image modified successfully." << endl; // Print success message
                break;
            case 10:
                cropping_driver(current);
                cout << "Image modified successfully." << endl; // Print success message
                break;
            case 11:
                resize_driver(current);
                cout << "Image modified successfully." << endl; // Print success message
                break;
            case 12:
                merge_driver(current);
                cout << "Image modified successfully." << endl; // Print success message
                break;
            case 13:
                edgeDetection_driver(current);
                cout << "Image modified successfully." << endl; // Print success message
                break;
            case 14:
                applySunlightFilter(current);
                cout << "Image modified successfully." << endl; // Print success message
                break;
            case 15:
                addHintOfPurple(current);
                cout << "Image modified successfully." << endl; // Print success message
                break;
            case 16:
                infrared(current);
                cout << "Image modified successfully." << endl; // Print success message
                break;
            case 17:
                saveImgDriver(current); // Save the current image
                break;

            case 18:
                delete current; // Exit the program
                cout << "Thank you for using Baby Photoshop for Image Processing.\n";
                cout << "*********************************************************";
                break;

            default:
                cout << "INVALID OPTION!!\n"; // Display error for invalid option
        }
    }
}


// our repo on githup: https://github.com/menna226/Assignment-3-
