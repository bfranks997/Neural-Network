#include <iostream>
#include <fstream>
#include <vector>

const int IMAGE_SIZE = 28;
const int NUM_IMAGES = 1000;
const int TOTAL_PIXELS = IMAGE_SIZE * IMAGE_SIZE;

// Function to read and display a few images from a binary file
void processAndDisplayImages(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }

    std::vector<unsigned char> buffer(TOTAL_PIXELS);

    for (int i = 0; i < 5; ++i) { // Display first 5 images
        file.read(reinterpret_cast<char*>(buffer.data()), TOTAL_PIXELS);
        if (file.gcount() != TOTAL_PIXELS) {
            std::cerr << "Error reading image data from file." << std::endl;
            break;
        }

        // Display the image in ASCII (for simplicity)
        std::cout << "Image " << i + 1 << ":\n";
        for (int row = 0; row < IMAGE_SIZE; ++row) {
            for (int col = 0; col < IMAGE_SIZE; ++col) {
                std::cout << (buffer[row * IMAGE_SIZE + col] > 128 ? "#" : ".");
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    file.close();
}

int main() {
    // List of data files
    std::vector<std::string> files = {"data0.txt", "data1.txt", "data2.txt", "data3.txt", "data4.txt", "data5.txt", "data6.txt", "data7.txt", "data8.txt", "data9.txt"};

    // Process and display images from one file as a test
    std::string testFile = "data0.txt"; // Example file to process
    processAndDisplayImages(testFile);

    return 0;
}
