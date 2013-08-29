#include "CSVFileReader.hpp"
#include <cstdlib> // For atof
#include <fstream>
#include <sstream>

const std::vector<std::string> CSVFileReader::convert_line_to_vector_of_strings(const std::string& line, const char separator) const
{
    std::istringstream line_stream(line);
    std::string field;
    bool end_of_file_was_reached = true;
    std::vector<std::string> values;
    while (std::getline(line_stream, field, separator))
    {
        values.push_back(field);
        end_of_file_was_reached = line_stream.eof();
    }
    if (not(end_of_file_was_reached)) values.push_back(std::string());
    return values;
}

const std::vector<double> CSVFileReader::convert_line_to_vector_of_doubles(const std::string& line, const char separator) const
{
    const std::vector<std::string> values = convert_line_to_vector_of_strings(line, separator);
    std::vector<double> ret;
    std::vector<std::string>::const_iterator it = values.begin();
    for (;it!=values.end() ; ++it) ret.push_back(atof(it->c_str()));
    return ret;
}

void CSVFileReader::extract_column_titles(std::istream& file, const char separator)
{
	std::string current_line;
	getline(file, current_line, '\n');
	titles = convert_line_to_vector_of_strings(current_line, separator);

}

void CSVFileReader::extract_values(std::istream& file, const char separator)
{
	std::string current_line;
	while (getline(file, current_line, '\n'))
	{
		values.push_back(convert_line_to_vector_of_doubles(current_line, separator));
	}
}


CSVFileReader::CSVFileReader(const char* filename, const size_t expected_nb_of_columns, const char separator) : titles(std::vector<std::string>()),
		values(std::vector<std::vector<double> >()),
		that_line(values.begin())
{
	std::ifstream file(filename);
	if (not (file.good()))
	{
		THROW(__PRETTY_FUNCTION__,CSVFileReaderException, "Unable to open CSV file.");
	}

	extract_column_titles(file, separator);
	if (titles.size() != expected_nb_of_columns)
    {
        THROW(__PRETTY_FUNCTION__, CSVFileReaderException, "Invalid number of columns.");
    }
	extract_values(file, separator);
	that_line = values.begin();
}

bool CSVFileReader::has_more_data() const
{
	return that_line != values.end();
}

std::vector<double> CSVFileReader::get_line()
{
	if (that_line == values.end())
	{
		THROW(__PRETTY_FUNCTION__, CSVFileReaderException, "No more lines in input CSV file.");
	}
	return *(that_line++);
}
