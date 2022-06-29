/**
 * @file CsvWriter.h
 * @author Alex H. (https://github.com/al-eax/CSVWriter) and updated by Matheus Kerber Veturelli (matheuskventurelli@gmail.com)
 * @brief File that implements CsvWriter: a class that writes CSV files.
 * @version 1.1
 * @date 2022-06-18
 * 
 * @copyright MIT License 2022
 * 
 */

#ifndef CSVWRITER_H
#define CSVWRITER_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <typeinfo>

/**
 * @brief This class writes CSV files.
 * 
 */
class CsvWriter {
public:

    /**
     * @brief Default constructor for CsvWriter.
     * 
     */
    CsvWriter() {
        this->firstRow = true;
        this->seperator = ";";
        this->columnNum = -1;
        this->valueCount = 0;
    }

    /**
     * @brief Construct a new CsvWriter object with a predefined number of colums.
     * 
     * @param numberOfColums: Number of columns.
     */
    CsvWriter(int numberOfColums) {
        this->firstRow = true;
        this->seperator = ";";
        this->columnNum = numberOfColums;
        this->valueCount = 0;
    }

    /**
     * @brief Construct a new CsvWriter object with a given separator.
     * 
     * @param seperator: a std::string reference representing the separator.
     */
    CsvWriter(const std::string& seperator) {
        this->firstRow = true;
        this->seperator = seperator;
        this->columnNum = -1;
        this->valueCount = 0;
    }

    /**
     * @brief Construct a new CsvWriter object with a given number of columns and a given separator.
     * 
     * @param seperator: a std::string reference representing the separator.
     * @param numberOfColums: Number of columns.
     */
    CsvWriter(const std::string& seperator, int numberOfColums) {
        this->firstRow = true;
        this->seperator = seperator;
        this->columnNum = numberOfColums;
        this->valueCount = 0;
    }

    /**
     * @brief Add a constant char pointer to this CsvWriter object.
     * 
     * @param str: The constant char pointer to be added to the CsvWriter object.
     * @return Reference to a CsvWriter oject with str added.
     */
    CsvWriter& add(const char *str) { 
        return this->add(std::string(str));
    }

    /**
     * @brief Add a char pointer to this CsvWriter object.
     * 
     * @param str: The char pointer to be added to the CsvWriter object.
     * @return Reference to a CsvWriter oject with str added.
     */
    CsvWriter& add(char *str) {
        return this->add(std::string(str));
    }

    /**
     * @brief Add a string to this CsvWriter object.
     * 
     * @param str: The string to be added to the CsvWriter object.
     * @return Reference to a CsvWriter oject with str added.
     */
    CsvWriter& add(std::string str) {
        //if " character was found, escape it
        size_t position = str.find("\"",0);
        bool foundQuotationMarks = position != std::string::npos;
        while(position != std::string::npos){
            str.insert(position,"\"");
            position = str.find("\"",position + 2);
        }
        if(foundQuotationMarks){
            str = "\"" + str + "\"";
        }else if(str.find(this->seperator) != std::string::npos){
            //if seperator was found and string was not escapted before, surround string with "
            str = "\"" + str + "\"";
        }
        return this->add<std::string>(str);
    }

    /**
     * @brief Add a generig type T to this CsvWriter object.
     * 
     * @tparam T: generic type.
     * @param str: The generic object to be added to the CsvWriter object. 
     * @return Reference to a CsvWriter oject with str added.
     */
    template<typename T>
    CsvWriter& add(T str) {
        if(this->columnNum > -1){
            //if autoNewRow is enabled, check if we need a line break
            if(this->valueCount == this->columnNum ){
                this->newRow();
            }
        }
        if(valueCount > 0)
            this->ss << this->seperator;
        this->ss << str;
        this->valueCount++;

        return *this;
    }

    /**
     * @brief Appends a generic object to this CsvWriter object.
     * 
     * @tparam T: generic type.
     * @param t: The generic object to be appended to the CsvWriter object. 
     * @return Reference to a CsvWriter oject with t added.
     */
    template<typename T>
    CsvWriter& operator<<(const T& t) {
        return this->add(t);
    }

    /**
     * @brief Append the content of another CsvWriter object to this CsvWriter object. 
     * 
     * @param csv: Other CsvWriter object.
     */
    void operator+=(CsvWriter &csv) {
        this->ss << std::endl << csv;
    }

