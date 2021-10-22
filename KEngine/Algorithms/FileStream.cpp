#include "FileStream.hpp"

namespace ke
{

	FileStream::FileStream()
	{
		m_loaded = false;
	}


	////////////////////////////////


	FileStream::FileStream(const std::string& filename, std::ios_base::openmode mode, int prot)
	{
		m_file_stream.open(filename, mode, prot);
		m_file_name = filename;

		if (!m_file_stream.good())
		{
			throw_error("FileStream::FileStream(...)", "could not open \"" + filename + "\"", "ERROR");
			m_loaded = false;
		}

		m_loaded = true;
	}


	////////////////////////////////


	FileStream::~FileStream()
	{
		m_file_stream.close();
	}



	////////////////////////////////////////////////////////////////



	void FileStream::createFile(const std::string& filename)
	{
		std::ofstream buffer(filename);
		buffer.close();
	}


	////////////////////////////////


	void FileStream::setFileName(const std::string& name)
	{
		m_file_name = name;
	}

	std::string FileStream::getFileName() const
	{
		return m_file_name;
	}


	////////////////////////////////


	bool FileStream::open(const std::string& filename, std::ios_base::openmode mode, int prot)
	{
		m_file_stream.open(filename, mode, prot);
		m_file_name = filename;

		if (!m_file_stream.good())
		{
			throw_error("FileStream::open(...)", "could not open \"" + filename + "\"", "ERROR");
			m_loaded = false;
			return false;
		}

		m_loaded = true;
		return true;
	}

	void FileStream::close()
	{
		m_file_stream.close();
	}



	////////////////////////////////////////////////////////////////



	bool FileStream::getline(std::string& _string, char ending_char)
	{
		if (!(std::getline(m_file_stream, _string, ending_char)))
		{
			throw_error("FileStream::getline(...)", "could not read from \"" + m_file_name + "\"", "ERROR");
			return false;
		}

		return true;
	}


	////////////////////////////////


	bool FileStream::binRead(std::string& _string)
	{
		size_t str_size = _string.size();

		if (m_file_stream.eof())
		{
			throw_error("FileStream::binRead(str)", "\"" + m_file_name + " is incomplete - reached end of file", "WARNING");
			return false;
		}

		if (!(m_file_stream.read(reinterpret_cast<char*>(&str_size), sizeof(str_size))))
		{
			throw_error("FileStream::binRead(str)", "could not read from \"" + m_file_name + "\"", "ERROR");

			if (Settings::ModifyStringWhenFstreamFailed())
				_string = "_0";

			return false;
		}
		else if (str_size < 0 || str_size > Settings::MaxStringSize())
		{
			throw_error("FileStream::binRead(str)", "string is too large", "ERROR");
			print_note("you can set maximum string size in Settings::setMaxStringSize(..)");

			if (Settings::ModifyStringWhenFstreamFailed())
				_string = "_0";

			return false;
		}
		else
		{
			_string.resize(str_size);

			if (!(m_file_stream.read(&_string[0], str_size)))
			{
				throw_error("FileStream::binRead(str)", "could not read from \"" + m_file_name + "\"", "ERROR");
				if (Settings::ModifyStringWhenFstreamFailed())
					_string = "_0";

				return false;
			}

		}

		return true;
	}

	bool FileStream::binWrite(const std::string& _string)
	{
		size_t str_size = _string.size();


		if (!(m_file_stream.write(reinterpret_cast<char*>(&str_size), sizeof(str_size))))
		{
			throw_error("FileStream::binWrite(T)", "could not write to \"" + m_file_name + "\"", "ERROR");
			return false;
		}
		if (!(m_file_stream.write(&_string[0], str_size)))
		{
			throw_error("FileStream::binWrite(T)", "could not write to \"" + m_file_name + "\"", "ERROR");
			return false;
		}

		return true;
	}



	//bool FileStream::binRead(char* _string)
	//{
	//	size_t str_size = strlen(_string);

	//	if (m_file_stream.eof())
	//	{
	//		throw_error("FileStream::binRead(str)", "\"" + m_file_name + " is incomplete - reached end of file", "WARNING");
	//		return false;
	//	}

	//	if (!(m_file_stream.read(reinterpret_cast<char*>(&str_size), sizeof(str_size))))
	//	{
	//		throw_error("FileStream::binRead(str)", "could not read from \"" + m_file_name + "\"", "ERROR");

	//		if (Settings::ModifyStringWhenFstreamFailed())
	//			strcpy(_string, "_0"); // ERROR: UNSAFE

	//		return false;
	//	}
	//	else if (str_size < 0 || str_size > Settings::MaxStringSize())
	//	{
	//		throw_error("FileStream::binRead(str)", "string is too large", "ERROR");
	//		print_note("you can set maximum string size in Settings::setMaxStringSize(..)");

	//		if (Settings::ModifyStringWhenFstreamFailed())
	//			strcpy(_string, "_0"); // ERROR: UNSAFE
	//			

	//		return false;
	//	}

	//	return true;
	//}

	//bool FileStream::binWrite(const char* _string)
	//{
	//	size_t str_size = strlen(_string);


	//	if (!(m_file_stream.write(reinterpret_cast<char*>(&str_size), sizeof(str_size))))
	//	{
	//		throw_error("FileStream::binWrite(T)", "could not write to \"" + m_file_name + "\"", "ERROR");
	//		return false;
	//	}
	//	/*if (!(m_file_stream.write(&_string[0], str_size)))
	//	{
	//		throw_error("FileStream::binWrite(T)", "could not write to \"" + m_file_name + "\"", "ERROR");
	//		return false;
	//	}*/

	//	return true;
	//}


	////////////////////////////////


	void FileStream::seekg(std::streampos s_posistion)
	{
		if (!(m_file_stream.seekg(s_posistion)))
			throw_error("FileStream::seekg(...)", "could not set position in file \"" + m_file_name + "\"", "ERROR");
	}

	void FileStream::seekg(std::streamoff s_off, std::ios_base::seekdir way)
	{
		if (!(m_file_stream.seekg(s_off, way)))
			throw_error("FileStream::seekg(...)", "could not set position in file \"" + m_file_name + "\"", "ERROR");
	}


	////////////////////////////////


	void FileStream::seekp(std::streampos s_posistion)
	{
		if (!(m_file_stream.seekg(s_posistion)))
			throw_error("FileStream::seekp(...)", "could not set position in file \"" + m_file_name + "\"", "ERROR");
	}

	void FileStream::seekp(std::streamoff s_off, std::ios_base::seekdir way)
	{
		if (!(m_file_stream.seekp(s_off, way)))
			throw_error("FileStream::seekp(...)", "could not set position in file \"" + m_file_name + "\"", "ERROR");
	}



	////////////////////////////////////////////////////////////////



	std::fstream* FileStream::getFStream()
	{
		return &m_file_stream;
	}


	////////////////////////////////


	bool FileStream::loaded() const
	{
		return m_loaded;
	}

} // namespace ke