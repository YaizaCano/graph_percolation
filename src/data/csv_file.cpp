#include "csv_file.h"


/* =================================
 *               PUBLIC
 *  =================================*/

CsvFile::CsvFile(std::string const &fileDir) {
    outputDir = fileDir;
}

void CsvFile::addRow(CsvRow const &row) {
    rows.push_back(row);
}

void CsvFile::write() const {
    unsigned int i = 0;
    std::string fileName = outputDir + "_experiment_";
    std::ifstream fileOpener(fileName + std::to_string(i) + CSV_EXTENSION);
    while(fileOpener.is_open()){
        fileOpener.close();
        fileOpener = std::ifstream(fileName + std::to_string(++i) + CSV_EXTENSION);
    }

    std::ofstream file(fileName + std::to_string(i) + CSV_EXTENSION, std::ios::out);
    std::cout << "Writing file " << fileName + std::to_string(i) + CSV_EXTENSION << std::endl;
    for(auto const& row : rows){
        std::string currentRow;
        int current = 0;
        for(auto const& value : row){
            currentRow += value;
            if(current != row.size() - 1)currentRow += ",";
            current++;
        }
        file << currentRow << "\n";
    }
    file.close();
}