    /**
     * @brief Returns the content of this CsvWriter object as a string.
     * 
     * @return std::string representing the content of this CsvWriter object.
     */
    std::string toString() {
        return ss.str();
    }

    /**
     * @brief Appends the contents of this CsvWriter object to an ostream and returns the ostream.
     * 
     * @param os: The ostream to append the content of this CsvWriter object to.
     * @param csv: The CsvWriter object to append to the ostream.
     * @return std::ostream& representing the ostream with the content of this CsvWriter object appended to it.
     */
    friend std::ostream& operator<<(std::ostream& os, CsvWriter & csv) {
        return os << csv.toString();
    }

    /**
     * @brief Add a new row to this CsvWriter object.
     * 
     * @return CsvWriter& with the row added.
     */
    CsvWriter& newRow() {
        if(!this->firstRow || this->columnNum > -1) {
            ss << std::endl;
        } else {
            //if the row is the first row, do not insert a new line
            this->firstRow = false;
        }
        valueCount = 0;
        return *this;
    }

    /**
     * @brief Erases the contents of a file.
     * 
     * @param filename: name of the file.
     * @return true: if the file contents were successfully erased. 
     * @return false: if the file contents were not be erased. 
     */
    bool eraseFileContents(const std::string& filename) {
        std::ofstream file;
        file.open(filename.c_str(), std::ios::out | std::ios::trunc);;
        if(file.is_open()) {
            file.close();
            return true;
        }
        return false;
    }

    /**
     * @brief Writes the content of this CsvWriter object to a file.
     * 
     * @param filename: The name of the file.
     * @return true if no error flags are set. False otherwise. (see std::ofstream::fail)
     */
    bool writeToFile(const std::string& filename) {
        return writeToFile(filename,false);
    }

    /**
     * @brief Writes the content of this CsvWriter object to a file.
     * 
     * @param filename: The name of the file.
     * @param append: If true, the content of this CsvWriter object is appended to the file.
     * @return true if no error flags are set. False otherwise. (see std::ofstream::fail)
     */
    bool writeToFile(const std::string& filename, bool append) {
        std::ofstream file;
        bool appendNewLine = false;
        if (append) {
            //check if last char of the file is newline
            std::ifstream fin;
            fin.open(filename);
            if (fin.is_open()) {
                fin.seekg(-1, std::ios_base::end); //go to end of file
                int lastChar = fin.peek();
                if (lastChar != -1 && lastChar != '\n') //if file is not empty and last char is not new line char
                    appendNewLine = true;
            }
            file.open(filename.c_str(), std::ios::out | std::ios::app);
        }
        else {
            file.open(filename.c_str(), std::ios::out | std::ios::trunc);
        }
        if(!file.is_open())
            return false;
        if(append && appendNewLine) {
            file << std::endl;
            std::string s = this->toString();
            s = s.substr(1, s.size() - 2);
            file << s;
        } else {
            file << this->toString();
        }
        file.close();
        return file.good();
    }

    /**
     * @brief Sets the maximum number of columns in a row. If 
     * the user tries to add more columns than this number, a new row is added.
     * 
     * @param numberOfColumns: The maximum number of columns in a row.
     */
    void enableAutoNewRow(int numberOfColumns) {
        this->columnNum = numberOfColumns;
    }

    /**
     * @brief Disables the automatic new row feature.   
     * 
     */
    void disableAutoNewRow() {
        this->columnNum = -1;
    }

    /**
     * @brief Resets the contents of this CsvWriter object.
     * 
     */
    void resetContent() {
        const static std::stringstream initial;

        ss.str(std::string());
        ss.clear();
        ss.copyfmt(initial);
    }  

    /**
     * @brief Destructor for the CsvWriter class.
     * 
     */
    ~CsvWriter() {
        resetContent();
    }

protected:

    /**
     * @brief std::string representing the separator of the CSV file.
     * 
     */
    std::string seperator;

    /**
     * @brief Maximum number of columns in a row. If the value is -1,
     *  the automatic new row feature is disabled.
     * 
     */
    int columnNum;

    /**
     * @brief Current number of columns in a row.
     * 
     */
    int valueCount;

    /**
     * @brief If true, the first row is not written to the file.
     * 
     */
    bool firstRow;

    /**
     * @brief std::stringstream object representing the content of this CsvWriter object.
     * 
     */
    std::stringstream ss;

};

#endif // CSVWRITER_H