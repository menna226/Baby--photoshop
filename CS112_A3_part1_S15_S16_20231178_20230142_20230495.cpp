// FCAI – Structured Programming – 2024 - Assignment 3
// Program Name: CS112_A3_Part1_S15_S16_20231178_20230142_20230495.cpp
// Program Description: This program allows the user to upload and apply on it diffrent filters and the user can choose more than one image to apply the filter needed, the user can apply diffrent filters on the same image, it allows the user to save the image too. 
// Last Modification Date: 27/3/2023
// Author1 and ID and Group: Menna Abdallah Helmi, ID: 20231178, she did Invert Image colors filter & Rotate Image filter, Email: mennaabdallah2.2.6@gmail.com
// Author2 and ID and Group: Roaa Mohammed Sayed, ID: 20230142, she did Grayscale Conversion filter & Darken and Lighten Image, Email: roaamuhamed312@gmail.com
// Author3 and ID and Group: Yosef Hamdy Aboelmaaty, ID: 20230495, He did Black and White filter & Flip Image filter, Email: yosefhamdy4102@gmail.com
// Teaching Assistant: Belal Tarek Hassan


#include <iostream>
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
// Main function
int main(){
    cout << "************Welcome to Baby Photoshop for Image Processing************\n";

    Image *current = new Image();
    loadImgDriver(current); // Load initial image

    int option = 0;
    while(option != 9){
        cout << "Please choose an option.\n";
        cout << "1- Load a new image\n";
        cout << "2- Filter: Rotate an image\n";
        cout << "3- Filter: Invert image colors\n";
        cout << "4- Filter: Turn image to only Black&White\n";
        cout << "5- Filter: Flip image.\n";
        cout << "6- Filter: Convert to gray scale.\n";
        cout << "7- Filter: Lighten or darken an image.\n";
        cout << "8- save an image.\n";
        cout << "9-Exit.\n";
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
                saveImgDriver(current); // Save the current image
                break;

            case 9:
                delete current; // Exit the program
                cout << "Thank you for using Baby Photoshop for Image Processing.";
                break;

            default:
                cout << "INVALID OPTION!!\n"; // Display error for invalid option
        }
    }
}