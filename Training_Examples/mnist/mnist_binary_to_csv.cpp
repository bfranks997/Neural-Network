#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

const int IMAGE_SIZE = 28;
const int NUM_IMAGES = 1000;
const int TOTAL_PIXELS = IMAGE_SIZE * IMAGE_SIZE;

// Function to save an image to a CSV file
void saveImageToCSV(const std::vector<unsigned char>& image, const std::string& folder, const std::string& fileName) {
    // Create directory if it doesn't exist
    if (!fs::create_directories(folder) && !fs::exists(folder)) {
        std::cerr << "Failed to create directory: " << folder << std::endl;
        return;
    }

    std::ofstream outFile(folder + "/" + fileName);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing: " << folder + "/" + fileName << std::endl;
        return;
    }

    for (int row = 0; row < IMAGE_SIZE; ++row) {
        for (int col = 0; col < IMAGE_SIZE; ++col) {
            outFile << static_cast<int>(image[row * IMAGE_SIZE + col]);
            if (col < IMAGE_SIZE - 1) {
                outFile << ",";
            }
        }
        outFile << "\n";
    }

    outFile.close();
}

// Function to process a text file and save images to CSV files
void processFileAndSaveCSV(const std::string& fileName, int digit) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        exit(1);
        return;
    }

    std::vector<unsigned char> buffer(TOTAL_PIXELS);
    std::string folderName = std::to_string(digit);

    for (int i = 0; i < NUM_IMAGES; ++i) {
        file.read(reinterpret_cast<char*>(buffer.data()), TOTAL_PIXELS);
        if (file.gcount() != TOTAL_PIXELS) {
            std::cerr << "Error reading image data from file." << std::endl;
            break;
        }

        std::string csvFileName = std::to_string(digit) + "_" + std::to_string(i) + ".csv";
        saveImageToCSV(buffer, folderName, csvFileName);
    }

    file.close();
}

int main() {
    // List of data files
    std::vector<std::string> files = {"data0.txt", "data1.txt", "data2.txt", "data3.txt", "data4.txt", 
                                      "data5.txt", "data6.txt", "data7.txt", "data8.txt", "data9.txt"};

    // Process each file and save images to corresponding folders
    for (int digit = 0; digit < files.size(); ++digit) {
        std::cout << "Processing file: " << files[digit] << std::endl;
        processFileAndSaveCSV(files[digit], digit);
    }

    return 0;
}
