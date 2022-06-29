/**
 * @file CsvWriter.h
 * @author Original authors: Martin York and Guillaume Racicot on StackOverflow (https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c)
 *  and updated by Matheus Kerber Veturelli (matheuskventurelli@gmail.com).
 * @brief File that implements classes to read CSVs.
 * @version 1.1
 * @date 2022-06-18
 * 
 * @copyright MIT License 2022
 * 
 */

#ifndef CSVREADER_H
#define CSVREADER_H

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <eigen3/Eigen/Dense>

/**
 * @brief Class that reads a CSV row.
 * 
 */
class CSVRow {
public:
    /**
     * @brief Index operator to access the cells of the row.
     * 
     * @param index: The index of the cell on the row.
     * @return std::string_view representing the contents of the cell.
     */
    std::string_view operator[](std::size_t index) const {
        return std::string_view(&m_line[m_data[index] + 1], m_data[index + 1] - (m_data[index] + 1));
    }

    /**
     * @brief The size of the row.
     * 
     * @return std::size_t representing the size of the row.
     */
    std::size_t size() const {
        return m_data.size() - 1;
    }

    /**
     * @brief Reads the next wor of the file.
     * 
     * @param str: The file stream to read from.    
     */
    void readNextRow(std::istream& str) {
        std::getline(str, m_line);

        m_data.clear();
        m_data.emplace_back(-1);
        std::string::size_type pos = 0;
        while((pos = m_line.find(';', pos)) != std::string::npos) {
            m_data.emplace_back(pos);
            ++pos;
        }

        // This checks for a trailing comma with no data after it.
        pos = m_line.size();
        m_data.emplace_back(pos);
    }
    
private:
    /**
     * @brief The line of the CSV file.
     * 
     */
    std::string m_line;

    /**
     * @brief Auxiliary variable to read the file and manage indexes.
     * 
     */
    std::vector<int> m_data;
};

/**
 * @brief Stream operator to read a CSV row.
 * 
 * @param str The data stream to read from.
 * @param data The CSV row that will read from the data stream.
 * @return std::istream& representing the stream that was read.
 */
std::istream& operator>>(std::istream& str, CSVRow& data) {
    data.readNextRow(str);
    return str;
}   

/**
 * @brief Class that represents an iterator of CSV rows.
 * 
 */
class CSVIterator {   
public:
    typedef std::input_iterator_tag     iterator_category;
    typedef CSVRow                      value_type;
    typedef std::size_t                 difference_type;
    typedef CSVRow*                     pointer;
    typedef CSVRow&                     reference;

    /**
     * @brief Construct a new CSVIterator object from a given file stream.
     * 
     * @param str fille stream to read from.
     */
    CSVIterator(std::istream& str) :m_str(str.good()?&str:nullptr) { ++(*this); }

    /**
     * @brief Default constructor for CSVIterator.
     * 
     */
    CSVIterator() :m_str(nullptr) {}

    /**
     * @brief Pre increment operator.
     * 
     * @return CSVIterator& representing the iterator after the increment.
     */
    CSVIterator& operator++() {
        if (m_str) {
            if (!((*m_str) >> m_row)) {
                m_str = nullptr;
            }
        }
        return *this;
    }
    
    /**
     * @brief Post increment operator.
     * 
     * @return CSVIterator& representing the iterator after the increment.
     */
    CSVIterator operator++(int) {
        CSVIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    /**
     * @brief Value of the iterator pointer.
     * 
     * @return CSVRow const& representing the value of the iterator pointer.
     */
    CSVRow const& operator*() const {
        return m_row;
    }

    /**
     * @brief Pointer function call operator.
     * 
     * @return CSVRow const* representing the pointer to titerator.
     */
    CSVRow const* operator->() const {
        return &m_row;
    }

    /**
     * @brief Checks if the iterator is equal to another iterator.
     * 
     * @param other: The iterator to compare with.
     * @return true if the iterators are equal.
     * @return false if the iterators are not equal.
     */
    bool operator==(CSVIterator const& rhs) {
        return ((this == &rhs) || ((this->m_str == nullptr) && (rhs.m_str == nullptr)));
    }

    /**
     * @brief Checks if the iterator is not equal to another iterator.
     * 
     * @param other: The iterator to compare with.
     * @return true if the iterators are not equal.
     * @return false if the iterators are equal.
     */
    bool operator!=(CSVIterator const& rhs) {
        return !((*this) == rhs);
    }

private:
    /**
     * @brief The file stream to read from.
     * 
     */ 
    std::istream* m_str;

    /**
     * @brief The CSV row that will read from the file stream.
     * 
     */
    CSVRow m_row;
};

/**
 * @brief Iterator class that makes it possible to use for each loops with CSVs.
 * 
 */
class CSVRange
{
    /**
     * @brief The file stream to read from.
     * 
     */
    std::istream& stream;
public:
    /**
     * @brief Construct a new CSVRange object from a given file stream.
     * 
     * @param str fille stream to read from.
     */
    CSVRange(std::istream& str) : stream(str) {}

    /**
     * @brief Iterator to the first row of the CSV.
     * 
     * @return CSVIterator representing the iterator to the first row of the CSV.
     */
    CSVIterator begin() const {
        return CSVIterator{stream};
    }

    /**
     * @brief Iterator to the end of the CSV.
     * 
     * @return CSVIterator representing the iterator to the end of the CSV.
     */
    CSVIterator end() const {
        return CSVIterator{};
    }
};

/**
 * @brief Helper function to split strings into a vector of strings.
 * 
 * @tparam Out: generic type to store the strings.
 * @param s: The string to split.
 * @param delim: The delimiter to split the string with.
 * @param result: The generic container that stores tha strings.
 */
template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

/**
 * @brief Spit a string into a vector of strings given a delimiter char.
 * 
 * @param s: The string to split.
 * @param delim: The delimiter to split the string with. 
 * @return std::vector<std::string> containing the split string. 
 */
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

/**
 * @brief Converts a string to a double vector of type Eigen::Vector2d.
 * 
 * @param str: The string to convert.
 * @return Eigen::Vector2d representing the double vector.
 */
Eigen::Vector2d get2DVector(std::string str) {
    std::vector<std::string> strVec = split(str, ' ');
    double x = atof(strVec[0].c_str());
    double y = atof(strVec[1].c_str());
    Eigen::Vector2d vec(x, y);
    return vec;
}

#endif